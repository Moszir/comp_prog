#include <array>
#include <iostream>
#include <fstream>
#include <string>

#define SZ(v) (static_cast<int>(v.size()))


struct Number
{
    char digit;
    std::string name;
    int value;
};

std::array<Number, 9> numbers
{{
    {'1', "one", 1},
    {'2', "two", 2},
    {'3', "three", 3},
    {'4', "four", 4},
    {'5', "five", 5},
    {'6', "six", 6},
    {'7', "seven", 7},
    {'8', "eight", 8},
    {'9', "nine", 9},
}};

int processLine(const std::string_view& line, const bool useStrings = false)
{
    int first = -1;
    int last = -1;
    for (int i = 0; i < SZ(line); ++i)
    {
        for (const auto& number: numbers)
        {
            if (line[i] == number.digit || (useStrings && line.substr(i).starts_with(number.name)))
            {
                if (first == -1)
                {
                    first = number.value;
                }
                last = number.value;
            }
        }
    }
    return 10*first + last;
}

int processFile(const std::string& fileName, const bool useStrings)
{
    std::ifstream in(fileName);
    std::string s;
    int sum = 0;
    while (in >> s)
    {
        sum += processLine(s, useStrings);
    }
    return sum;
}

int main()
{
    std::cout
        << processFile("example.txt", false) << '\n' // 142
        << processFile("input.txt", false) << '\n' // 55'538
        << processFile("example_b.txt", true) << '\n' // 281
        << processFile("input.txt", true) << '\n'; // 54'875
    return 0;
}
