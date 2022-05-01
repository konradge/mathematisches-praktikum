#ifndef SORTINTERFACE_H_
#define SORTINTERFACE_H_

#include <fstream>
#include <vector>

#include "Sort.h"
#include "student.h"

namespace mapra {

enum SortingAlgorithm { BUBBLE_SORT, SELECTION_SORT, MERGE_SORT, NONE };

mapra::SortingAlgorithm getSortingAlgorithm(std::string str) {
  if (str == "B") return mapra::SortingAlgorithm::BUBBLE_SORT;
  if (str == "A") return mapra::SortingAlgorithm::SELECTION_SORT;
  if (str == "M") return mapra::SortingAlgorithm::MERGE_SORT;
  return mapra::SortingAlgorithm::NONE;
}

template <typename T>
void Read(std::ifstream& ifs, std::vector<T>& array) {
  while (!ifs.eof() && !ifs.fail()) {
    T data;
    ifs >> data;
    array.push_back(data);
  }
}

template <typename T>
void Print(std::ostream& os, const std::vector<T>& array) {
  for (auto data : array) {
    os << data << std::endl;
  }
}

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
      break;
  }
  if (algorithm_pointer != nullptr) {
    return algorithm_pointer(array);
  } else {
    return array;
  }
}

}  // namespace mapra

#endif