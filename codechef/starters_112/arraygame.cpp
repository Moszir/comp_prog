/**
 * https://www.codechef.com/problems/ARRAYGAME
 *
 * Alice and Bob play a game on array `A`, taking turns alternating moves. Alice goes first.
 * Alice also has a sequence `B`, initially empty.
 * Alice deletes an element from `A` and appends it to `B` on her turn.
 * Bob just deletes an element from `A`.
 * Alice must ensure that `B` is always sorted.
 * You’re also given `S \in {0, 1}`, Alice is allowed to skip her move if `S = 1`, and can’t if `S = 0`.
 * What’s the maximum `sum(B)` that Alice can attain, if Bob is playing to minimize it?
 */
#include <algorithm>
#include <iostream>
#include <numeric>
#include <vector>

#define LL int64_t
#define VLL std::vector<LL>
#define IN std::cin >>
#define OUT std::cout <<

/**
 * S = 0
 * - Sort the array
 * - In the odd N case Alice has to take the smallest (N+1)/2 elements
 *   - Otherwise Bob just always takes the highest available element, and Alice would have to break the rule -> 0.
 * - If N is even, then Alice can disregard the smallest element, and play it on A[1:]
 *
 * S = 1
 * - Sort the array
 * - Alice has a strategy for every k = 1 .. (N+1) / 2 for taking exactly k element:
 *   - 1: take the largest, "a[-1]", and then skip
 *   - 2: take a[-3], Bob takes a[-1], Alice takes a[-2], and then skip
 *   - 3: similarly a[-5, -4, -3] while Bob takes a[-1, -2]
 *   - and so on.
 * - This is basically playing the S = 0 game on the largest m numbers, where m is odd.
 */
int main()
{
    int t, s; IN t >> s;
    while (t--)
    {
        int n; IN n;
        VLL a(n);
        for (int i = 0u; i < n; ++i) IN a[i];
        std::sort(a.begin(), a.end());

        const bool even = (n % 2 == 0);
        const auto middle = a.begin() + n / 2 + 1;
        LL best = std::accumulate(a.begin() + (even ? 1 : 0), middle, 0ll); // solution for S = 0, base case for S = 1.

        if (s == 1)
        {
            // stones == 1: take last one
            int alice = n-1;
            int bob = n; // past the end
            LL sum = a[n-1];
            best = std::max(best, sum);

            // stones == 2: take -3, -2 (Bob takes -1)
            // stones == 3: take -5, -4, -3 (Bob takes -2, -1)
            // Generally, Alice takes two smaller stones, while Bob takes away the largest stone.
            while (alice >= 2)
            {
                sum -= a[--bob];
                sum += a[--alice];
                sum += a[--alice];
                best = std::max(best, sum);
            }
        }
        OUT best << '\n';
    }
    return 0;
}

/**
 * Tests
 *
 * S = 0
 * 10 1 2 -> 3 (Alice chooses 1, Bob 10, Alice 2)
 * 1 2 -> 2 (Alice chooses 2)
 *
 * S = 1
 * 10 1 2 -> 10 (Alice chooses 10, skips other)
 * 1 1 1 1 1 1 1 1 8 9 10 -> 17 (A 8, B 10, A 9, skips rest)
 * 2 3 4 4 5 -> 9 (2+3+4 > 4+4 > 5)
 */
