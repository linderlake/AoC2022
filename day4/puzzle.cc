#include "../AoCHelper/AoCHelper.h"
#include <vector>

std::vector<std::string> split(const std::string &s, char delimiter)
{
    std::vector<std::string> tokens;
    std::string token;
    std::istringstream tokenStream(s);
    while (std::getline(tokenStream, token, delimiter))
    {
        tokens.push_back(token);
    }
    return tokens;
}

void puzzle_one(std::vector<std::string> input)
{
    int answer{};
    for (std::string row : input)
    {
        std::vector<std::string> elfs = split(row, ',');
        std::string firstElf = elfs[0];
        std::string secondElf = elfs[1];
        int firstElfStart{std::stoi(split(firstElf, '-')[0])};
        int firstElfEnd{std::stoi(split(firstElf, '-')[1])};
        int secondElfStart{std::stoi(split(secondElf, '-')[0])};
        int secondElfEnd{std::stoi(split(secondElf, '-')[1])};

        if (firstElfStart <= secondElfStart && firstElfEnd >= secondElfEnd)
        {
            answer++;
        }
        else if (secondElfStart <= firstElfStart && secondElfEnd >= firstElfEnd)
        {
            answer++;
        }
    }
    std::cout << "Puzzle one: " << answer << std::endl;
}

void puzzle_two(std::vector<std::string> input)
{
    int answer{};
    for (std::string row : input)
    {
        std::vector<std::string> elfs = split(row, ',');
        std::string firstElf = elfs[0];
        std::string secondElf = elfs[1];
        int firstElfStart{std::stoi(split(firstElf, '-')[0])};
        int firstElfEnd{std::stoi(split(firstElf, '-')[1])};
        int secondElfStart{std::stoi(split(secondElf, '-')[0])};
        int secondElfEnd{std::stoi(split(secondElf, '-')[1])};
        if (firstElfStart >= secondElfStart && firstElfStart <= secondElfEnd)
        {
            answer++;
        }
        else if (secondElfStart >= firstElfStart && secondElfStart <= firstElfEnd)
        {
            answer++;
        }
    }

    std::cout << "Puzzle two: " << answer << std::endl;
}

int main()
{
    std::vector<std::string> exampleInput{"2-4,6-8",
                                          "2-3,4-5",
                                          "5-7,7-9",
                                          "2-8,3-7",
                                          "6-6,4-6",
                                          "2-6,4-8"};
    AoCHelper a1{"2022", "4"};
    std::vector<std::string> result = a1.get_input();
    puzzle_one(result);
    puzzle_two(result);
}
