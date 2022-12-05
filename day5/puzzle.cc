#include "../AoCHelper/AoCHelper.h"
#include <vector>
#include <stack>

void puzzle_one(std::vector<std::string> &input)
{
    bool parseStacks{true};
    std::vector<std::stack<char>> stacks{};

    for (size_t i = 0; i <= 9; i++)
    {
        stacks.push_back(std::stack<char>()); // 0 will be unused
    }

    for (size_t rowIndex = 0; rowIndex < input.size(); rowIndex++)
    {
        std::string row = input[rowIndex];
        if (parseStacks)
        {
            if (row.find(" 1   2   3 ") == std::string::npos)
            {
                continue;
            }
            parseStacks = false;
            for (size_t i = 1; (i + 1) < row.size(); i += 4)
            {
                for (int j = rowIndex - 1; j >= 0; j--)
                {
                    if (input[j][i] != ' ')
                    {
                        stacks[(i / 4) + 1].push(input[j][i]);
                    }
                }
            }
        }

        else
        {
            if (row.find("move") == std::string::npos)
            {
                continue;
            }
            auto splitRow = (myLib::split(row, ' '));
            int amount = std::stoi(splitRow[1]);
            int from = std::stoi(splitRow[3]);
            int to = std::stoi(splitRow[5]);

            for (int i = 0; i < amount; i++)
            {
                stacks[to].push(stacks[from].top());
                stacks[from].pop();
            }
        }
    }
    std::string answer{};
    for (size_t i = 1; i <= 9; i++)
    {
        if (!stacks[i].empty())
        {
            answer.push_back(stacks[i].top());
        }
    }
    std::cout << "Puzzle one: " << answer << std::endl;
}

void puzzle_two(std::vector<std::string> &input)
{
    bool parseStacks{true};
    std::vector<std::stack<char>> stacks{};

    for (size_t i = 0; i <= 9; i++)
    {
        stacks.push_back(std::stack<char>()); // 0 will be unused
    }

    for (size_t rowIndex = 0; rowIndex < input.size(); rowIndex++)
    {
        std::string row = input[rowIndex];
        if (parseStacks)
        {
            if (row.find(" 1   2   3 ") == std::string::npos)
            {
                continue;
            }
            parseStacks = false;
            for (size_t i = 1; (i + 1) < row.size(); i += 4)
            {
                for (int j = rowIndex - 1; j >= 0; j--)
                {
                    if (input[j][i] != ' ')
                    {
                        stacks[(i / 4) + 1].push(input[j][i]);
                    }
                }
            }
        }
        else
        {
            if (row.find("move") == std::string::npos)
            {
                continue;
            }
            const auto splitRow = (myLib::split(row, ' '));
            const int amount = std::stoi(splitRow[1]);
            const int from = std::stoi(splitRow[3]);
            const int to = std::stoi(splitRow[5]);

            std::stack<char> tempStack{};
            for (int i = 0; i < amount; i++)
            {
                tempStack.push(stacks[from].top());
                stacks[from].pop();
            }
            for (int i = 0; i < amount; i++)
            {
                stacks[to].push(tempStack.top());
                tempStack.pop();
            }
        }
    }
    std::string answer{};
    for (size_t i = 1; i <= 9; i++)
    {
        if (!stacks[i].empty())
        {
            answer.push_back(stacks[i].top());
        }
    }
    std::cout << "Puzzle two: " << answer << std::endl;
}

int main()
{
    std::vector<std::string> exampleInput{
        "    [D]    ",
        "[N] [C]    ",
        "[Z] [M] [P]",
        " 1   2   3 ",
        "",
        "move 1 from 2 to 1",
        "move 3 from 1 to 3",
        "move 2 from 2 to 1",
        "move 1 from 1 to 2"

    };
    AoCHelper a1{"2022", "5"};
    std::vector<std::string> result = a1.get_input();
    puzzle_one(result);
    puzzle_two(result);
}
