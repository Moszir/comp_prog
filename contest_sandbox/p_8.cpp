// region Includes, macros, utility functions
#include <algorithm>
#include <iostream>
#include <vector>

#define FROM_FILE
#ifdef FROM_FILE
    #include <fstream>
    const auto thisFile = std::string(__FILE__);
    std::ifstream inputFile(std::string(__FILE__).replace(thisFile.size()-3, 3, "txt"));
    #define in inputFile
    #define D(x) std::cout << x << '\n';
    #define D2(x, y) std::cout << x << y << '\n';
    #define D3(x, y, z) std::cout << x << y << z << '\n';
#else
    #define in std::cin
    #define D(x)
    #define D2(x, y)
    #define D3(x, y, z)
#endif
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

int main()
{
    auto t = read<int>();
    while (t--)
    {
//        auto [n, a] = readVector<i64>();
    }
    return 0;
}
