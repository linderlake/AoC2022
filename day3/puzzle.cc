#include "../AoCHelper/AoCHelper.h"
#include <vector>

int getPriorityLevel(char item)
{
    if (item >= 'a' && item <= 'z')
    {
        return int(item - 'a' + 1);
    }
    else if (item >= 'A' && item <= 'Z')
    {
        return int(item - 'A' + 27);
    }
    return 0;
}

void puzzle_one(std::vector<std::string> input)
{
    int answer{};
    for (std::string row : input)
    {
        std::vector<char> firstCompartment;
        std::vector<char> secondCompartment;
        for (int i = 0; i < row.size() / 2; i++)
        {
            firstCompartment.push_back(row[i]);
        }
        for (int i = row.size() / 2; i < row.size(); i++)
        {
            secondCompartment.push_back(row[i]);
        }
        for (int i = 0; i < firstCompartment.size(); i++)
        {
            if (std::any_of(secondCompartment.begin(), secondCompartment.end(), [&](char secondCompartmentItem)
                            { return secondCompartmentItem == firstCompartment[i]; }))
            {
                answer += getPriorityLevel(firstCompartment[i]);
                break; // Only one item can be duplicate.
            };
        }
    }

    std::cout << "Puzzle one: " << answer << std::endl;
}

void puzzle_two(std::vector<std::string> input)
{
    int answer{};

    for (int i = 0; i < input.size(); i += 3)
    {
        std::vector<char> firstElf;
        std::vector<char> secondElf;
        std::vector<char> thirdElf;
        for (int j = 0; j < input[i].size(); j++)
        {
            firstElf.push_back(input[i][j]);
        }
        for (int j = 0; j < input[i + 1].size(); j++)
        {
            secondElf.push_back(input[i + 1][j]);
        }
        for (int j = 0; j < input[i + 2].size(); j++)
        {
            thirdElf.push_back(input[i + 2][j]);
        }
        auto sameItem = std::find_if(firstElf.begin(), firstElf.end(), [&](char firstElfItem)
                                     { return std::any_of(secondElf.begin(), secondElf.end(), [&](char secondElfItem)
                                                          { return secondElfItem == firstElfItem; }) &&
                                              std::any_of(thirdElf.begin(), thirdElf.end(), [&](char thirdElfItem)
                                                          { return thirdElfItem == firstElfItem; }); });
        if (sameItem != firstElf.end())
        {
            answer += getPriorityLevel(*sameItem);
        }
    }

    std::cout << "Puzzle two: " << answer << std::endl;
}

int main()
{
    std::vector<std::string> exampleInput{"vJrwpWtwJgWrhcsFMMfFFhFp",
                                          "jqHRNqRjqzjGDLGLrsFMfFZSrLrFZsSL",
                                          "PmmdzqPrVvPwwTWBwg",
                                          "wMqvLMZHhHMvwLHjbvcjnnSBnvTQFn",
                                          "ttgJtRGJQctTZtZT",
                                          "CrZsJsPPZsGzwwsLwLmpwMDw"};
    AoCHelper a1{"2022", "3"};
    std::vector<std::string> result = a1.get_input();
    puzzle_one(result);
    puzzle_two(result);
}
