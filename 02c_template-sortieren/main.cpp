#include "main.h"

#include <fstream>

#include "Sort.h"
#include "student.h"

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

template <typename T>
void SortType(std::string filename) {
  std::ifstream stream(filename);

  std::vector<T> array;
  mapra::Read(stream, array);

  auto out = Sort::Mergesort(array);

  mapra::Print(std::cout, out);
}

int main() {
  std::cout << std::endl << "-----Doubles------" << std::endl;
  SortType<double>("doubles.txt");

  std::cout << std::endl << "-----Strings------" << std::endl;
  SortType<std::string>("strings.txt");

  std::cout << std::endl << "-----Students------" << std::endl;
  SortType<mapra::Student>("studenten.txt");

  return 0;
}