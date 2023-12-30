#include <algorithm>
#include <numeric>

#include "gtest/gtest.h"

int times2(int x) { return 2*x; }

auto generateNumbers(const int size)
{
    std::vector<int> a(size, 0);
    std::iota(a.begin(), a.end(), 1);
    return a;
}
const auto someNumbers = generateNumbers(10); // 1, 2, ..., 10

// region transform
TEST(algorithm, transform)
{
    std::vector<int> results{};
    std::transform(someNumbers.begin(), someNumbers.end(), std::back_inserter(results), times2);
    EXPECT_EQ(results, std::vector<int>({2, 4, 6, 8, 10, 12, 14, 16, 18, 20}));
}

TEST(algorithm, rangesTransform)
{
    std::vector<int> results{};
    std::ranges::transform(someNumbers, std::back_inserter(results), times2);
    EXPECT_EQ(results, std::vector<int>({2, 4, 6, 8, 10, 12, 14, 16, 18, 20}));
}
// endregion transform
