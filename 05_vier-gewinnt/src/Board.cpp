#include "mapra/Board.h"

#include <stdexcept>

Board::Board(int n, int m) : col_count(n), row_depth(m) {
  board.resize(col_count);
  for (int i = 0; i < row_depth; i++) {
    board[i].resize(row_depth, EMPTY_STATE);
  }
}

void Board::clear() {
  for (int i = 0; i < row_depth; i++) {
    for (int j = 0; j < col_count; j++) {
      board[i][j] = EMPTY_STATE;
    }
  }
}

// Access the state of the board at the given position, where row=0 means the
// bottom of the given column.
// Return State::EMPTY if the position does not exist on the board.
State Board::operator()(int col, int row) const {
  if (row >= row_depth || col >= col_count) {
    // throw std::out_of_range("row or col out of range");
    return EMPTY_STATE;
  }
  return board[col][row];
}

// Access the state of the board at the given position, where row=0 means the
// bottom of the given column
// Throw an error if the position does not exist on the board.
State& Board::operator()(int col, int row) {
  if (row >= row_depth || col >= col_count) {
    throw std::out_of_range("row or col out of range");
  }
  return board[col][row];
}

// Inserts the player's piece in the given column.
bool Board::insert(int column, Player player) {
  if (column >= col_count) {
    throw std::out_of_range("column out of range");
  }
  for (int i = 0; i < row_depth; i++) {
    if ((*this)(column, i) == EMPTY_STATE) {
      (*this)(column, i) = (State)player;
      return hasWon(player);
    }
  }

  // Selected column is already filled
  return false;
}

WinningState Board::getWinningState() const {
  if (hasWon(Player::YELLOW)) {
    return YELLOW_WON;
  } else if (hasWon(Player::RED)) {
    return RED_WON;
  } else if (boardFilled()) {
    return DRAW;
  } else {
    return UNFINISHED;
  }
}

bool Board::hasWon(Player player) const {
  // Check rows(State)
  for (int i = 0; i < row_depth; i++) {
    for (int j = 0; j < col_count - 3; j++) {
      if ((*this)(j, i) == (State)player &&
          (*this)(j + 1, i) == (State)player &&
          (*this)(j + 2, i) == (State)player &&
          (*this)(j + 3, i) == (State)player) {
        return true;
      }
    }
  }

  // Check columns
  for (int i = 0; i < col_count; i++) {
    for (int j = 0; j < row_depth - 3; j++) {
      if ((*this)(i, j) == (State)player &&
          (*this)(i, j + 1) == (State)player &&
          (*this)(i, j + 2) == (State)player &&
          (*this)(i, j + 3) == (State)player) {
        return true;
      }
    }
  }

  // Check diagonals
  for (int i = 0; i < row_depth - 3; i++) {
    for (int j = 0; j < col_count - 3; j++) {
      if ((*this)(j, i) == (State)player &&
          (*this)(j + 1, i + 1) == (State)player &&
          (*this)(j + 2, i + 2) == (State)player &&
          (*this)(j + 3, i + 3) == (State)player) {
        return true;
      }
    }
  }

  return false;
}

bool Board::boardFilled() const {
  for (int col = 0; col < col_count; col++) {
    if ((*this)(col, row_depth - 1) == EMPTY_STATE) {
      return false;
    }
  }
  return true;
}