/**
 * Codeforces 915 (Div 2), C.
 *
 * https://codeforces.com/contest/1905/problem/C
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
 * #string #greedy
 *
 * The thing to notice here, is that the successive steps can be summarized in one step:
 * the original lexicographically largest subset will be reversed in the positions it occupies.
 *
 * Find the largest subset. If it is `n` long, then it will take `n-1` steps to reverse.
 * Except that if it starts with multiple copies of its largest letter, then those do not need to be rearranged.
 * E.g. `zzzaa` -> `azzza` -> `aazzz`, and we don't have to "fix" the 3 `z`s.
 * Thus, the answer is `n-k`, where `k` is the multiplicity of the first letter.
 */
int main()
{
    auto t = read<int>();
    while (t--)
    {
        auto n = read<int>();
        auto s = read<String>();
        // Find the largest substring greedily, store their indices.
        VI is{0}; // start with the first letter already there
        for (int i = 1; i < n; ++i)
        {
            while (!is.empty() && s[i] > s[is.back()])
            {
                is.pop_back();
            }
            is.push_back(i);
        }
        // Count the first letter's multiplicity
        int cnt = 0;
        for (auto i: is)
        {
            if (s[i] == s[is[0]]) ++cnt;
            else break;
        }
        // Does the reversal actually sort the string?
        for (int i = 0; i < SZ(is)-1-i; ++i)
        {
            std::swap(s[is[i]], s[is[SZ(is)-1-i]]);
        }
        out << (std::is_sorted(s.begin(), s.end()) ? SZ(is) - cnt : -1) << '\n';
    }
    return 0;
}
