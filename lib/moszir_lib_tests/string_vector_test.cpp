#include <fstream>
#include "gtest/gtest.h"
#include "moszir_lib/string/string_vector_terse.hpp"

namespace moszir
{

TEST(stringVector, defaultConstructor)
{
    StringVector sv;
    EXPECT_TRUE(sv.empty());
    EXPECT_EQ(0u, sv.size());
}

/**
 * @test
 * Tests the string vector's constructor with 1 delimiter, empty fields not allowed.
 */
TEST(stringVector, constructor1)
{
    StringVector sv(";;Apple;;;banana;;lemon;", ";", false);
    EXPECT_EQ(3u, sv.size());
    EXPECT_EQ("Apple", sv[0]);
    EXPECT_EQ("banana", sv[1]);
    EXPECT_EQ("lemon", sv[2]);
}

/**
 * @test
 * Tests the string vector's constructor with 1 delimiter, empty fields are allowed.
 */
TEST(stringVector, constructor2)
{
    StringVector sv(";;Apple;;;banana;;lemon;", ";", true);
    EXPECT_EQ(9u, sv.size());
    EXPECT_EQ(sv, std::vector<std::string>({"", "", "Apple", "", "", "banana", "", "lemon", ""}));
}

/**
 * @test
 * Tests the string vector's constructor with multiple delimiters, empty fields are not allowed.
 */
TEST(stringVector, constructor3)
{
    StringVector sv(",;Apple.;,banana.,lemon;", ";.,", false);
    EXPECT_EQ(3u, sv.size());
    EXPECT_EQ(sv, std::vector<std::string>({"Apple", "banana", "lemon"}));
}

/**
 * @test
 * Tests the string vector's constructor with multiple delimiters, empty fields are allowed.
 */
TEST(stringVector, constructor4)
{
    StringVector sv(",;Apple.;,banana.,lemon;", ";.,", true);
    EXPECT_EQ(9u, sv.size());
    EXPECT_EQ(sv, std::vector<std::string>({"", "", "Apple", "", "", "banana", "", "lemon", ""}));
}

/**
 * @test
 * Tests building a string vector from a stream.
 */
TEST(stringVector, fromStream)
{
    std::ofstream out("string_vector_from_stream.txt");
    out <<
        ";;Apple;;;banana;;lemon;\n"
        ";;Apple;;;banana;;lemon;\n"
        ",;Apple.;,banana.,lemon;\n"
        ",;Apple.;,banana.,lemon;\n";
    out.close();

    std::ifstream in("string_vector_from_stream.txt");
    StringVector sv(in, ";", true);
    EXPECT_EQ(sv, std::vector<std::string>({"", "", "Apple", "", "", "banana", "", "lemon", ""}));
    sv = StringVector(in, ";", false);
    EXPECT_EQ(sv, std::vector<std::string>({"Apple", "banana", "lemon"}));
    sv = StringVector(in, ";.,", true);
    EXPECT_EQ(sv, std::vector<std::string>({"", "", "Apple", "", "", "banana", "", "lemon", ""}));
    sv = StringVector(in, ";,.", false);
    EXPECT_EQ(sv, std::vector<std::string>({"Apple", "banana", "lemon"}));

    // The file has an empty line at its end.
    // While it is possible to get an infinite amount of empty string vectors out of it,
    // we shall only get one by checking `in.good()`.
    int counter = 0;
    while (in.good() && (++counter < 10))
    {
        sv = StringVector(in, ";,.", false);
        EXPECT_TRUE(sv.empty());
    }
    EXPECT_EQ(counter, 1);
}

/**
 * @test
 * Tests the `fromString` function with 1 delimiter, empty fields not allowed.
 */
TEST(stringVector, fromString1)
{
    StringVector sv("original content", " ");
    sv.fromString(";;Apple;;;banana;;lemon;", ";", false);
    EXPECT_EQ(3u, sv.size());
    EXPECT_EQ("Apple", sv[0]);
    EXPECT_EQ("banana", sv[1]);
    EXPECT_EQ("lemon", sv[2]);
}

/**
 * @test
 * Tests the `fromString` function with 1 delimiter, empty fields are allowed.
 */
TEST(stringVector, fromString2)
{
    StringVector sv("original content", " ");
    sv.fromString(";;Apple;;;banana;;lemon;", ";", true);
    EXPECT_EQ(9u, sv.size());
    EXPECT_EQ(sv, std::vector<std::string>({"", "", "Apple", "", "", "banana", "", "lemon", ""}));
}

/**
 * @test
 * Tests the `fromString` function with multiple delimiters, empty fields are not allowed.
 */
TEST(stringVector, fromString3)
{
    StringVector sv("original content", " ");
    sv.fromString(",;Apple.;,banana.,lemon;", ";.,", false);
    EXPECT_EQ(3u, sv.size());
    EXPECT_EQ(sv, std::vector<std::string>({"Apple", "banana", "lemon"}));
}

/**
 * @test
 * Tests the `fromString` function with multiple delimiters, empty fields are allowed.
 */
TEST(stringVector, fromString4)
{
    StringVector sv("original content", " ");
    sv.fromString(",;Apple.;,banana.,lemon;", ";.,", true);
    EXPECT_EQ(9u, sv.size());
    EXPECT_EQ(sv, std::vector<std::string>({"", "", "Apple", "", "", "banana", "", "lemon", ""}));
}

/**
 * @test
 * Tests the `findIndex` function.
 */
TEST(stringVector, findIndex)
{
    StringVector sv("apple banana lemon", " ");
    EXPECT_EQ(1, sv.findIndex("banana"));
}

/**
 * @test
 * Tests the `findIndex` function with a start index.
 */
TEST(stringVector, findIndexWithStart)
{
    StringVector sv("apple banana lemon melon banana", " ");
    EXPECT_EQ(4, sv.findIndex("banana", 2)); // skips the banana at index 1.
}

/**
 * @test
 * Tests the `findIndex` function when the token is not part of the vector.
 */
TEST(stringVector, findIndexNotFound)
{
    StringVector sv("apple banana lemon melon banana", " ");
    EXPECT_EQ(-1, sv.findIndex("pomegranate"));
}

/**
 * @test
 * Tests the `findIndex` function when the token is only found before the start index.
 */
TEST(stringVector, findIndexWithStartNotFound)
{
    StringVector sv("apple banana lemon melon banana", " ");
    EXPECT_EQ(-1, sv.findIndex("apple", 1)); // skips the apple at index 0.
}

} // namespace moszir
