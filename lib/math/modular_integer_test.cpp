#include "gtest/gtest.h"
#include "modular_integer.hpp"
//#include "modular_integer_terse.hpp"


constexpr int intModulus = 7;
using ModularInt = Modular<std::integral_constant<std::decay<decltype(intModulus)>::type, intModulus>>;

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

// TODO Add tests for the other functionalities
