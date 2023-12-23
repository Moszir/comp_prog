// region Includes, macros, utility functions
#include <algorithm>
#include <array>
#include <iostream>
#include <numeric>
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

#define IN std::cin >>
#define OUT std::cout <<

#define LL int64_t
#define PII std::pair<int, int>
#define VI std::vector<int>
#define VLL std::vector<LL>
#define VPII std::vector<PII>
#define SZ(x) static_cast<int>((x).size())

template<typename T>
std::tuple<int, std::vector<T>> readVector()
{
    int n; IN n;
    std::vector<T> values(n);
    for (auto& v: values) { IN v; }
    return std::tie(n, values);
}
// endregion Includes, macros, utility functions

int main()
{
    int t; IN t;
    while (t--)
    {
//        auto [n, a] = readVector<LL>();
    }
    return 0;
}
