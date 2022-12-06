#include "../AoCHelper/AoCHelper.h"
#include <vector>

void puzzle_one(std::vector<std::string> input)
{
    int answer{0};
    for (std::string row : input)
    {
        for (size_t i = 0; i < row.size() + 3; i++)
        {

            std::vector<char> packets{row[i], row[i + 1], row[i + 2], row[i + 3]};
            bool unique{true};
            for (size_t j = 0; j <= 3; j++)
            {
                if (std::count(packets.begin(), packets.end(), packets[j]) > 1)
                {
                    unique = false;
                }
            }
            if (unique)
            {
                answer = i + 4;
                break;
            }
        }
    }
    std::cout << "Puzzle one: " << answer << std::endl;
}

void puzzle_two(std::vector<std::string> input)
{
    int answer{0};
    for (std::string row : input)
    {
        for (size_t i = 0; i < row.size() + 3; i++)
        {

            std::vector<char> packets;
            for (size_t j = 0; j <= 13; j++)
            {
                packets.push_back(row[i + j]);
            }
            bool unique{true};
            for (size_t j = 0; j <= 13; j++)
            {
                if (std::count(packets.begin(), packets.end(), packets[j]) > 1)
                {
                    unique = false;
                }
            }
            if (unique)
            {
                answer = i + 14;
                break;
            }
        }
    }
    std::cout << "Puzzle two: " << answer << std::endl;
}

int main()
{
    std::vector<std::string> exampleInput{"mjqjpqmgbljsphdztnvjfqwrcgsmlb"};
    AoCHelper a1{"2022", "6"};
    std::vector<std::string> result = a1.get_input();
    puzzle_one(result);
    puzzle_two(result);
}
