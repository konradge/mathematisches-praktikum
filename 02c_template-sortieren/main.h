#ifndef MAIN_H_
#define MAIN_H_

#include <fstream>
#include <iostream>
#include <vector>

#include "Sort.h"

namespace mapra {

enum SortingAlgorithm { BUBBLE_SORT, SELECTION_SORT, MERGE_SORT, NONE };

template <typename T>
void Read(std::ifstream& ifs, std::vector<T>& array);

template <typename T>
void Print(std::ostream& os, const std::vector<T>& array);

}  // namespace mapra

template <typename T>
std::vector<T> GetFromFileAndSort(std::string filename,
                                  mapra::SortingAlgorithm sorting_algorithm) {
  std::ifstream stream(filename);

  std::vector<T> array;
  mapra::Read(stream, array);

  std::vector<T> (*algorithm_pointer)(std::vector<T> data) = nullptr;

  switch (sorting_algorithm) {
    case mapra::SortingAlgorithm::MERGE_SORT:
      algorithm_pointer = &(Sort::Mergesort);
      break;
    case mapra::SortingAlgorithm::SELECTION_SORT:
      algorithm_pointer = &(Sort::Selectionsort);
      break;
    case mapra::SortingAlgorithm::BUBBLE_SORT:
      algorithm_pointer = &(Sort::Bubblesort);
      break;
    default:
      std::cout << "Bitte M, A oder B angeben!" << std::endl;
  }
  if (algorithm_pointer != nullptr) {
    return algorithm_pointer(array);
  } else {
    return array;
  }
}

#endif