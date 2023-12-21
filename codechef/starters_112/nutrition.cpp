/**
 * https://www.codechef.com/problems/NUTRITION
 *
 * You have $N$ fruits, the $i$-th is of type $A_i$ and has nutrition $B_i$.
 * You can eat at most one of each type of fruit.
 * What’s the maximum nutrition you can attain?
 */
#include <iostream>
#include <array>
#include <numeric>

#define in std::cin
#define out std::cout

/**
 * Since we can only eat at most one fruit of each type, clearly it’s best to eat the one with maximum nutrition of each type.
 * If this maximum nutrition is negative, it’s optimal to not eat any fruits of this type.
 */
int main()
{
    int t; in >> t;
    while (t--)
    {
        int n; in >> n;
        std::array<int, 101> values{}; // Use that 1 <= n <= 100, and 1 <= A_i <= n, initialized to 0.
        std::array<int, 101> types{};
        for (int i = 0; i < n; ++i) { in >> types[i]; }
        for (int i = 0; i < n; ++i)
        {
            int value; in >> value;
            values[types[i]] = std::max(values[types[i]], value);
        }
        out << std::accumulate(values.begin(), values.end(), 0) << '\n';
    }
    return 0;
}
