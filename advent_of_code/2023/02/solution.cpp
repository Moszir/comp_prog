#include <fstream>
#include <iostream>

#include "moszir_lib/string/string_vector.hpp"

struct Cubes
{
    int greens = 0;
    int reds = 0;
    int blues = 0;
    [[nodiscard]] int power() const { return greens * reds * blues; }
};

using StringVector = moszir::StringVector;

void solve(const std::string &fileName)
{
    std::ifstream in(fileName);
    int solutionA = 0;
    int solutionB = 0;
    for (int gameId = 1; in.good(); ++gameId)
    {
        StringVector game(in, ":;");
        if (game.empty()) { break; }

        Cubes cubes;
        for (uint32_t i = 1u; i < game.size(); ++i)  // ignore the starting "Game 13" part
        {
            StringVector cubesDescription(game[i], ", ");
            for (uint32_t j = 0u; j < cubesDescription.size(); j += 2)
            {
                const auto &color = cubesDescription[j + 1u];
                const auto number = std::stoi(cubesDescription[j]);
                auto &store = (color == "green" ? cubes.greens : color == "red" ? cubes.reds : cubes.blues);
                store = std::max(store, number);
            }
        }

        if (cubes.reds <= 12 && cubes.greens <= 13 && cubes.blues <= 14)
        {
            solutionA += gameId;
        }
        solutionB += cubes.power();
    }

    std::cout << fileName << ": " << solutionA << ", " << solutionB << '\n';
}

int main()
{
    solve("example.txt");
    solve("input.txt");
    return 0;
}
