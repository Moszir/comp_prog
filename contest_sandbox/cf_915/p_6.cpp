// CF 915 D: Mex cycling

#include <algorithm>
#include <deque>
#include <iostream>
#include <vector>

//#define FROM_FILE

// region Macros and Helpers
#ifdef FROM_FILE
    #include <fstream>

    const auto thisFile = std::string(__FILE__);
    std::ifstream inputFile(std::string(__FILE__).replace(thisFile.size()-3, 3, "txt"));
    #define in inputFile
#else
    #define in std::cin
#endif
#define out std::cout

#define SZ(x) static_cast<int>((x).size())
#define LL long long
#define VI std::vector<int>
#define PII std::pair<int, int>
#define PLL std::pair<LL, LL>
#define VPII std::vector<PII>
#define VPLL std::vector<PLL>
using String = std::string;
using Strings = std::vector<String>;

template<typename T> T read() { T t; in >> t; return t; }

template<typename T>
std::tuple<LL, std::vector<T>> readVector()
{
    auto n = read<LL>();
    std::vector<T> values(n);
    for (auto& v: values) { in >> v; }
    return std::tie(n, values);
}


int main()
{
    auto t = read<int>();
    while (t--)
    {
        auto [n, a] = readVector<LL>();
        std::deque<PLL> dq;
        LL currentSum = 0;
        auto push = [&dq, &currentSum](LL value, LL rep){ dq.emplace_back(value, rep); currentSum += value * rep; };

        {
            LL missing = 0;
            VI seen(n + 1);
            for (LL i = 0; i < n; ++i)
            {
                ++seen[a[i]];
                while (seen[missing]) { ++missing; }
                push(missing, 1);
            }
        }

        long long best = currentSum;
        for (LL i = 0; i < n-1; ++i)
        {
            currentSum -= dq.front().first;
            if (--dq.front().second == 0) { dq.pop_front(); }

            // Those at the end of the deque that are missing at least a[i] will now miss a[i] instead.
            LL tail = 0;
            while (!dq.empty() && dq.back().first >= a[i])
            {
                tail += dq.back().second;
                currentSum -= dq.back().first * dq.back().second;
                dq.pop_back();
            } // Pop them...
            push(a[i], tail);
            push(n, 1);
            best = std::max(best, currentSum);
        }
        out << best << '\n';
    }
    return 0;
}
