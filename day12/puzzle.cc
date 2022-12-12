#include <queue>
#include <vector>

#include "../AoCHelper/AoCHelper.h"

struct square {
  char height{};
  bool visited{false};
  bool isEnd{false};
  std::vector<square *> neighbours{};
  square *previous{nullptr};
};

int bfs(square *start) {
  std::queue<square *> q;
  q.push(start);
  start->visited = true;
  while (!q.empty()) {
    square *s = q.front();
    q.pop();
    if (s->isEnd) {
      int answer{};
      while (s->previous != nullptr) {
        ++answer;
        s = s->previous;
      }
      return answer;
    }
    for (square *n : s->neighbours) {
      if (!n->visited) {
        n->visited = true;
        n->previous = s;
        q.push(n);
      }
    }
  }
  return INT_MAX;
}

void parseNeighbours(std::vector<std::vector<square *>> &squareMap) {
  for (int i = 0; i < squareMap.size(); ++i) {
    for (int j = 0; j < squareMap[i].size(); ++j) {
      square *s = squareMap[i][j];
      if (i > 0 && (squareMap[i - 1][j]->height) <= (s->height + 1)) {
        s->neighbours.push_back(squareMap[i - 1][j]);
      }
      if (i < squareMap.size() - 1 &&
          (squareMap[i + 1][j]->height) <= (s->height + 1)) {
        s->neighbours.push_back(squareMap[i + 1][j]);
      }
      if (j > 0 && (squareMap[i][j - 1]->height) <= (s->height + 1)) {
        s->neighbours.push_back(squareMap[i][j - 1]);
      }
      if (j < squareMap[i].size() - 1 &&
          (squareMap[i][j + 1]->height) <= (s->height + 1)) {
        s->neighbours.push_back(squareMap[i][j + 1]);
      }
    }
  }
}

void resetNeighbours(std::vector<std::vector<square *>> &squareMap) {
  for (int i = 0; i < squareMap.size(); ++i) {
    for (int j = 0; j < squareMap[i].size(); ++j) {
      square *s = squareMap[i][j];
      s->visited = false;
      s->previous = nullptr;
    }
  }
}

void delete_squareMap(std::vector<std::vector<square *>> &squareMap) {
  for (int i = 0; i < squareMap.size(); ++i) {
    for (int j = 0; j < squareMap[i].size(); ++j) {
      delete squareMap[i][j];
    }
  }
}

void puzzle_one(std::vector<std::string> input) {
  int answer{};
  square *start;
  std::vector<std::vector<square *>> squareMap;
  for (int i = 0; i < input.size(); ++i) {
    std::string row = input[i];
    std::vector<square *> squares;
    for (int j = 0; j < row.size(); ++j) {
      char c = row[j];
      square *s = new square();
      if (c == 'S') {
        s->height = 'a';
        start = s;
      } else if (c == 'E') {
        s->isEnd = true;
        s->height = 'z';
      } else {
        s->height = c;
      }
      squares.push_back(s);
    }
    squareMap.push_back(squares);
  }
  parseNeighbours(squareMap);
  answer = bfs(start);
  std::cout << "Puzzle one: " << answer << std::endl;
  delete_squareMap(squareMap);
}

void puzzle_two(std::vector<std::string> input) {
  int answer{INT_MAX};
  std::vector<square *> startingCandidates{};
  std::vector<std::vector<square *>> squareMap;
  for (int i = 0; i < input.size(); ++i) {
    std::string row = input[i];
    std::vector<square *> squares;
    for (int j = 0; j < row.size(); ++j) {
      char c = row[j];
      square *s = new square();
      if (c == 'S' || c == 'a') {
        s->height = 'a';
        startingCandidates.push_back(s);
      } else if (c == 'E') {
        s->isEnd = true;
        s->height = 'z';
      } else {
        s->height = c;
      }
      squares.push_back(s);
    }
    squareMap.push_back(squares);
  }
  parseNeighbours(squareMap);
  for (square *start : startingCandidates) {
    answer = std::min(answer, bfs(start));
    resetNeighbours(squareMap);
  }
  std::cout << "Puzzle two: " << answer << std::endl;
  delete_squareMap(squareMap);
}

int main() {
  std::vector<std::string> exampleInput{"Sabqponm", "abcryxxl", "accszExk",
                                        "acctuvwj", "abdefghi"};
  AoCHelper a1{"2022", "12"};
  std::vector<std::string> result = a1.get_input();
  puzzle_one(result);
  puzzle_two(result);
}
