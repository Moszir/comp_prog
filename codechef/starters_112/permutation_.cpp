/**
 * https://www.codechef.com/problems/PERMUTATION_
 *
 * Given `N` and `X`, construct a permutation `P` of `{1, 2, ..., N}` such that:
 *
 * `P_1 = X` and
 * The array of differences `D` is a palindrome, where `D_i = P_{i+1} - P_{i}`
 */
#include <iostream>

#define in std::cin
#define out std::cout

/**
 * The following will work (note that N-X+1 is the symmetric element to X in 1..N):
 * - If X > (n+1) / 2:
 *   - X, X+1, ..., n, X-1, ..., n-X+2, 1, ..., N-X+1
 * - If X < (n+1) / 2:
 *   - X, X-1, ..., 1, X+1, ..., N-X, N, ..., N-X+1
 * - If X == (N+1) / 2:
 *   - Impossible, (N+1)/2 needs to be the middle element in every such permutation.
 *
 * Some more theory for that last part, and something that can help give constructions.
 * Take the cas of an odd N.
 * Then there is a middle element p := P_{(N+1) / 2}
 * As the differences around p are symmetrical, its 2 neighbors will be symmetrical to p (p-d and p+d).
 * Furthermore, its second neighbors are symmetrical to p too: p-d1-d2 and p+d1+d2.
 * And so on.
 * In particular, this means that half of the rest of the numbers are larger than p, and half of them are smaller.
 * Only (N+1)/2 satisfies that.
 *
 * For the case of an even N, we can imagine adding an extra element in the middle of the 2 middle elements of the permutation.
 * Then with the same argument we can see that that middle element will be `(N+1)/2`, and `P_i` and `P_{n-i+1}` are symmetrical.
 *
 * #constructive #permutation
 */
int main()
{
    int t; in >> t;
    while (t--)
    {
        int n, x; in >> n >> x;
        if (n % 2 == 1 && x == n/2 + 1) { out << "-1\n"; }
        else
        {
            auto middle = n/2;
            out << x;
            if (x <= middle)
            {
                for (int k = x-1; k >= 1; --k) { out << ' ' << k; }
                for (int k = x+1; k <=n-x; ++k) { out << ' ' << k; }
                for (int k = n; k > n-x; --k) { out << ' ' << k; }
            }
            else
            {
                for (int k = x+1; k <= n; ++k) { out << ' ' << k; }
                for (int k = x-1; k > n-x+1; --k) { out << ' ' << k; }
                for (int k = 1; k <= n-x+1; ++k) { out << ' ' << k; }
            }
            out << '\n';
        }
    }
    return 0;
}
