#include <vector>

#include "../AoCHelper/AoCHelper.h"

struct Knot {
  int x;
  int y;
};

bool isHeadAndTailTouching(Knot head, Knot tail) {
  if (head.x == tail.x && head.y == tail.y ||
      head.x == tail.x + 1 && head.y == tail.y ||
      head.x == tail.x - 1 && head.y == tail.y ||
      head.x == tail.x && head.y == tail.y + 1 ||
      head.x == tail.x && head.y == tail.y - 1 ||
      head.x == tail.x + 1 && head.y == tail.y + 1 ||
      head.x == tail.x - 1 && head.y == tail.y - 1 ||
      head.x == tail.x + 1 && head.y == tail.y - 1 ||
      head.x == tail.x - 1 && head.y == tail.y + 1) {
    return true;
  }
  return false;
}

void print2dMap(Knot head, Knot tail) {
  std::vector<std::vector<char>> map(35, std::vector<char>(35, '.'));
  map[head.y][head.x] = 'H';
  map[tail.y][tail.x] = 'T';
  for (int i = map.size() - 1; i >= 0; i--) {
    for (int j = map.size() - 1; j >= 0; j--) {
      std::cout << map[i][j] << " ";
    }
    std::cout << std::endl;
  }
  std::cout << std::endl;
}

// print all knots in vector on a 2d map
void print2dMap(Knot head, std::vector<Knot*>& knots) {
  std::vector<std::vector<char>> map(35, std::vector<char>(35, '.'));
  int x_offset = map.size() / 2;
  int y_offset = map.size() / 2;
  map[y_offset][x_offset] = 's';
  for (int i = knots.size() - 1; i >= 0; i--) {
    Knot* knot = knots[i];
    map[knot->y + y_offset][knot->x + x_offset] =
        std::to_string(i + 1).c_str()[0];
  }
  map[head.y + y_offset][head.x + x_offset] = 'H';
  for (int i = map.size() - 1; i >= 0; i--) {
    for (int j = 0; j < map.size(); j++) {
      std::cout << map[i][j] << " ";
    }
    std::cout << std::endl;
  }

  std::cout << std::endl;
}

// print tail map
void print2dmapTailMoves(std::vector<Knot>& tailMoves) {
  std::vector<std::vector<char>> map(35, std::vector<char>(35, '.'));
  int x_offset = map.size() / 2;
  int y_offset = map.size() / 2;
  for (int i = tailMoves.size() - 1; i >= 0; i--) {
    Knot knot = tailMoves[i];
    map[knot.y + y_offset][knot.x + x_offset] = '#';
  }
  map[y_offset][x_offset] = 's';
  for (int i = map.size() - 1; i >= 0; i--) {
    for (int j = 0; j < map.size(); j++) {
      std::cout << map[i][j] << " ";
    }
    std::cout << std::endl;
  }

  std::cout << std::endl;
}

bool isHeadAndTailOnSameRow(Knot head, Knot tail) {
  if (head.y == tail.y) {
    return true;
  }
  return false;
}

bool isHeadAndTailOnSameColumn(Knot head, Knot tail) {
  if (head.x == tail.x) {
    return true;
  }
  return false;
}

void registerMove(Knot& tail, std::vector<Knot>& tailMoves) {
  if (!std::any_of(tailMoves.begin(), tailMoves.end(),
                   [tail](Knot t) { return t.x == tail.x && t.y == tail.y; })) {
    tailMoves.push_back(tail);
  }
}

void puzzle_one(std::vector<std::string> input) {
  int answer{};
  Knot head{0, 0};
  Knot tail{0, 0};
  std::vector<Knot> tailMoves{tail};
  for (std::string row : input) {
    char moveDir = myLib::split(row, ' ')[0][0];
    int movePos = std::stoi(myLib::split(row, ' ')[1]);

    // move head
    switch (moveDir) {
      case 'R':
        head.x += movePos;
        break;
      case 'L':
        head.x -= movePos;
        break;
      case 'U':
        head.y += movePos;
        break;
      case 'D':
        head.y -= movePos;
        break;
    }

    if (!isHeadAndTailTouching(head, tail)) {
      while (!isHeadAndTailOnSameColumn(head, tail) &&
             !isHeadAndTailOnSameRow(head, tail) &&
             !isHeadAndTailTouching(head, tail)) {
        // move diagonally towards head
        if (head.x > tail.x && head.y > tail.y) {
          tail.x += 1;
          tail.y += 1;
        } else if (head.x > tail.x && head.y < tail.y) {
          tail.x += 1;
          tail.y -= 1;
        } else if (head.x < tail.x && head.y > tail.y) {
          tail.x -= 1;
          tail.y += 1;
        } else if (head.x < tail.x && head.y < tail.y) {
          tail.x -= 1;
          tail.y -= 1;
        }
        registerMove(tail, tailMoves);
      }
      if (isHeadAndTailOnSameRow(head, tail)) {
        while (!isHeadAndTailTouching(head, tail)) {
          if (head.x > tail.x) {
            tail.x += 1;
          } else {
            tail.x -= 1;
          }
          registerMove(tail, tailMoves);
        }
      } else if (isHeadAndTailOnSameColumn(head, tail)) {
        while (!isHeadAndTailTouching(head, tail)) {
          if (head.y > tail.y) {
            tail.y += 1;
          } else {
            tail.y -= 1;
          }
          registerMove(tail, tailMoves);
        }
      }
    }
    registerMove(tail, tailMoves);
  }
  answer = tailMoves.size();
  std::string coutAnswer =
      (answer == 6494) ? std::to_string(answer)
                       : "Error, wrong answer ❌. Should be 6494 but is " +
                             std::to_string(answer) + "";
  std::cout << "Puzzle one: " << coutAnswer << std::endl;
}

void puzzle_two(std::vector<std::string> input) {
  int answer{};
  Knot head{0, 0};
  Knot knot{0, 0};
  Knot knot2{0, 0};
  Knot knot3{0, 0};
  Knot knot4{0, 0};
  Knot knot5{0, 0};
  Knot knot6{0, 0};
  Knot knot7{0, 0};
  Knot knot8{0, 0};
  Knot knot9{0, 0};
  std::vector<Knot*> knots{&knot,  &knot2, &knot3, &knot4, &knot5,
                           &knot6, &knot7, &knot8, &knot9};
  std::vector<Knot> tailMoves{knot9};
  for (std::string row : input) {
    char moveDir = myLib::split(row, ' ')[0][0];
    int movePos = std::stoi(myLib::split(row, ' ')[1]);

    for (size_t i = 0; i < movePos; i++) {
      switch (moveDir) {
        case 'R':
          head.x++;
          break;
        case 'L':
          head.x--;
          break;
        case 'U':
          head.y++;
          break;
        case 'D':
          head.y--;
          break;
      }
      for (size_t i = 0; i < knots.size(); i++) {
        Knot* previousKnot{};
        if (i == 0) {
          previousKnot = &head;
        } else {
          previousKnot = knots[i - 1];
        }
        Knot* tail = knots[i];

        if (!isHeadAndTailTouching(*previousKnot, *tail)) {
          if (!isHeadAndTailOnSameColumn(*previousKnot, *tail) &&
              !isHeadAndTailOnSameRow(*previousKnot, *tail)) {
            // move diagonally towards previousKnot
            if (previousKnot->x > tail->x && previousKnot->y > tail->y) {
              tail->x += 1;
              tail->y += 1;
            } else if (previousKnot->x > tail->x && previousKnot->y < tail->y) {
              tail->x += 1;
              tail->y -= 1;
            } else if (previousKnot->x < tail->x && previousKnot->y > tail->y) {
              tail->x -= 1;
              tail->y += 1;
            } else if (previousKnot->x < tail->x && previousKnot->y < tail->y) {
              tail->x -= 1;
              tail->y -= 1;
            }
            if (i == 8) registerMove(knot9, tailMoves);
          }
          if (isHeadAndTailOnSameRow(*previousKnot, *tail) &&
              !isHeadAndTailTouching(*previousKnot, *tail)) {
            if (previousKnot->x > tail->x) {
              tail->x += 1;
            } else {
              tail->x -= 1;
            }
            if (i == 8) registerMove(knot9, tailMoves);

          } else if (isHeadAndTailOnSameColumn(*previousKnot, *tail) &&
                     !isHeadAndTailTouching(*previousKnot, *tail)) {
            if (previousKnot->y > tail->y) {
              tail->y += 1;
            } else {
              tail->y -= 1;
            }
            if (i == 8) registerMove(knot9, tailMoves);
          }
        }
        if (i == 8) registerMove(knot9, tailMoves);
      }
    }
  }
  answer = tailMoves.size();
  std::string coutAnswer =
      (answer == 2691) ? std::to_string(answer)
                       : "Error, wrong answer ❌. Should be 2691 but is " +
                             std::to_string(answer) + "";
  std::cout << "Puzzle two: " << coutAnswer << std::endl;
}

int main() {
  std::vector<std::string> exampleInput{"R 4", "U 4", "L 3", "D 1",
                                        "R 4", "D 1", "L 5", "R 2"};
  std::vector<std::string> exampleInput2{"R 5",  "U 8",  "L 8",  "D 3",
                                         "R 17", "D 10", "L 25", "U 20"};
  AoCHelper a1{"2022", "9"};
  std::vector<std::string> result = a1.get_input();
  puzzle_one(result);
  puzzle_two(result);
}
