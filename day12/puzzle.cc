#include "../AoCHelper/AoCHelper.h"
#include <vector>
#include <queue>

struct square
{
    char height;
    bool visited{false};
    bool isEnd{false};
    std::vector<square *> neighbours;
};


void puzzle_one(std::vector<std::string> input)
{
    int answer{};
    std::vector<std::vector<square>> squareMap;
    square *start;
    for (int i = 0; i < input.size(); ++i)
        std::string row = input[i];
    {
        std::vector<square> squares;
        for (int j = 0; j < row.size(); ++j)
        {
            char c = row[j];
            square s;
            if (c == 'S')
            {
                start = &s;
            }
            if (c == 'E')
            {
                s.isEnd = true;
                s.height = 'z';
            }
            else
            {
                s.height = c;
            }
            squares.push_back(s);
           
        }
        squareMap.push_back(squares);
    }

    // find neighbours
    for (int i = 0; i < squareMap.size(); ++i)
    {
        for (int j = 0; j < squareMap[i].size(); ++j)
        {
            square *s = &squareMap[i][j];
            if (i > 0)
            {
                s->neighbours.push_back(&squareMap[i - 1][j]);
            }
            if (i < squareMap.size() - 1)
            {
                s->neighbours.push_back(&squareMap[i + 1][j]);
            }
            if (j > 0)
            {
                s->neighbours.push_back(&squareMap[i][j - 1]);
            }
            if (j < squareMap[i].size() - 1)
            {
                s->neighbours.push_back(&squareMap[i][j + 1]);
            }
        }
    }

    std::queue<square *> q;
    q.push(start);
    while (!q.empty())
    {
        square *s = q.front();
        q.pop();
        if (s->visited)
            continue;
        s->visited = true;
        if (s->isEnd)
        {
            break;
        }
        for (square *n : s->neighbours)
        {
            if (n->height >= (s->height + 1))
            {
                q.push(n);
            }
        }
    }

    std::cout << "Puzzle one: " << answer << std::endl;
}

void puzzle_two(std::vector<std::string> input)
{
    int answer{};
    for (std::string row : input)
    {
    }
    std::cout << "Puzzle two: " << answer << std::endl;
}

int main()
{
    std::vector<std::string> exampleInput{
        "Sabqponm",
        "abcryxxl",
        "accszExk",
        "acctuvwj",
        "abdefghi"};
    AoCHelper a1{"2022", "12"};
    std::vector<std::string> result = a1.get_input();
    puzzle_one(result);
    puzzle_two(result);
}
