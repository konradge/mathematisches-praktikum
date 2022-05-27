// Copyright (c) 2022, The MaPra Authors.

#include <algorithm>
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>

#include "Sort.h"
#include "mapra_test.h"
#include "unit.h"

void test_algorithm(unsigned int algorithmNumber, int testNumber);
void test_median();

int main() {
  // each number corresponds to one algorithm, triggered by switch-case
  for (auto number : {0, 1, 2, 3, 4, 5, 6})
    test_algorithm(number, 2);
  test_median();
  return 0;
}

void test_algorithm(unsigned int algorithmNumber, int testNumber) {
  std::vector<unsigned int> (*algorithm)(std::vector<unsigned int>);
  std::string algorithmName;
  switch (algorithmNumber) {
  case 0:
    algorithmName = "bubblesort";
    algorithm = &(Sort::Bubblesort);
    break;
  case 1:
    algorithmName = "mergesort";
    algorithm = &(Sort::Mergesort);
    break;
  case 2:
    algorithmName = "selectionsort";
    algorithm = &(Sort::Selectionsort);
    break;
  case 3:
    algorithmName = "insertionsort";
    algorithm = &(Sort::Insertionsort);
    break;
  case 4:
    algorithmName = "heapsort";
    algorithm = &(Sort::Heapsort);
    break;
  case 5:
    algorithmName = "quicksort";
    algorithm = &(Sort::Quicksort);
    break;
  default: // case 6
    algorithmName = "quicksortMedian";
    algorithm = &(Sort::QuicksortMedian);
  }

  mapra::MapraTest test(algorithmName);

  std::vector<unsigned int> data0 = {};
  test.AssertEq("-----test with empty vector-----", algorithm(data0), data0);

  std::vector<unsigned int> data1 = {1};
  test.AssertEq("-----test with a vector with one element-----",
                algorithm(data1), data1);

  for (int i = 0; i < testNumber; i++) {
    std::vector<unsigned int> data2 = mapra::GetExample(1, 10);
    test.Assert("-----test with vector with even number of elements -----",
                mapra::CheckSolution(algorithm(data2)));
  }

  for (int i = 0; i < testNumber; i++) {
    std::vector<unsigned int> data3 = mapra::GetExample(1, 11);
    test.Assert("-----test with vector with uneven number of elements -----",
                mapra::CheckSolution(algorithm(data3)));
  }

  for (int i = 0; i < testNumber; i++) {
    std::vector<unsigned int> data4 = mapra::GetExample(2, 10);
    test.Assert("-----test with a sorted vector-----",
                mapra::CheckSolution(algorithm(data4)));
  }

  for (int i = 0; i < testNumber; i++) {
    std::vector<unsigned int> data5 = mapra::GetExample(3, 10);
    test.Assert("-----test with a inverse sorted vector-----",
                mapra::CheckSolution(algorithm(data5)));
  }

  for (int i = 0; i < testNumber; i++) {
    std::vector<unsigned int> data6 = mapra::GetExample(4, 10);
    test.Assert("-----test with quicksort median aus 3 killer-----",
                mapra::CheckSolution(algorithm(data6)));
  }

  std::vector<unsigned int> sideEffects = mapra::GetExample(1, 10);
  std::vector<unsigned int> oldArray;
  for (auto elem : sideEffects) {
    oldArray.push_back(elem);
  }
  algorithm(sideEffects);
  test.AssertEq("-----test for absence of side effects-----", oldArray,
                sideEffects);
}

void test_median() {
  mapra::MapraTest test("MedianOfThree");

  std::vector<unsigned int> data = {1, 2, 3};
  test.AssertEq<unsigned int>("sorted", 1, Sort::MedianOfThree(data));

  data = {3, 2, 1};
  test.AssertEq<unsigned int>("sortedNinverted", 1, Sort::MedianOfThree(data));

  data = {2, 3, 1};
  test.AssertEq<unsigned int>("firstElement", 0, Sort::MedianOfThree(data));

  data = {3, 1, 2};
  test.AssertEq<unsigned int>("lastElement", 2, Sort::MedianOfThree(data));

  data = {4, 4, 4};
  test.AssertEq<unsigned int>("allEqual", 0, Sort::MedianOfThree(data));

  data = {1, 2, 3, 4};
  test.AssertEq<unsigned int>("moreThanThree", 2, Sort::MedianOfThree(data));
}
