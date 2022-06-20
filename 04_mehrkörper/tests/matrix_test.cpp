// Copyright (c) 2022, The MaPra Authors.

#include "mapra/matrix.h"

#include <algorithm>

#include "gtest/gtest.h"

void fillMatrix(mapra::Matrix<int>& m) {
  for (size_t i = 0; i < m.GetRows(); i++) {
    for (size_t j = 0; j < m.GetCols(); j++) {
      m(i, j) = rand();
    }
  }
}

class MatrixTest : public ::testing::Test {
 protected:
  mapra::Matrix<int> m;
};

TEST_F(MatrixTest, ValuesAfterInitialization) {
  ASSERT_EQ(m.GetRows(), 1);
  ASSERT_EQ(m.GetCols(), 1);
  ASSERT_EQ(m(0, 0), 0);
}

TEST_F(MatrixTest, ValuesAfterRedim) {
  fillMatrix(m);
  m.Redim(5, 7, 0);

  ASSERT_EQ(m.GetRows(), 5);
  ASSERT_EQ(m.GetCols(), 7);

  for (size_t i = 0; i < m.GetRows(); i++) {
    for (size_t j = 0; j < m.GetCols(); j++) {
      ASSERT_EQ(m(i, j), 0);
    }
  }
}

TEST_F(MatrixTest, AssigningMatrices) {
  mapra::Matrix<int> n;
  m.Redim(1000, 2000);
  fillMatrix(m);
  n = m;
  ASSERT_TRUE(n == m);
  ASSERT_EQ(m.GetCols(), n.GetCols());
  ASSERT_EQ(m.GetRows(), n.GetRows());
  for (size_t i = 0; i < m.GetRows(); i++) {
    for (size_t j = 0; j < m.GetCols(); j++) {
      ASSERT_EQ(n(i, j), m(i, j));
    }
  }
}

TEST_F(MatrixTest, CopyConstructor) {
  m.Redim(1000, 1000);
  fillMatrix(m);
  mapra::Matrix<int> n(m);
  ASSERT_TRUE(n == m);
  ASSERT_EQ(m.GetCols(), n.GetCols());
  ASSERT_EQ(m.GetRows(), n.GetRows());
  for (size_t i = 0; i < m.GetRows(); i++) {
    for (size_t j = 0; j < m.GetCols(); j++) {
      ASSERT_EQ(n(i, j), m(i, j));
    }
  }
}