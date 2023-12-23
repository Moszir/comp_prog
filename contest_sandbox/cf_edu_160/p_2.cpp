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
#define LL int64_t
// endregion Includes, macros, utility functions

int main()
{
    auto t = read<int>();
    std::array<int, 30> have{};
    while (t--)
    {
        int typ; LL what; in >> typ >> what;
        if (typ == 1) // ADD
        {
            ++have[what];
        }
        else // 2 GET
        {
            bool canDo = true;
            auto h = have;
            int i = 0;
//            for (auto g: h) out << g << ' ';
//            out << '\n';
            while (what > 0)
            {
                D2("what ", what)
                if (what % 2 == 1)
                {
                    auto j = i; D2("j", j)
                    int needs = 1;
                    while (needs > 0 && j >= 0)
                    {
                        D2("needs ", needs)
                        if (h[j] >= needs)
                        {
                            h[j] -= needs;
                            needs = 0;
                            break;
                        }
                        else
                        {
                            needs -= h[j];
                            h[j] = 0;
                            needs *= 2;
                            --j;
                        }
                    }
                    if (needs > 0)
                    {
                        canDo = false;
                        break;
                    }
                }
                ++i;
                what /= 2;
            }
            out << (canDo ? "YES" : "NO") << '\n';
        }
    }
    return 0;
}
