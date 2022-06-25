#include "mapra/Board.h"

#include <stdexcept>

Board::Board(size_t n, size_t m) : col_count(n), row_depth(m) {
  board.resize(col_count);
  for (size_t i = 0; i < row_depth; i++) {
    board[i].resize(row_depth, EMPTY_STATE);
  }
}

Board::Board(Board& b) {
  col_count = b.col_count;
  row_depth = b.row_depth;

  board.resize(col_count);
  for (size_t i = 0; i < row_depth; i++) {
    board[i].resize(row_depth, EMPTY_STATE);
    for (size_t j = 0; j < row_depth; j++) {
      board[i][j] = b.board[i][j];
    }
  }
}

void Board::clear() {
  for (size_t i = 0; i < row_depth; i++) {
    for (size_t j = 0; j < col_count; j++) {
      board[i][j] = EMPTY_STATE;
    }
  }
}

// Access the state of the board at the given position, where row=0 means the
// bottom of the given column.
// Return State::EMPTY if the position does not exist on the board.
State Board::operator()(size_t col, size_t row) const {
  if (row >= row_depth || col >= col_count) {
    // throw std::out_of_range("row or col out of range");
    return EMPTY_STATE;
  }
  return board[col][row];
}

// Access the state of the board at the given position, where row=0 means the
// bottom of the given column
// Throw an error if the position does not exist on the board.
State& Board::operator()(size_t col, size_t row) {
  if (row >= row_depth || col >= col_count) {
    throw std::out_of_range("row or col out of range");
  }
  return board[col][row];
}

// Inserts the player's piece in the given column.
bool Board::insert(size_t column, Player player) {
  if (column >= col_count) {
    throw std::out_of_range("column out of range");
  }
  for (size_t i = 0; i < row_depth; i++) {
    if ((*this)(column, i) == EMPTY_STATE) {
      (*this)(column, i) = (State)player;
      return true;
    }
  }

  // Selected column is already filled
  return false;
}

bool Board::canInsert(size_t column) const {
  if (column >= col_count) {
    return false;
  } else {
    return (*this)(column, row_depth - 1) == EMPTY_STATE;
  }
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
  for (size_t i = 0; i < row_depth; i++) {
    for (size_t j = 0; j < col_count - 3; j++) {
      if ((*this)(j, i) == (State)player &&
          (*this)(j + 1, i) == (State)player &&
          (*this)(j + 2, i) == (State)player &&
          (*this)(j + 3, i) == (State)player) {
        return true;
      }
    }
  }

  // Check columns
  for (size_t i = 0; i < col_count; i++) {
    for (size_t j = 0; j < row_depth - 3; j++) {
      if ((*this)(i, j) == (State)player &&
          (*this)(i, j + 1) == (State)player &&
          (*this)(i, j + 2) == (State)player &&
          (*this)(i, j + 3) == (State)player) {
        return true;
      }
    }
  }

  // Check diagonals
  for (size_t i = 0; i < row_depth - 3; i++) {
    for (size_t j = 0; j < col_count - 3; j++) {
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
  for (size_t col = 0; col < col_count; col++) {
    if ((*this)(col, row_depth - 1) == EMPTY_STATE) {
      return false;
    }
  }
  return true;
}