/**
 * Codeforces 915 (Div 2), B.
 *
 * https://codeforces.com/contest/1905/problem/B
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
 * #tree #theory
 *
 * We can prove by induction that on any tree with K leaves, the answer is (K+1)/2
 * This can be proven by induction:
 * - For two leaves, the answer is clearly 1
 * - For three leaves, the answer is clearly 2
 * - For 4 or more leaves:
 *   - The graph either has a node with degree at least 4, or has at least 2 nodes with degree at least 3.
 *   - Choose a path that goes through the 4-degree node, or a path that goes through the path between the 2 3-degree node.
 *   - The resulting node will have at least 2 remaining edges -> not a leaf.
 *   - Therefore we reduced the number of leaves by 2 in one move.
 */
int main()
{
    int t; in >> t;
    while(t--)
    {
        int n; in >> n;
        VI deg(n, 0);
        for (int i = 0; i < n-1; ++i)
        {
            int a, b; in >> a >> b;
            ++deg[a-1];
            ++deg[b-1];
        }
        int leaves = 0;
        for (auto d: deg)
        {
            if (d == 1) ++leaves;
        }
        out << (leaves + 1) / 2 << '\n';
    }
}
