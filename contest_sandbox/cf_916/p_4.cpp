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
        int n; in >> n;
        VLL a(n);
        VLL b(n);
        for (int i = 0; i < n; ++i) { in >> a[i]; }
        for (int i = 0; i < n; ++i) { in >> b[i]; }
        struct C { LL alice; LL bob; LL relative; };
        std::vector<C> c(n);
        for (int i = 0; i < n; ++i)
        {
            c[i].alice = a[i]-1;
            c[i].bob = b[i]-1;
            c[i].relative = c[i].alice + c[i].bob;
        }
//        for (int i = 0; i < n; ++i)
//        {
//            out << c[i].alice << ' ' << c[i].relative << '\n';
//        }
        std::sort(c.begin(), c.end(), [](const C& lhs, const C& rhs){ return lhs.relative > rhs.relative; });
//        for (int i = 0; i < n; ++i)
//        {
//            out << c[i].alice << ' ' << c[i].relative << '\n';
//        }
        LL sum = 0;
        for (int i = 0; i < n; ++i)
        {
            if (i % 2 == 0) sum += c[i].alice;
            else sum -= c[i].bob;
        }
        out << sum << '\n';
    }
    return 0;
}
