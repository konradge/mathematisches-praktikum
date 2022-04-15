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

  cout << "-----------------------------------------" << endl;
  std::vector <unsigned int	> data1 = mapra::GetExample(0, 30);
  cout << "vector before bubblesort" << endl;
  Sort::print_vector(data1);
  cout << "vector after bubblesort" << endl;
  data1 = Sort::bubblesort(data1);
  mapra::CheckSolution(*&data1);
  Sort::print_vector(data1);

  cout << "-----------------------------------------" << endl;
  std::vector <unsigned int > data2 = mapra::GetExample(1, 10);
  cout << "vector before mergesort" << endl;
  Sort::print_vector(data2);
  cout << "vector after mergesort" << endl;
  data2 = Sort::mergesort(data2);
  Sort::print_vector(data2);
  mapra::CheckSolution(*&data2);
  cout << "-----------------------------------------" << endl;
  
  std::vector <unsigned int > data3 = mapra::GetExample(1, 10);
  cout << "vector before selectionsort" << endl;
  Sort::print_vector(data3);
  cout << "vector after selectionsort" << endl;
  data3 = Sort::selectionsort(data3);
  Sort::print_vector(data3);
  mapra::CheckSolution(*&data3);
  
  return 0;
}
