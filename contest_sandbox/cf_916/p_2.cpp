// region Includes, macros, utility functions
#include <algorithm>
#include <iostream>
#include <vector>

//#define DO_DEBUG
#ifdef DO_DEBUG
    #define D(x) std::cout << x << '\n';
    #define D2(x, y) std::cout << x << y << '\n';
    #define D3(x, y, z) std::cout << x << y << z << '\n';
#else
    #define D(x)
    #define D2(x, y)
    #define D3(x, y, z)
#endif

#define in std::cin
#define out std::cout

#define LL int64_t
#define PII std::pair<int, int>
#define VI std::vector<int>
#define VLL std::vector<LL>
#define VPII std::vector<PII>
#define SZ(x) static_cast<int>((x).size())

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
// endregion Includes, macros, utility functions

int main()
{
    auto t = read<int>();
    while (t--)
    {
        int n, k; in >> n >> k;
        VI a(n);
        VI b(n);
        for (int i = 0; i < n; ++i)
        {
            in >> a[i];
        }
        for (int i = 0; i < n; ++i)
        {
            in >> b[i];
        }
        LL maxXp = 0ll;
        // What can he do with the first k quests?
        VLL aPartSum(n);
        aPartSum[0] = a[0];
        for (int i = 1; i < n; ++i) { aPartSum[i] = aPartSum[i-1] + a[i]; }

        VI bPartMax(n);
        bPartMax[0] = b[0];
        for (int i = 1; i < n; ++i) { bPartMax[i] = std::max(bPartMax[i-1], b[i]); }

        for (int i = 0; i < n && i+1 <= k; ++i)
        {
            LL xp = aPartSum[i]; // need to have played them at least once
            auto remainingGames = k - (i+1);
            xp += remainingGames * bPartMax[i];
            maxXp = std::max(maxXp, xp);
        }
        out << maxXp << '\n';
    }
    return 0;
}
