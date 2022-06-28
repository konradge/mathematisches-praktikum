// Copyright (c) 2022, The MaPra Authors.

#include "mapra/Board.h"

#include <algorithm>

#include "gtest/gtest.h"

TEST(BoardTest, ConstBoardAfterInitialization) {
  const Board b(4, 4);
  EXPECT_EQ(b(1, 1), State::EMPTY_STATE);
  EXPECT_EQ(b(10, 10), State::EMPTY_STATE);
  EXPECT_FALSE(b.boardFilled());
  EXPECT_EQ(b.getWinningState(), WinningState::UNFINISHED);
}

TEST(BoardTest, TooSmallBoard) {
  EXPECT_THROW(Board b(3, 3), std::invalid_argument);
}

TEST(BoardTest, HasWonHorizontallyYellow) {
  Board b(5, 5);
  EXPECT_TRUE(b.insert(0, YELLOW));
  EXPECT_TRUE(b.insert(1, YELLOW));
  EXPECT_TRUE(b.insert(2, YELLOW));
  EXPECT_TRUE(b.insert(3, YELLOW));
  EXPECT_TRUE(b.hasWon(YELLOW));
  EXPECT_EQ(b.getWinningState(), YELLOW_WON);
  EXPECT_FALSE(b.boardFilled());
}

TEST(BoardTest, HasWonHorizontallyRed) {
  Board b(5, 5);
  EXPECT_TRUE(b.insert(0, YELLOW));
  EXPECT_TRUE(b.insert(1, RED));
  EXPECT_TRUE(b.insert(2, YELLOW));
  EXPECT_TRUE(b.insert(3, YELLOW));
  EXPECT_TRUE(b.insert(0, RED));
  EXPECT_TRUE(b.insert(1, RED));
  EXPECT_TRUE(b.insert(2, RED));
  b.insert(3, RED);

  EXPECT_TRUE(b.hasWon(RED));
  EXPECT_EQ(b.getWinningState(), RED_WON);
  EXPECT_FALSE(b.boardFilled());
}

TEST(BoardTest, HasWonVerticallyYellow) {
  Board b(5, 5);
  EXPECT_TRUE(b.insert(0, RED));
  EXPECT_TRUE(b.insert(0, YELLOW));
  EXPECT_TRUE(b.insert(0, YELLOW));
  EXPECT_TRUE(b.insert(0, YELLOW));
  EXPECT_TRUE(b.insert(0, YELLOW));
  EXPECT_TRUE(b.hasWon(YELLOW));
  EXPECT_EQ(b.getWinningState(), YELLOW_WON);
  EXPECT_FALSE(b.boardFilled());
}

TEST(BoardTest, HasWonDiagonallyYellow) {
  Board b(5, 5);
  EXPECT_TRUE(b.insert(0, YELLOW));
  EXPECT_TRUE(b.insert(1, YELLOW));
  EXPECT_TRUE(b.insert(1, YELLOW));
  EXPECT_TRUE(b.insert(2, YELLOW));
  EXPECT_TRUE(b.insert(2, YELLOW));
  EXPECT_TRUE(b.insert(2, YELLOW));
  EXPECT_TRUE(b.insert(3, RED));
  EXPECT_TRUE(b.insert(3, RED));
  EXPECT_TRUE(b.insert(3, RED));
  EXPECT_TRUE(b.insert(3, YELLOW));
  EXPECT_TRUE(b.hasWon(YELLOW));
  EXPECT_EQ(b.getWinningState(), YELLOW_WON);
  EXPECT_FALSE(b.boardFilled());
}

TEST(BoardTest, VerticalOverflow) {
  Board b(5, 5);
  EXPECT_TRUE(b.insert(0, RED));
  EXPECT_TRUE(b.insert(0, YELLOW));
  EXPECT_TRUE(b.insert(0, RED));
  EXPECT_TRUE(b.insert(0, RED));
  EXPECT_TRUE(b.insert(0, RED));
  EXPECT_FALSE(b.insert(0, RED));
  EXPECT_FALSE(b.hasWon(RED));
  EXPECT_EQ(b.getWinningState(), UNFINISHED);
  EXPECT_FALSE(b.boardFilled());
}