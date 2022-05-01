#include <iostream>
#include <vector>

#include "unit.h"

int main() {
  std::cout << "Welches Beispiel soll gerechnet werden?" << std::endl;
  int example_id;
  std::cin >> example_id;

  double a, b, epsilon;

  getExample(1, a, b, epsilon, false);

  std::cout << f(200) << std::endl;
  return 0;
}