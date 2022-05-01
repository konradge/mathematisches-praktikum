#include "SortInterface.h"
#include "student.h"

int main() {
  std::string sorting_algorithm;

  mapra::SortingAlgorithm algorithm;

  std::cout << "Bitte M, A oder B für den Algorithmus wählen: " << std::endl;
  std::cin >> sorting_algorithm;

  algorithm = mapra::getSortingAlgorithm(sorting_algorithm);

  while (algorithm == mapra::SortingAlgorithm::NONE) {
    std::cout << "Nur M, A oder B erlaubt" << std::endl;
    std::cin >> sorting_algorithm;
    algorithm = mapra::getSortingAlgorithm(sorting_algorithm);
  }

  std::cout << std::endl << "-----Doubles------" << std::endl;

  mapra::Print<double>(
      std::cout, mapra::GetFromFileAndSort<double>("doubles.txt", algorithm));

  std::cout << std::endl << "-----Strings------" << std::endl;
  mapra::Print<std::string>(std::cout, mapra::GetFromFileAndSort<std::string>(
                                           "strings.txt", algorithm));

  std::cout << std::endl << "-----Students------" << std::endl;
  mapra::Print<mapra::Student>(
      std::cout,
      mapra::GetFromFileAndSort<mapra::Student>("studenten.txt", algorithm));

  return 0;
}