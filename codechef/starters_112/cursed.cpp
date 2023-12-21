/*
 * https://discuss.codechef.com/t/cursed-editorial/114754
 * 
 * For an array `A`, an index `i >= 1` is called cursed if `A_1 + A_2 + A_3 + ... + A_{i-1} >= A_i`.
 * You’re given an array `A`, which you can rearrange as you like.
 * What’s the minimum number of cursed indices attainable?
 */
#include <iostream>
#include <vector>
#include <algorithm>

#define in std::cin
#define out std::cout
#define LL int64_t
#define VLL std::vector<LL>
#define SZ(x) static_cast<int>((x).size())

/**
 * Notice that if a cursed index is followed by a non-cursed index, then they can be switched, and nothing changes.
 * Therefore, a minimum configuration can be reached with greedily choosing as many non-cursed numbers as possible:
 * the smallest A_i first, then the smallest one that is larger than A_i, the smallest one that is larger than the sum so far... etc.
 *
 * #greedy
 */
int main()
{
    int t; in >> t;
    while (t--)
    {
        int n; in >> n;
        VLL a(n);
        for (int i = 0; i < n; ++i) { in >> a[i]; }

        std::sort(a.begin(), a.end());
        LL partial_sum = 0;
        VLL good{};
        VLL bad{};
        for (const auto k: a)
        {
            if (k <= partial_sum)
            {
                bad.push_back(k);
            }
            else
            {
                good.push_back(k);
                partial_sum += k;
            }
        }

        out << bad.size() << '\n';
        out << good[0]; // There is guaranteed to be at least 1 good index.
        for (int i = 1; i < SZ(good); ++i)
        {
            out << ' ' << good[i];
        }
        for (auto b: bad) { out << ' ' << b; }
        out << '\n';
    }
    return 0;
}
