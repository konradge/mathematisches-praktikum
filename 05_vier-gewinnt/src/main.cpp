#include <algorithm>
#include <cassert>
#include <iostream>
#include <random>
#include <sstream>
#include <tuple>

#include "mapra/Board.h"
#include "mapra/unit.h"
#include "util.h"

double Z_2 = 0.005, Z_3 = 0.01;
size_t difficulty = 1, depth = 4;

std::pair<double, int> miniMaxAlgorithmus(Board& b, Player caller, Player turn,
                                          int depth);

Player getOtherPlayer(Player p) { return (p == YELLOW) ? RED : YELLOW; }

int main(int argc, char* argv[]) {
  if (argc >= 5) {
    std::istringstream(argv[4]) >> depth;
  }
  if (argc >= 4) {
    std::istringstream(argv[3]) >> difficulty;
  }
  if (argc >= 3) {
    std::istringstream(argv[2]) >> Z_3;
  }
  if (argc >= 2) {
    std::istringstream(argv[1]) >> Z_2;
  }

  std::cout << "Running with Z_2 = " << Z_2 << " and Z_3 = " << Z_3
            << " and depth = " << depth << std::endl;
  Board b(mapra::kNumCols, mapra::kNumRows);
  mapra::StartGame(difficulty);
  size_t round = 0;
  int column;

  while (true) {
    auto [value, turn] = miniMaxAlgorithmus(b, YELLOW, YELLOW, depth);
    // auto turn = random() % mapra::kNumCols;
    b.insert(turn, YELLOW);

    column = mapra::NextTurn(turn);
    if (column >= 0) {
      b.insert(column, RED);
    } else {
      b.clear();
      round++;
      if (round < 5 && round % 2 != 0) {
        column = mapra::NextTurn(-1);
        b.insert(column, RED);
      } else if (round >= 5) {
        return 1;
      }
    }
  }

  return 0;
}

typedef std::vector<State> section_t;

std::vector<section_t> getSections(Board& b) {
  // Get all sections of four on the board
  std::vector<section_t> sections;
  // Columns
  for (size_t i = 0; i < b.get_col_count(); i++) {
    for (size_t j = 0; j < b.get_row_depth() - 3; j++) {
      sections.push_back(
          section_t{b(i, j), b(i, j + 1), b(i, j + 2), b(i, j + 3)});
    }
  }
  // Rows
  for (size_t i = 0; i < b.get_row_depth(); i++) {
    for (size_t j = 0; j < b.get_col_count() - 3; j++) {
      sections.push_back(
          section_t{b(j, i), b(j + 1, i), b(j + 2, i), b(j + 3, i)});
    }
  }
  // Diagonals left-bottom to right-top
  for (size_t i = 0; i < b.get_row_depth() - 3; i++) {
    for (size_t j = 0; j < b.get_col_count() - 3; j++) {
      sections.push_back(section_t{b(j, i), b(j + 1, i + 1), b(j + 2, i + 2),
                                   b(j + 3, i + 3)});
    }
  }

  // Diagonals left-top to right-bottom
  for (size_t i = 3; i < b.get_row_depth(); i++) {
    for (size_t j = 0; j < b.get_col_count() - 3; j++) {
      sections.push_back(section_t{b(j, i), b(j + 1, i - 1), b(j + 2, i - 2),
                                   b(j + 3, i - 3)});
    }
  }

  return sections;
}

double heuristic(Board& b) {
  double value;
  for (auto section : getSections(b)) {
    if (vector_contains(section, YELLOW_STATE) &&
        vector_contains(section, RED_STATE)) {
      // NOOP
    } else if (vector_count(section, YELLOW_STATE) == 2) {
      value += Z_2;
    } else if (vector_count(section, YELLOW_STATE) == 3) {
      value += Z_3;
    } else if (vector_count(section, RED_STATE) == 2) {
      value -= Z_2;
    } else if (vector_count(section, RED_STATE) == 3) {
      value -= Z_3;
    } else if (vector_count(section, YELLOW_STATE) == 4) {
      return 1;
    } else if (vector_count(section, RED_STATE) == 4) {
      return -1;
    }
  }

  if (fabs(value) >= 1) {
    // std::cout << value << std::endl;
  }
  return value;
}

std::pair<double, int> miniMaxAlgorithmus(Board& b, Player caller, Player turn,
                                          int depth) {
  if (b.getWinningState() == DRAW) {
    // Game ended in a draw
    return std::make_pair(0, 0);
  } else if (b.getWinningState() != UNFINISHED) {
    // Game was won by one of the players
    return std::make_pair(b.getWinningState() == (WinningState)caller ? 1 : -1,
                          0);
  } else if (depth == 0) {
    // Apply heuristic function
    return std::make_pair(heuristic(b), 0);
  }

  std::vector<std::pair<double, size_t>> possible_turns;
  for (size_t col = 0; col < mapra::kNumCols; col++) {
    if (b.canInsert(col)) {
      // Execute step on (copied) board to test its value
      /** Version with uninsert **/
      b.insert(col, turn);
      auto [currentValue, _] =
          miniMaxAlgorithmus(b, caller, getOtherPlayer(turn), depth - 1);
      // And add it to the list of possible turns
      possible_turns.push_back(std::make_pair(currentValue, col));
      b.uninsert(col);

      /** Version with copy **/
      Board boardCopy(b);
      // boardCopy.insert(col, turn);
      // auto [currentValue, _] = miniMaxAlgorithmus(
      //     boardCopy, caller, getOtherPlayer(turn), depth - 1);
      // // And add it to the list of possible turns
      // possible_turns.push_back(std::make_pair(currentValue, col));
    }
  }

  // Find best/worst possible value
  double extreme_value = possible_turns[0].first;

  for (auto& [value, _] : possible_turns) {
    if (caller == turn) {
      if (value > extreme_value) {
        extreme_value = value;
      }
    } else {
      if (value < extreme_value) {
        extreme_value = value;
      }
    }
  }

  // Find all turns with best/worst value
  std::vector<std::pair<double, size_t>> extreme_turns;

  // Filter all turns with a value of extreme_value
  std::copy_if(possible_turns.begin(), possible_turns.end(),
               std::back_inserter(extreme_turns), [extreme_value](auto turn) {
                 return turn.first == extreme_value;
               });

  // Select on of those turns randomly
  return extreme_turns[randomInt(0, extreme_turns.size() - 1)];
}