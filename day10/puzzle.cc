#include <queue>
#include <vector>

#include "../AoCHelper/AoCHelper.h"

void determineSignalStrength(int& answer, int& cycle, int& x) {
  if (cycle == 20 || cycle == 60 || cycle == 100 || cycle == 140 ||
      cycle == 180 || cycle == 220) {
    answer += (x * (cycle));
  }
}

void printCrtScreen(std::vector<int>& crtMap) {
  std::vector<std::vector<char>> map(6, std::vector<char>(40, '.'));
  for (int i = 0; i < crtMap.size(); i++) {
    int j = crtMap[i] % 40;
    int v = crtMap[i] / 40;
    map[v][j] = '#';
  }
  for (int i = 0; i < map.size(); i++) {
    for (int j = 0; j < map[0].size(); j++) {
      std::cout << map[i][j];
    }
    std::cout << std::endl;
  }
  std::cout << std::endl;
}

void puzzle(std::vector<std::string> input) {
  int partOneanswer{};
  int x{1};
  int totalCycles{0};
  int crtCycle{0};
  std::queue<int> toBeExecuted{};
  std::queue<int> executing{};
  std::vector<int> crtMap{};
  for (std::string row : input) {
    int calculationCycles{1};
    int value{0};
    std::string instruction = row.substr(0, 4);
    if (instruction != "noop") {
      value = std::stoi(row.substr(5, row.size()));
      calculationCycles = 2;
    }
    for (int i = 1; i <= calculationCycles; i++) {
      if (crtCycle == x - 1 || crtCycle == x || crtCycle == x + 1) {
        crtMap.push_back(totalCycles);
      }
      totalCycles++;
      crtCycle = totalCycles % 40;
      determineSignalStrength(partOneanswer, totalCycles, x);
    }
    x += value;
  }
  std::cout << "Puzzle one: " << partOneanswer << std::endl;
  std::cout << "Puzzle two: " << std::endl;
  printCrtScreen(crtMap);
}

int main() {
  std::vector<std::string> exampleInput{
      "addx 15",  "addx -11", "addx 6",   "addx -3",  "addx 5",   "addx -1",
      "addx -8",  "addx 13",  "addx 4",   "noop",     "addx -1",  "addx 5",
      "addx -1",  "addx 5",   "addx -1",  "addx 5",   "addx -1",  "addx 5",
      "addx -1",  "addx -35", "addx 1",   "addx 24",  "addx -19", "addx 1",
      "addx 16",  "addx -11", "noop",     "noop",     "addx 21",  "addx -15",
      "noop",     "noop",     "addx -3",  "addx 9",   "addx 1",   "addx -3",
      "addx 8",   "addx 1",   "addx 5",   "noop",     "noop",     "noop",
      "noop",     "noop",     "addx -36", "noop",     "addx 1",   "addx 7",
      "noop",     "noop",     "noop",     "addx 2",   "addx 6",   "noop",
      "noop",     "noop",     "noop",     "noop",     "addx 1",   "noop",
      "noop",     "addx 7",   "addx 1",   "noop",     "addx -13", "addx 13",
      "addx 7",   "noop",     "addx 1",   "addx -33", "noop",     "noop",
      "noop",     "addx 2",   "noop",     "noop",     "noop",     "addx 8",
      "noop",     "addx -1",  "addx 2",   "addx 1",   "noop",     "addx 17",
      "addx -9",  "addx 1",   "addx 1",   "addx -3",  "addx 11",  "noop",
      "noop",     "addx 1",   "noop",     "addx 1",   "noop",     "noop",
      "addx -13", "addx -19", "addx 1",   "addx 3",   "addx 26",  "addx -30",
      "addx 12",  "addx -1",  "addx 3",   "addx 1",   "noop",     "noop",
      "noop",     "addx -9",  "addx 18",  "addx 1",   "addx 2",   "noop",
      "noop",     "addx 9",   "noop",     "noop",     "noop",     "addx -1",
      "addx 2",   "addx -37", "addx 1",   "addx 3",   "noop",     "addx 15",
      "addx -21", "addx 22",  "addx -6",  "addx 1",   "noop",     "addx 2",
      "addx 1",   "noop",     "addx -10", "noop",     "noop",     "addx 20",
      "addx 1",   "addx 2",   "addx 2",   "addx -6",  "addx -11", "noop",
      "noop",     "noop"};
  AoCHelper a1{"2022", "10"};
  std::vector<std::string> result = a1.get_input();
  puzzle(result);
}
