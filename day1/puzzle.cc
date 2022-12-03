#include "../AoCHelper/AoCHelper.h"
#include <vector>

void puzzle_one(std::vector<std::string> input)
{
    std::vector<int> calories{};
    int currentElfCalorie{0};
    for (std::string row : input)
    {
        if (row == "")
        {
            // next elf
            calories.push_back(currentElfCalorie);
            currentElfCalorie = 0;
        }
        else
        {
            currentElfCalorie = currentElfCalorie + std::stoi(row);
        }
    }
    std::sort(calories.begin(), calories.end());
    int answer{calories.back()};
    std::cout << "Puzzle one: " << answer << std::endl;
}

void puzzle_two(std::vector<std::string> input)
{

    std::vector<int> calories{};
    int currentElfCalorie{0};
    for (std::string row : input)
    {
        if (row == "")
        {
            // next elf
            calories.push_back(currentElfCalorie);
            currentElfCalorie = 0;
        }
        else
        {
            currentElfCalorie = currentElfCalorie + std::stoi(row);
        }
    }
    std::sort(calories.begin(), calories.end(), std::greater<int>());
    int answer{calories.at(0) + calories.at(1) + calories.at(2)};
    std::cout << "Puzzle two: " << answer << std::endl;
}

int main()
{
    std::vector<std::string> exampleInput{"", "", "", "", ""};
    AoCHelper a1{"2022", "1"};
    std::vector<std::string> result = a1.get_input();
    puzzle_one(result);
    puzzle_two(result);
}
