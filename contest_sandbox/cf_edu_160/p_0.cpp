// region Includes, macros, utility functions
#include <algorithm>
#include <iostream>
#include <vector>
#include <string>

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
#define LL int64_t
#define VI std::vector<int>
#define PII std::pair<int, int>
#define VPII std::vector<PII>
// endregion Includes, macros, utility functions

int main()
{
    auto t = read<int>();
    while (t--)
    {
        std::string s;
        in >> s;
        bool found = false;
        for (int i = 0; i < s.size()-1; ++i)
        {
            if (s[i+1] == '0') continue;
            LL a = std::stoll(s.substr(0, i+1));
            LL b = std::stoll(s.substr(i+1));
            if (a < b)
            {
                out << a << ' ' << b << '\n';
                found = true;
                break;
            }
        }
        if (!found) out << "-1\n";
    }
    return 0;
}
