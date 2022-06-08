// Copyright (c) 2022, The MaPra Authors.

#include <iostream>

#include "mapra/matrix.h"
#include "mapra/vector.h"

int main() {
  mapra::Matrix<int> m(2, 2);

  m(0, 0) = 5;
  m(1, 1) = 10;
  std::cout << m << std::endl;

  mapra::Vector<int> v(2);
  v(0) = 1;
  v(1) = 2;

  std::cout << v << std::endl;
  return 0;
}
