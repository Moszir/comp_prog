// region Includes, macros, utility functions
#include <algorithm>
#include <iostream>
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
    while (t--)
    {
        int n; in >> n;
        std::array<
            std::vector<std::pair<LL, int>>,
            3> a;
        for (int i = 0; i < 3; ++i)
        {
            a[i].resize(n);
            for (int j = 0; j < n; ++j)
            {
                in >> a[i][j].first;
                a[i][j].second = j;
            }
            std::sort(a[i].begin(), a[i].end(), [](const auto& lhs, const auto& rhs){ return lhs.first > rhs.first; });
        }

        auto select = [&a](int i1, int i2, int i3)
        {
            const auto& a1 = a[i1];
            const auto& a2 = a[i2];
            const auto& a3 = a[i3];
            LL sum = a1[0].first;
            const auto a1i = a1[0].second;
            int a2i;
            if (a2[0].second == a1i) {
                a2i = a2[1].second;
                sum += a2[1].first;
            }
            else {
                a2i = a2[0].second;
                sum += a2[0].first;
            }

            if (a3[0].second != a1i && a3[0].second != a2i) { sum += a3[0].first; }
            else if (a3[1].second != a1i && a3[1].second != a2i) { sum += a3[1].first; }
            else { sum += a3[2].first; }
            return sum;
        };

        LL r = 0ll;
        r = std::max(r, select(0, 1, 2));
        r = std::max(r, select(0, 2, 1));
        r = std::max(r, select(1, 0, 2));
        r = std::max(r, select(1, 2, 0));
        r = std::max(r, select(2, 0, 1));
        r = std::max(r, select(2, 1, 0));

        out << r << '\n';
    }
    return 0;
}
