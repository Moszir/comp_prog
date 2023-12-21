/**
 * https://www.codechef.com/problems/LOGICIAN
 *
 * $N$ logicians walk into a bar. You know, for each one, whether they want a beer or not — this information is encoded in binary string $S$.
 * The bartender asks them, “Does everyone want a beer?”
 * The logicians reply to this in order, with their only information being knowledge of their own choice and the replies
 * of the people ahead of them.
 * Can you predict all their replies?
 */

#include <iostream>

#define in std::cin
#define out std::cout

/**
 * If someone is a NO, then they are a NO, and everyone after them is also a NO.
 * If someone is a YES, and everyone before them was an IDK, then they are also IDK, unless they are the last person,
 * in which case they are a YES.
 */
int main()
{
    int t; in >> t;
    while (t--)
    {
        int n; in >> n;
        std::string s; in >> s;
        bool someoneSaidNo = false;
        for (uint32_t i = 0u; i < s.size(); ++i)
        {
            if (s[i] == '0') { someoneSaidNo = true; }
            out << (someoneSaidNo ? "NO" : (i == s.size()-1u ? "YES" : "IDK")) << '\n';
        }
    }
    return 0;
}

/**
Testcases

- Case 1
3
111

IDK
IDK
YES

- Case 2
4
1101

IDK
IDK
NO
NO

 */
