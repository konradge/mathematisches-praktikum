// Copyright (c) 2022, The MaPra Authors.

#include <fstream>
#include <iostream>
#include <sstream>
#include <string>

#include "mapra_test.h"
#include "sparse_matrix.h"
#include "vector.h"

int main() {
  mapra::MapraTest test("Matrizen");

  Sparse_Matrix m(3, 3);
  Vector v(3), expected(3), d(3);
  m.put(0, 0, 9);
  m.put(1, 0, 0);
  m.put(2, 0, 2);
  m.put(0, 1, 3);
  m.put(1, 1, 1);
  m.put(2, 1, 2);
  m.put(0, 2, 4);
  m.put(1, 2, 2);
  m.put(2, 2, 2);

  v(0) = 1;
  v(1) = 2;
  v(2) = 3;

  expected(0) = 27;
  expected(1) = 8;
  expected(2) = 12;
  test.Assert("Matrix * Vector", m * v == expected);

  d(0) = 4;
  d(1) = 0.5;
  d(2) = 10;

  expected(0) = 0.25;
  expected(1) = 4;
  expected(2) = 0.3;

  test.Assert("Matrix / Vector", v / d == expected);

  v(0) = 0;
  v(1) = 3;
  v(2) = 4;

  test.Assert("2-Norm", v.norm2() == 5);

  test.Assert("Vector - Vector", (v - v).norm2() == 0);
  return 0;
}