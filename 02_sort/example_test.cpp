// Copyright (c) 2022, The MaPra Authors.

#include "mapra_test.h"

#include <algorithm>
#include <iostream>
#include <string>

#include "Sort.h"
#include "unit.h"

int main() {
  mapra::MapraTest test("Beispiel");
  test.Assert("cin works", std::cin.good());
  test.AssertEq("max(-4,3) is 3", 3, std::max(-4, 3));
  test.AssertEq("max(3,-4) is 3", 3, std::max(3, -4));  // extra falsch
  std::vector <unsigned int	> data = mapra::GetExample(0, 30);




  Sort s;
  s.print_vector(data);




  data = s.mergeSort(data, data.size());
  s.print_vector(data);
  mapra::CheckSolution(*&data);
  return 0;
}
