#include "../AoCHelper/AoCHelper.h"
#include <vector>

bool go_up(std::vector<std::vector<int>> input, int height, int x, int y, int &steps)
{
    if (y == 0)
    {
        return true;
    }
    if (input[y - 1][x] >= height)
    {
        steps++;
        return false;
    }
    steps++;
    return go_up(input, height, x, y - 1, steps);
}

bool go_left(std::vector<std::vector<int>> input, int height, int x, int y, int &steps)
{
    if (x == 0)
    {
        return true;
    }
    if (input[y][x - 1] >= height)
    {
        steps++;
        return false;
    }
    steps++;
    return go_left(input, height, x - 1, y, steps);
}

bool go_right(std::vector<std::vector<int>> input, int height, int x, int y, int &steps)
{
    if (x == input[y].size() - 1)
    {
        return true;
    }
    if (input[y][x + 1] >= height)
    {
        steps++;
        return false;
    }
    steps++;
    return go_right(input, height, x + 1, y, steps);
}

bool go_down(std::vector<std::vector<int>> input, int height, int x, int y, int &steps)
{
    if (y == input.size() - 1)
    {
        return true;
    }
    if (input[y + 1][x] >= height)
    {
        steps++;
        return false;
    }
    steps++;
    return go_down(input, height, x, y + 1, steps);
}

void puzzle(std::vector<std::string> rawInput)
{
    std::vector<std::vector<int>> input;
    size_t highestScenicScore{};

    for (std::string row : rawInput)
    {
        std::vector<int> temp;
        for (char c : row)
        {
            temp.push_back(c - '0');
        }
        input.push_back(temp);
    }

    int answer{(input.size() * 2) + ((input[0].size() - 2) * 2)};

    for (int i = 1; i < input.size() - 1; i++)
    {
        for (int j = 1; j < input[i].size() - 1; j++)
        {
            int currentHeight = input[i][j];
            int steps_up{};
            int steps_down{};
            int steps_left{};
            int steps_right{};
            bool canGoUp = go_up(input, currentHeight, j, i, steps_up);
            bool canGoDown = go_down(input, currentHeight, j, i, steps_down);
            bool canGoLeft = go_left(input, currentHeight, j, i, steps_left);
            bool canGoRight = go_right(input, currentHeight, j, i, steps_right);
            if (canGoDown || canGoLeft || canGoRight || canGoUp)
            {
                answer++;
            }
            size_t scenicScore = steps_up * steps_down * steps_left * steps_right;
            if (scenicScore > highestScenicScore)
            {
                highestScenicScore = scenicScore;
            }
        }
    }
    std::cout << "Puzzle one: " << answer << std::endl;
    std::cout << "Puzzle two: " << highestScenicScore << std::endl;
}

int main()
{
    std::vector<std::string> exampleInput{"30373",
                                          "25512",
                                          "65332",
                                          "33549",
                                          "35390"};
    AoCHelper a1{"2022", "8"};
    std::vector<std::string> result = a1.get_input();
    puzzle(result);
}
