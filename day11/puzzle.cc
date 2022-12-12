#include <queue>
#include <vector>

#include "../AoCHelper/AoCHelper.h"

struct Monkey {
  std::queue<uint64_t> holdingItems{};
  std::string operation;
  uint64_t test;
  int ifTrueThrowTo;
  int ifFalseThrowTo;
  size_t counter{0};
};

uint64_t doOperation(uint64_t item, std::string& operation) {
  std::vector<std::string> splitOperation = myLib::split(operation, ' ');
  uint64_t lhs{};
  uint64_t rhs{};
  if (splitOperation[3] == "old") {
    lhs = item;
  } else {
    lhs = std::stoll(splitOperation[3]);
  }

  if (splitOperation[5] == "old") {
    rhs = item;
  } else {
    rhs = std::stoll(splitOperation[5]);
  }

  if (splitOperation[4] == "*") {
    return lhs * rhs;
  } else if (splitOperation[4] == "+") {
    return lhs + rhs;
  }
  return 0;
}

std::vector<Monkey> parseInput(std::vector<std::string> input) {
  std::vector<Monkey> monkeys{};
  for (std::string row : input) {
    if (row == "") {
      continue;
    }
    std::vector<std::string> splitRow = myLib::split(row, ' ');
    if (row.substr(0, 6) == "Monkey") {
      Monkey m{};
      monkeys.push_back(m);
    } else if (splitRow[2] == "Starting") {
      for (int i = 4; i < splitRow.size(); i++) {
        if (splitRow[i].back() == ',') {
          splitRow[i].pop_back();
        }
        monkeys.back().holdingItems.push(std::stoll(splitRow[i]));
      }
    } else if (splitRow[2] == "Operation:") {
      std::string operation = myLib::split(row, ':')[1];
      monkeys.back().operation = operation;
    } else if (splitRow[2] == "Test:") {
      monkeys.back().test = std::stoll(splitRow[5]);
    } else if (splitRow[4] == "If") {
      if (splitRow[5] == "true:") {
        monkeys.back().ifTrueThrowTo = std::stoi(splitRow[9]);
      } else {
        monkeys.back().ifFalseThrowTo = std::stoi(splitRow[9]);
      }
    }
  }
  return monkeys;
}

void puzzle_one(std::vector<std::string> input) {
  int answer{};
  std::vector<Monkey> monkeys = parseInput(input);
  for (int round = 0; round < 20; round++) {
    for (int i = 0; i < monkeys.size(); i++) {
      while (!monkeys[i].holdingItems.empty()) {
        uint64_t item = monkeys[i].holdingItems.front();
        monkeys[i].counter++;
        monkeys[i].holdingItems.pop();
        item = doOperation(item, monkeys[i].operation);
        item = item / 3;
        if (item % monkeys[i].test == 0) {
          monkeys[monkeys[i].ifTrueThrowTo].holdingItems.push(item);
        } else {
          monkeys[monkeys[i].ifFalseThrowTo].holdingItems.push(item);
        }
      }
    }
  }
  std::sort(
      monkeys.begin(), monkeys.end(),
      [](const Monkey& a, const Monkey& b) { return a.counter > b.counter; });
  answer = monkeys[0].counter * monkeys[1].counter;
  std::cout << "Puzzle one: " << answer << std::endl;
}

void puzzle_two(std::vector<std::string> input) {
  size_t answer{};
  std::vector<Monkey> monkeys = parseInput(input);
  uint64_t superMod = 1;
  for (Monkey m : monkeys) {
    superMod *= m.test;
  }
  for (int round = 0; round < 10000; round++) {
    for (int i = 0; i < monkeys.size(); i++) {
      while (!monkeys[i].holdingItems.empty()) {
        uint64_t item = monkeys[i].holdingItems.front();
        monkeys[i].counter++;
        monkeys[i].holdingItems.pop();
        item = doOperation(item, monkeys[i].operation);
        item = item % superMod;
        if (item % monkeys[i].test == 0ll) {
          monkeys[monkeys[i].ifTrueThrowTo].holdingItems.push(item);
        } else {
          monkeys[monkeys[i].ifFalseThrowTo].holdingItems.push(item);
        }
      }
    }
  }
  std::sort(
      monkeys.begin(), monkeys.end(),
      [](const Monkey& a, const Monkey& b) { return a.counter > b.counter; });
  answer = monkeys[0].counter * monkeys[1].counter;
  std::cout << "Puzzle two: " << answer << std::endl;
}

int main() {
  std::vector<std::string> exampleInput{"Monkey 0:",
                                        "  Starting items: 79, 98",
                                        "  Operation: new = old * 19",
                                        "  Test: divisible by 23",
                                        "    If true: throw to monkey 2",
                                        "    If false: throw to monkey 3",
                                        "",
                                        "Monkey 1:",
                                        "  Starting items: 54, 65, 75, 74",
                                        "  Operation: new = old + 6",
                                        "  Test: divisible by 19",
                                        "    If true: throw to monkey 2",
                                        "    If false: throw to monkey 0",
                                        "",
                                        "Monkey 2:",
                                        "  Starting items: 79, 60, 97",
                                        "  Operation: new = old * old",
                                        "  Test: divisible by 13",
                                        "    If true: throw to monkey 1",
                                        "    If false: throw to monkey 3",
                                        "",
                                        "Monkey 3:",
                                        "  Starting items: 74",
                                        "  Operation: new = old + 3",
                                        "  Test: divisible by 17",
                                        "    If true: throw to monkey 0",
                                        "    If false: throw to monkey 1"};
  AoCHelper a1{"2022", "11"};
  std::vector<std::string> result = a1.get_input();
  puzzle_one(result);
  puzzle_two(result);
}
