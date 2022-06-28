#include "mapra/Board.h"

#include <iostream>
#include <stdexcept>

Board::Board(size_t n, size_t m) : col_count(n), row_depth(m) {
  board.resize(col_count * row_depth);
  for (size_t i = 0; i < col_count; i++) {
    for (size_t j = 0; j < row_depth; j++) {
      (*this)(i, j) = EMPTY_STATE;
    }
  }
}

Board::Board(Board& b) {
  col_count = b.col_count;
  row_depth = b.row_depth;

  board.resize(col_count * row_depth);
  for (size_t i = 0; i < col_count; i++) {
    for (size_t j = 0; j < row_depth; j++) {
      (*this)(i, j) = b(i, j);
    }
  }
}

void Board::print() const {
  std::cout << "-----------------" << std::endl;
  std::cout << col_count << " columns and " << row_depth << " rows"
            << std::endl;
  for (size_t i = row_depth; i > 0; i--) {
    for (size_t j = 0; j < col_count; j++) {
      std::cout << (*this)(j, i - 1) << " ";
    }
    std::cout << std::endl;
  }
  std::cout << "-----------------" << std::endl;
}

void Board::clear() {
  for (size_t i = 0; i < col_count; i++) {
    for (size_t j = 0; j < row_depth; j++) {
      (*this)(i, j) = EMPTY_STATE;
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
  return board[col * row_depth + row];
}

// Access the state of the board at the given position, where row=0 means the
// bottom of the given column
// Throw an error if the position does not exist on the board.
State& Board::operator()(size_t col, size_t row) {
  if (row >= row_depth || col >= col_count) {
    throw std::out_of_range("row " + std::to_string(row) + " or col " +
                            std::to_string(col) + " out of range");
  }
  return board[col * row_depth + row];
}

// Inserts the player's piece in the given column.
bool Board::insert(size_t column, Player player) {
  if (column >= col_count) {
    throw std::out_of_range("column " + std::to_string(column) +
                            " out of range");
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

void Board::uninsert(size_t column) {
  if (column >= col_count) {
    throw std::out_of_range("column " + std::to_string(column) +
                            " out of range");
  }
  for (size_t i = row_depth; i > 0; i--) {
    if ((*this)(column, i - 1) != EMPTY_STATE) {
      (*this)(column, i - 1) = EMPTY_STATE;
      return;
    }
  }
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
  // std::cout << (*this)(0, 0);
  // Check rows
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

  // Diagonals left-top to right-bottom
  for (size_t i = 3; i < get_row_depth(); i++) {
    for (size_t j = 0; j < get_col_count() - 3; j++) {
      if ((*this)(j, i) == (State)player &&
          (*this)(j + 1, i - 1) == (State)player &&
          (*this)(j + 2, i - 2) == (State)player &&
          (*this)(j + 3, i - 3) == (State)player) {
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