/**
 * Codeforces 915 (Div 2), Problem A
 *
 * https://codeforces.com/contest/1905/problem/A
 */

// region Includes, macros, utility functions
#include <algorithm>
#include <iostream>
#include <vector>

#define in std::cin
#define out std::cout

using String = std::string;
using Strings = std::vector<String>;

template<typename T> T read() { T t; in >> t; return t; }

template<typename T>
std::tuple<int, std::vector<T>> readVector()
{
    auto n = read<int>();
    std::vector<T> values(n);
    for (auto& v: values) { in >> v; }
    return std::tie(n, values);
}

#define SZ(x) static_cast<int>((x).size())
#define VI std::vector<int>
#define PII std::pair<int, int>
#define VPII std::vector<PII>
// endregion Includes, macros, utility functions

/**
 * Solution
 *
 * After understanding the problem we can see that the answer is `max(n, m)`.
 */
int main()
{
    int t; in >> t;
    while (t--)
    {
        int n, m; in >> n >> m;
        out << std::max(n, m) << '\n';
    }
    return 0;
}
