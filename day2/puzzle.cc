#include "../AoCHelper/AoCHelper.h"
#include <vector>

void puzzle_one(std::vector<std::string> input)
{
    int answer{0};
    for (std::string row : input)
    {
        char enemyMove = row[0];
        char playerMove = row[2];
        const int rockBonusPoints = 1;
        const int paperBonusPoints = 2;
        const int scissorBonusPoints = 3;
        int bonusPoints = 0;

        enemyMove == 'A' ? enemyMove = 'R' : enemyMove == 'B' ? enemyMove = 'P'
                                                              : enemyMove = 'S';
        switch (playerMove)
        {
        case 'X':
            playerMove = 'R';
            bonusPoints = rockBonusPoints;
            break;
        case 'Y':
            playerMove = 'P';
            bonusPoints = paperBonusPoints;
            break;
        case 'Z':
            playerMove = 'S';
            bonusPoints = scissorBonusPoints;
            break;
        default:
            break;
        }
        if (enemyMove == playerMove)
        {
            // "Tie"
            answer += 3;
        }
        else if (enemyMove == 'R' && playerMove == 'P' || enemyMove == 'S' && playerMove == 'R' || enemyMove == 'P' && playerMove == 'S')
        {
            // "Player wins"
            answer += 6;
        }
        answer += bonusPoints;
    }

    std::cout << "Puzzle one: " << answer << std::endl;
}

void puzzle_two(std::vector<std::string> input)
{
    int answer{0};
    for (std::string row : input)
    {
        char enemyMove = row[0];
        char outcome = row[2];
        char playerMove{};
        const int rockBonusPoints = 1;
        const int paperBonusPoints = 2;
        const int scissorBonusPoints = 3;
        int bonusPoints = 0;

        enemyMove == 'A' ? enemyMove = 'R' : enemyMove == 'B' ? enemyMove = 'P'
                                                              : enemyMove = 'S';
        switch (outcome)
        {
        case 'X':
            //  need to lose
            playerMove = enemyMove == 'R' ? 'S' : enemyMove == 'P' ? 'R'
                                                                   : 'P';
            break;
        case 'Y':
            // need to draw
            playerMove = enemyMove;
            break;
        case 'Z':
            // need to win
            playerMove = enemyMove == 'R' ? 'P' : enemyMove == 'P' ? 'S'
                                                                   : 'R';
            break;
        default:
            break;
        }
        if (enemyMove == playerMove)
        {
            // "Tie"
            answer += 3;
        }
        else if (enemyMove == 'R' && playerMove == 'P' || enemyMove == 'S' && playerMove == 'R' || enemyMove == 'P' && playerMove == 'S')
        {
            // "Player wins"
            answer += 6;
        }
        bonusPoints = playerMove == 'R' ? rockBonusPoints : playerMove == 'P' ? paperBonusPoints
                                                                              : scissorBonusPoints;
        answer += bonusPoints;
    }
    std::cout << "Puzzle two: " << answer << std::endl;
}

int main()
{
    std::vector<std::string> exampleInput{"A Y", "B X", "C Z"};
    AoCHelper a1{"2022", "2"};
    std::vector<std::string> result = a1.get_input();
    puzzle_one(result);
    puzzle_two(result);
}
