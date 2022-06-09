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

  Sparse_Matrix n(2, 3);
  n.put(0, 0, 1);
  n.put(0, 1, 2);
  n.put(0, 2, 3);
  n.put(1, 0, 4);
  n.put(1, 1, 5);
  n.put(1, 2, 6);

  Sparse_Matrix exp(3, 2);
  exp.put(0, 0, 1);
  exp.put(1, 0, 2);
  exp.put(2, 0, 3);
  exp.put(0, 1, 4);
  exp.put(1, 1, 5);
  exp.put(2, 1, 6);

  test.Assert("Transpose Matrix", transpose(n) == exp);

  Vector v1(3), v2(3);
  v1(0) = 2;
  v1(1) = 4;
  v1(2) = 1;

  v2(0) = 1;
  v2(1) = 2;
  v2(2) = 9;

  test.Assert("Vector * Vector", v1 * v2 == 19);
  return 0;
}