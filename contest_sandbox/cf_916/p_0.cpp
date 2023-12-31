// region Includes, macros, utility functions
#include <algorithm>
#include <iostream>
#include <string>
#include <vector>
#include <array>

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
    std::array<int, 26> s{};
    while (t--)
    {
        s.fill(0);
        int n; in >> n;
        for (int i = 0; i < n; ++i)
        {
            char c; in >> c; ++s[c-'A'];
        }
        int cnt = 0;
        for (int i = 0; i < 26; ++i)
        {
            if (s[i] > i) ++cnt;
        }
        out << cnt << '\n';
    }
    return 0;
}
