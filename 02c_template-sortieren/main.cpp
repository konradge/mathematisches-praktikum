#include "main.h"

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
    os << data;
  }
}

int main() { return 0; }