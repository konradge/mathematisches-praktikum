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
  test.AssertEq("max(3,-4) is 3", 3, std::max(3, -4));  // extra falsch  (but now true)

  std::vector <unsigned int	> data1 = mapra::GetExample(0, 30);
  cout << "vector before bubblesort" << endl;
  Sort::print_vector(data1);
  cout << "vector after bubblesort" << endl;
  data1 = Sort::bubblesort(data1, data1.size());
  mapra::CheckSolution(*&data1);
  Sort::print_vector(data1);

  std::vector <unsigned int > data2 = mapra::GetExample(1, 10);
  cout << "vector before mergesort" << endl;
  Sort::print_vector(data2);
  cout << "vector after mergesort" << endl;
  data2 = Sort::mergesort(data2, data2.size());
  Sort::print_vector(data2);
  mapra::CheckSolution(*&data2);

  
  
  
  return 0;
}
