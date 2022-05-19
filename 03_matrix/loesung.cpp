// 3 ist komplett falsch
// 4 falsch skaliert
// 5 hat Probleme mit Iterationen

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
    mapra::Matrix& A, mapra::Vector x0, double eps) {
  // Assert that x0 is not zero
  if (x0.NormMax() == 0) return std::make_tuple(x0, -1, 0);
  unsigned int iterations = 0;
  mapra::Vector x = x0;
  size_t k = 0;
  // Check if it is necessary to pick another k
  k = pick_k(x, k);
  double lambda = x(k);

  while (true) {
    iterations++;
    // Get the next unscaled x_i by multiplying A with the scaled x_{i-1}
    mapra::Vector x_next = A * x;

    // Eigenvalue is the entry at position k in unscaled vector
    double lambda_next = x_next(k);

    // Scale x_next, so that x_next(k) = 1
    x_next /= x_next(k);

    // Check if the iteration has converged
    // 1. Compare the scaled vectors
    bool isFinished = (x_next - x).NormMax() <= eps;
    // 2. Eigenvalue has not changed much
    isFinished = isFinished && fabs(lambda - lambda_next);

    if (isFinished) {
      // Iteration has converged
      std::cout << "k:" << k << std::endl;
      std::cout << "Eigenvalue:" << lambda << std::endl;
      return std::make_tuple(x_next, lambda, iterations);
    } else {
      // Prepare for next iteration
      x = x_next;
      lambda = lambda_next;
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

int main(int argc, char* argv[]) {
  if (argc <= 1) {
    std::cout << "Bitte gib die Nummer eines Beispiels an";
    return 0;
  }

  std::istringstream isstream(argv[1]);
  int example;
  isstream >> example;
  // int example = 2;

  auto [A, x, eps] = mapra::GetExample(example);
  auto [eigVector, eigValue, iterations] = calculate_eigenvector(A, x, eps);
  mapra::CheckSolution(eigVector, eigValue, iterations);
  return 1;
}