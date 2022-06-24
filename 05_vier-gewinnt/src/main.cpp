#include <iostream>

#include "mapra/Board.h"
#include "mapra/unit.h"

int main() {
  mapra::StartGame(0);

  while (true) {
    int turn;
    std::cout << "Yellow's turn. Please select a column" << std::endl;
    std::cin >> turn;
    std::cout << "Yellow places in column " << turn << std::endl;
    int column = mapra::NextTurn(turn);
    std::cout << "Red responded with column" << column << std::endl;
  }
  return 1;
}

void miniMaxAlgorithmus(Board b, Player turn) {
  // TODO
}