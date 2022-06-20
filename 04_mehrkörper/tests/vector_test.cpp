// Copyright (c) 2022, The MaPra Authors.

#include "mapra/vector.h"

#include <algorithm>

#include "gtest/gtest.h"

void fillVector(mapra::Vector<int>& v) {
  for (size_t i = 0; i < v.GetLength(); i++) {
    v(i) = rand();
  }
}

class VectorTest : public ::testing::Test {
 protected:
  mapra::Vector<int> v;
};

TEST_F(VectorTest, ValuesAfterInitialization) {
  ASSERT_EQ(v.GetLength(), 1);
  ASSERT_EQ(v(0), 0);
}

TEST_F(VectorTest, ValuesAfterRedim) {
  fillVector(v);
  v.Redim(5);

  ASSERT_EQ(v.GetLength(), 5);

  for (size_t i = 0; i < v.GetLength(); i++) {
    ASSERT_EQ(v(i), 0);
  }
}

TEST_F(VectorTest, AssigningVectors) {
  mapra::Vector<int> w;
  v.Redim(2000);
  fillVector(v);
  w = v;
  ASSERT_TRUE(v == w);
  ASSERT_EQ(v.GetLength(), w.GetLength());
  for (size_t i = 0; i < v.GetLength(); i++) {
    ASSERT_EQ(v(i), w(i));
  }
}

TEST_F(VectorTest, CopyConstructor) {
  v.Redim(1500);
  fillVector(v);
  mapra::Vector<int> w(v);
  ASSERT_TRUE(v == w);
  ASSERT_EQ(v.GetLength(), w.GetLength());
  for (size_t i = 0; i < v.GetLength(); i++) {
    ASSERT_EQ(v(i), w(i));
  }
}