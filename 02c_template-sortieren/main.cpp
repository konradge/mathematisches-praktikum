#include "main.h"

#include <fstream>

#include "student.h"

mapra::SortingAlgorithm getSortingAlgorithm(std::string str) {
  if (str == "B") return mapra::SortingAlgorithm::BUBBLE_SORT;
  if (str == "A") return mapra::SortingAlgorithm::SELECTION_SORT;
  if (str == "M") return mapra::SortingAlgorithm::MERGE_SORT;
  return mapra::SortingAlgorithm::NONE;
}

template <typename T>
void mapra::Read(std::ifstream& ifs, std::vector<T>& array) {
  while (!ifs.eof() && !ifs.fail()) {
    T data;
    ifs >> data;
    array.push_back(data);
  }
}

template <typename T>
void mapra::Print(std::ostream& os, const std::vector<T>& array) {
  for (auto data : array) {
    os << data << std::endl;
  }
}

int getFromUser() {
  std::string sorting_algorithm;

  mapra::SortingAlgorithm algorithm;

  std::cout << "Bitte M, A oder B für den Algorithmus wählen: " << std::endl;
  std::cin >> sorting_algorithm;

  algorithm = getSortingAlgorithm(sorting_algorithm);

  while (algorithm == mapra::SortingAlgorithm::NONE) {
    std::cout << "Nur M, A oder B erlaubt" << std::endl;
    std::cin >> sorting_algorithm;
    algorithm = getSortingAlgorithm(sorting_algorithm);
  }

  std::cout << std::endl << "-----Doubles------" << std::endl;

  mapra::Print<double>(std::cout,
                       GetFromFileAndSort<double>("doubles.txt", algorithm));

  std::cout << std::endl << "-----Strings------" << std::endl;
  mapra::Print<std::string>(
      std::cout, GetFromFileAndSort<std::string>("strings.txt", algorithm));

  std::cout << std::endl << "-----Students------" << std::endl;
  mapra::Print<mapra::Student>(std::cout, GetFromFileAndSort<mapra::Student>(
                                              "studenten.txt", algorithm));

  return 0;
}