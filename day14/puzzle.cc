#include <vector>

#include "../AoCHelper/AoCHelper.h"

struct Tile {
  bool occupied{false};
  bool rock{false};  // only used for printing
};

void print_tiles(std::vector<std::vector<Tile>>& tiles) {
  for (int i = 0; i < 175; i++) {  // numbers based on what was relevant for my
                                   // input (min and max y)
    for (int j = 480; j < 550; j++) {  // same but for x
      if (tiles[i][j].occupied) {
        if (tiles[i][j].rock) {
          std::cout << "R";
        } else {
          std::cout << "#";
        }
      } else {
        if (i == 0 && j == 500) {
          std::cout << "+";
        } else {
          std::cout << ".";
        }
      }
    }
    std::cout << std::endl;
  }
}

void create_floor(std::vector<std::vector<Tile>>& tiles, int floorHeight) {
  for (auto& x : tiles[floorHeight]) {
    x.occupied = true;
    x.rock = true;
  }
}

int create_rocks(std::vector<std::vector<Tile>>& tiles,
                 std::vector<std::string>& input) {
  int max_y{0};
  int min_y{INT_MAX};
  int min_x{INT_MAX};
  int max_x{};
  for (std::string row : input) {
    int prev_x;
    int prev_y;
    for (int i = 0; i < myLib::split(row, '-').size(); i++) {
      {
        std::string coordinate = myLib::split(row, '-')[i];
        if (coordinate.substr(0, 1) == ">") {
          coordinate = coordinate.substr(1);
        }
        int x{std::stoi(myLib::split(coordinate, ',')[0])};
        int y{std::stoi(myLib::split(coordinate, ',')[1])};
        if (i == 0) {
          tiles[y][x].occupied = true;
          tiles[y][x].rock = true;
          prev_x = x;
          prev_y = y;
        } else {
          if (x != prev_x && y != prev_y) {
            std::cout << "Error while creating rocks! Diagonal line? x: " << x
                      << " y:" << y << " prev_x:" << prev_x
                      << " prev_y:" << prev_y << std::endl;
          }
          if (x == prev_x) {
            if (y > prev_y) {
              for (int j = prev_y; j <= y; j++) {
                tiles[j][x].occupied = true;
                tiles[j][x].rock = true;
              }
            } else {
              for (int j = y; j <= prev_y; j++) {
                tiles[j][x].occupied = true;
                tiles[j][x].rock = true;
              }
            }
          } else {
            if (x > prev_x) {
              for (int j = prev_x; j <= x; j++) {
                tiles[y][j].occupied = true;
                tiles[y][j].rock = true;
              }
            } else {
              for (int j = x; j <= prev_x; j++) {
                tiles[y][j].occupied = true;
                tiles[y][j].rock = true;
              }
            }
          }
          max_y = std::max(max_y, y);
          min_x = std::min(min_x, x);
          max_x = std::max(max_x, x);
          min_y = std::min(min_y, y);
          prev_x = x;
          prev_y = y;
        }
      }
    }
  }
  // std::cout << "min x: " << min_x << " max x: " << max_x << " min y:" <<
  // min_y
  //           << " max y:" << max_y << std::endl;
  return max_y;
}

// returns false if sand hits max_y
bool simulate_sand(std::vector<std::vector<Tile>>& tiles, int x, int y,
                   int max_y) {
  if (tiles[y + 1][x].occupied == false) {
    if (y + 1 >= max_y) {
      return false;
    }

    return simulate_sand(tiles, x, y + 1, max_y);
  } else {
    if (tiles[y + 1][x - 1].occupied == false) {
      return simulate_sand(tiles, x - 1, y + 1, max_y);
    } else if (tiles[y + 1][x + 1].occupied == false) {
      return simulate_sand(tiles, x + 1, y + 1, max_y);
    } else {
      tiles[y][x].occupied = true;
      return true;
    }
  }
}

void puzzle_one(std::vector<std::string> input) {
  int answer{};
  std::vector<std::vector<Tile>> tiles(5000, std::vector<Tile>(5000));
  int max_y = create_rocks(tiles, input);
  const int sand_spawn_point_x{500};
  const int sand_spawn_point_y{0};
  while (simulate_sand(tiles, sand_spawn_point_x, sand_spawn_point_y, max_y)) {
    answer++;
  }

  std::cout << "Puzzle one: " << answer << std::endl;
}

void puzzle_two(std::vector<std::string> input) {
  int answer{};
  std::vector<std::vector<Tile>> tiles(5000, std::vector<Tile>(5000));
  int max_y = create_rocks(tiles, input);
  create_floor(tiles, max_y + 2);
  const int sand_spawn_point_x{500};
  const int sand_spawn_point_y{0};
  while (tiles[sand_spawn_point_y][sand_spawn_point_x].occupied == false) {
    if (!simulate_sand(tiles, sand_spawn_point_x, sand_spawn_point_y,
                       tiles.size() - 1)) {
      print_tiles(tiles);
      std::cout << "Error puzzle two. Sand hit max_y!" << std::endl;
      break;
    }
    answer++;
  }
  // print_tiles(tiles);
  std::cout << "Puzzle two: " << answer << std::endl;
}

int main() {
  std::vector<std::string> exampleInput{"498,4 -> 498,6 -> 496,6",
                                        "503,4 -> 502,4 -> 502,9 -> 494,9"};
  AoCHelper a1{"2022", "14"};
  std::vector<std::string> result = a1.get_input();
  puzzle_one(result);
  puzzle_two(result);
}
