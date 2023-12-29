#include <fstream>
#include <filesystem>

#include "gtest/gtest.h"

#include "moszir_lib/math/modular_integer_terse.hpp"


constexpr int intModulus = 7;
using ModularInt = ::moszir::Modular<std::integral_constant<std::decay<decltype(intModulus)>::type, intModulus>>;

constexpr int64_t longModulus = 11;
using ModularLong = ::moszir::Modular<std::integral_constant<std::decay<decltype(longModulus)>::type, longModulus>>;

TEST(modular, defaultConstructor)
{
    EXPECT_EQ(ModularInt(), 0);
}

TEST(modular, constructor)
{
    EXPECT_EQ(ModularInt(6)(), 6);
    EXPECT_EQ(ModularInt(uint32_t(6u))(), 6);
    EXPECT_EQ(ModularInt(int64_t(6ll))(), 6);
    EXPECT_EQ(ModularInt(uint64_t(6ull))(), 6);
}

TEST(modular, normalize)
{
    EXPECT_EQ(ModularInt::normalize(0), 0);
    EXPECT_EQ(ModularInt::normalize(1), 1);
    EXPECT_EQ(ModularInt::normalize(5), 5);
    EXPECT_EQ(ModularInt::normalize(7), 0);
    EXPECT_EQ(ModularInt::normalize(8), 1);
    EXPECT_EQ(ModularInt::normalize(50), 1);
    EXPECT_EQ(ModularInt::normalize(-1), 6);
    EXPECT_EQ(ModularInt::normalize(-7), 0);
    EXPECT_EQ(ModularInt::normalize(-8), 6);
    EXPECT_EQ(ModularInt::normalize(-50), 6);
}

TEST(modular, invert)
{
    EXPECT_EXIT(ModularInt::invert(0), testing::ExitedWithCode(3), "");
    // The `invert` method does return negative values when the `%` operator does so.
    // E.g. invert(2) is actually -3.
    // The return value is intentionally not normalized, as invert is used in the division operation
    // (which multiplies with the inverse), which has to do a normalization anyway.
    auto f = [](auto n){ return ModularInt::normalize(ModularInt::invert(n)); };
    EXPECT_EQ(f(1), 1);
    EXPECT_EQ(f(2), 4); // 2*4 == 8 ~ 1  //  2 * -3 == -6 ~ 1
    EXPECT_EQ(f(3), 5); // 3*5 == 15 ~ 1 //  3 * -2
    EXPECT_EQ(f(4), 2);
    EXPECT_EQ(f(5), 3);
    EXPECT_EQ(f(6), 6); // 6*6 == 36 ~ 1 // -1 * -1 == 1
}

TEST(modular, conversion)
{
    auto m = ModularInt(5);
    EXPECT_EQ(m(), 5);
    EXPECT_EQ(int64_t(m), 5ll);
    EXPECT_EQ(uint32_t(m), 5u);
    EXPECT_EQ(double(m), 5.0);
}

TEST(modular, unaryMinus)
{
    EXPECT_EQ((-ModularInt(0))(), 0);
    EXPECT_EQ((-ModularInt(1))(), 6);
    EXPECT_EQ((-ModularInt(2))(), 5);
    EXPECT_EQ((-ModularInt(3))(), 4);
    EXPECT_EQ((-ModularInt(4))(), 3);
    EXPECT_EQ((-ModularInt(5))(), 2);
    EXPECT_EQ((-ModularInt(6))(), 1);
}

TEST(modular, compoundAddition)
{
    ModularInt m(3);
    m += ModularInt(5);
    EXPECT_EQ(m(), 1);
    m += 100;
    EXPECT_EQ(m(), 3); // 101 == 14*7 + 3
}

TEST(modular, addition)
{
    EXPECT_EQ((ModularInt(4) + ModularInt(5))(), 2);
    EXPECT_EQ((ModularInt(4) + 5)(), 2);
    EXPECT_EQ((4 + ModularInt(5))(), 2);
}

TEST(modular, increment)
{
    ModularInt m(6);
    EXPECT_EQ((++m)(), 0);
    EXPECT_EQ(m(), 0);

    m = ModularInt(6);
    EXPECT_EQ((m++)(), 6);
    EXPECT_EQ(m(), 0);
}

TEST(modular, compoundSubtraction)
{
    ModularInt m(3);
    m -= ModularInt(6);
    EXPECT_EQ(m(), 4);
    m -= 100;
    EXPECT_EQ(m(), 2); // 4 - 100 == -96 == (-14)*7 + 2
}

TEST(modular, subtraction)
{
    EXPECT_EQ((ModularInt(4) - ModularInt(5))(), 6);
    EXPECT_EQ((ModularInt(4) - 5)(), 6);
    EXPECT_EQ((4 - ModularInt(5))(), 6);
}

TEST(modular, decrement)
{
    ModularInt m(0);
    EXPECT_EQ((--m)(), 6);
    EXPECT_EQ(m(), 6);

    m = 0;
    EXPECT_EQ((m--)(), 0);
    EXPECT_EQ(m(), 6);
}

TEST(modular, compoundMultiplication)
{
    ModularInt m(3);
    m *= ModularInt(4); // 3*4 == 12 ~ 5 (7)
    EXPECT_EQ(m(), 5);
    m *= 10; // 5*10 == 50 ~ 1 (7)
    EXPECT_EQ(m(), 1);

    ModularLong n(10);
    n *= ModularLong(7); // 10*7 == 70 ~ 4 (11)
    EXPECT_EQ(n(), 4);
    n *= 7; // 4*7 == 28 ~ 6 (11)
    EXPECT_EQ(n(), 6);
}

TEST(modular, multiplication)
{
    const ModularInt m(3);
    const ModularInt n(4);
    EXPECT_EQ((m*n)(), 5);
    EXPECT_EQ((m*4ll)(), 5);
    EXPECT_EQ((3*n)(), 5);

    const ModularLong v(5);
    const ModularLong w(9);
    EXPECT_EQ((v*w)(), 1);
    EXPECT_EQ((v*9)(), 1);
    EXPECT_EQ((5ll*w)(), 1);
}

TEST(modular, compoundDivision)
{
    ModularInt m(3);
    m /= ModularInt(4);
    EXPECT_EQ(m(), 6); // 6*4 == 24 ~ 3 (7)
    m /= 2;
    EXPECT_EQ(m(), 3);
    m /= 74;
    EXPECT_EQ(m(), 6); // 74 ~ 4 (7), so we should get the same as above
}

TEST(modular, division)
{
    ModularInt m(3);
    ModularInt n(4);
    EXPECT_EQ((m / n)(), 6); // 6*4 == 24 ~ 3 (7)
    EXPECT_EQ((m / 4)(), 6);
    EXPECT_EQ((3 / n)(), 6);
}

TEST(modular, comparisons)
{
    for (int i = 0; i < 7; ++i)
    {
        for (int j = 0; j < 7; ++j)
        {
            EXPECT_EQ(ModularInt(i) == ModularInt(j), i == j);
            EXPECT_EQ(ModularInt(i) != ModularInt(j), i != j);
            EXPECT_EQ(ModularInt(i) < ModularInt(j), i < j);
            EXPECT_EQ(ModularInt(i) <= ModularInt(j), i <= j);
            EXPECT_EQ(ModularInt(i) > ModularInt(j), i > j);
            EXPECT_EQ(ModularInt(i) >= ModularInt(j), i >= j);
        }
    }
}

TEST(modular, power)
{
    ModularInt m(2);
    EXPECT_EQ(m.power(0), 1);
    EXPECT_EQ(m.power(1), 2);
    EXPECT_EQ(m.power(2), 4);
    EXPECT_EQ(m.power(3), 1);
    EXPECT_EQ(m.power(4), 2);
}

TEST(modular, stream)
{
    if (std::filesystem::exists("modular_integer_test_stream.txt"))
    {
        std::filesystem::remove("modular_integer_test_stream.txt");
    }

    std::ofstream testOut("modular_integer_test_stream.txt");
    testOut << ModularInt(73) << ' ' << 74 << '\n'; // Contains 3 and 74.
    testOut.close();

    std::ifstream in("modular_integer_test_stream.txt");
    std::string s;
    std::getline(in, s);
    EXPECT_EQ(s, "3 74");
    in.close();

    in.open("modular_integer_test_stream.txt");
    ModularInt m;
    in >> m;
    EXPECT_EQ(m(), 3);
    in >> m;
    EXPECT_EQ(m(), 4);
}
