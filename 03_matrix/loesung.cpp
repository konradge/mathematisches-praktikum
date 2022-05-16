#include <cmath>
#include <sstream>
#include <tuple>

#include "matrix.h"
#include "unit.h"
#include "vector.h"

// Constant C
#define C 2

size_t index_of_element(mapra::Vector&, double);

size_t pick_k(mapra::Vector&, size_t);

bool is_finished(mapra::Vector&, mapra::Vector&, size_t, double);

std::tuple<mapra::Vector, double, unsigned int> calculate_eigenvector(
    mapra::Matrix& m, mapra::Vector x0, double eps) {
  // Assert that x0 is not zero
  if (x0.NormMax() == 0) return std::make_tuple(x0, -1, 0);
  unsigned int iterations = 0;
  mapra::Vector x = x0;
  size_t k = 1;
  // Check if it is necessary to pick another k
  k = pick_k(x, k);

  while (true) {
    iterations++;
    // Calculate next x_i based on the given formula:
    // x_i^~ = A * x_{i-1}^~
    mapra::Vector x_next = m * x;

    double lambda = x_next(k);
    // x_i =x_i^~ / x_i(k)
    x_next /= x_next(k);

    if (is_finished(x, x_next, k, eps)) {
      // Iteration has converged
      return std::make_tuple(x_next, lambda, iterations);
    } else {
      // Prepare for next iteration
      x = x_next;
      k = pick_k(x, k);
    }
  }
}

size_t index_of_element(mapra::Vector& vector, double element) {
  for (size_t i = 0; i < vector.GetLength(); i++)
    if (vector(i) == element) return i;

  return 0;
}

// Pick new k, if necessary
size_t pick_k(mapra::Vector& x, size_t old_k) {
  if (C * std::fabs(x(old_k)) <= x.NormMax()) {
    return index_of_element(x, x.NormMax());
  } else {
    return old_k;
  }
}

bool is_finished(mapra::Vector& x_i, mapra::Vector& x_ip1, size_t k,
                 double eps) {
  return (x_ip1 - x_i).NormMax() <= eps && fabs(x_i(k) - x_ip1(k)) <= eps;
}

int main(int argc, char* argv[]) {
  if (argc <= 1) {
    std::cout << "Bitte gib die Nummer eines Beispiels an";
    return 0;
  }

  std::istringstream isstream(argv[1]);
  int example;
  isstream >> example;

  auto [A, x, eps] = mapra::GetExample(example);
  auto [eigVector, eigValue, iterations] = calculate_eigenvector(A, x, eps);
  mapra::CheckSolution(eigVector, eigValue, iterations);
  return 1;
}