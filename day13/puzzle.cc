#include <vector>

#include "../AoCHelper/AoCHelper.h"

bool is_number(const char c) { return c >= '0' && c <= '9'; }

bool compare(std::string& l, std::string& r) {
  int lCounter{};
  int rCounter{};
  while (lCounter < l.size() && rCounter < r.size()) {
    if (is_number(l[lCounter]) && is_number(r[rCounter])) {
      int lInt{};
      int rInt{};
      while (is_number(l[lCounter])) {
        lInt *= 10;
        lInt += l[lCounter] - '0';
        lCounter++;
      }
      while (is_number(r[rCounter])) {
        rInt *= 10;
        rInt += r[rCounter] - '0';
        rCounter++;
      }
      if (lInt == rInt) {
        continue;
      } else if (lInt < rInt) {
        std::cout << lInt << "<" << rInt << "  Left list item " << lInt
                  << " at pos " << lCounter << " smaller than right. (" << rInt
                  << " at pos " << rCounter << "):" << std::endl;
        return true;
      } else {
        // lInt > rInt
        return false;
      }
    } else if (l[lCounter] == r[rCounter]) {
      lCounter++;
      rCounter++;
    } else if (l[lCounter] == ']') {
      std::cout << "Left array ran out of items at pos " << lCounter << " :"
                << std::endl;
      return true;
    } else if (r[rCounter] == ']') {
      return false;
    } else if (l[lCounter] == ',' || l[lCounter] == '[') {
      lCounter++;
    } else if (r[rCounter] == ',' || r[rCounter] == '[') {
      rCounter++;
    }
  }
  if (lCounter == l.size()) {
    std::cout << "Hit the end:" << std::endl;
    return true;
  }
  return false;
}

void puzzle_one(std::vector<std::string> input) {
  int answer{};
  int counter{};
  for (int i = 0; i < input.size() - 3; i += 3) {
    counter++;
    if (compare(input[i], input[i + 1])) {
      std::cout << "Left:  " << input[i] << std::endl;
      std::cout << "Right: " << input[i + 1] << std::endl << std::endl;
      answer += counter;
    };
  }
  std::cout << "Puzzle one: " << answer << std::endl;
}

void puzzle_two(std::vector<std::string> input) {
  int answer{};
  for (std::string row : input) {
  }
  std::cout << "Puzzle two: " << answer << std::endl;
}

int main() {
  std::vector<std::string> exampleInput{"[1,1,3,1,1]",
                                        "[1,1,5,1,1]",
                                        "",
                                        "[[1],[2,3,4]]",
                                        "[[1],4]",
                                        "",
                                        "[9]",
                                        "[[8,7,6]]",
                                        "",
                                        "[[4,4],4,4]",
                                        "[[4,4],4,4,4]",
                                        "",
                                        "[7,7,7,7]",
                                        "[7,7,7]",
                                        "",
                                        "[]",
                                        "[3]",
                                        "",
                                        "[[[]]]",
                                        "[[]]",
                                        "",
                                        "[1,[2,[3,[4,[5,6,7]]]],8,9]",
                                        "[1,[2,[3,[4,[5,6,0]]]],8,9]"};
  AoCHelper a1{"2022", "13"};
  std::vector<std::string> result = a1.get_input();
  puzzle_one(result);
  puzzle_two(result);
}
