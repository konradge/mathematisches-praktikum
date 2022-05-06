#include <iostream>
#include <vector>

#include "CalculateIntegral.h"
#include "unit.h"

int main() {
  std::cout << "Welches Beispiel soll gerechnet werden?" << std::endl;
  int example_id;
  std::cin >> example_id;

  double a, b, epsilon;

  getExample(example_id, a, b, epsilon, false);

  double result = CalculateIntegral::calculate(a, b, epsilon);

  checkSolution(result);
  return 0;
}