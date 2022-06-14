// Copyright (c) 2022, The MaPra Authors.

#include <iostream>

#include "mapra/matrix.h"
#include "mapra/unit.h"
#include "mapra/vector.h"

void RkStep(VFFunction f, real& t, RealVector& y, real& h);

int main() {
  auto [mass, fun, y_0, t_begin, t_end, h_0] = mapra::GetExample(1, true, true);

  if (mass.Norm2() != 0) {
    // Mass is not the 0-Vector => fun must be calculated
    std::cout << "Function is being calculated" << std::endl;

    // TODO: Calculate fun based on the masses
  }

  while (t_begin + h_0 <= t_end) {
    RkStep(fun, t_begin, y_0, h_0);
    std::cout << "Checking step..." << std::endl;
    mapra::CheckStep(t_begin, y_0, true);
    std::cout << "Check completed" << std::endl;
  }

  // Last step to prevent calculating y for bigger t than t_end
  if (t_begin != t_end) {
    real h = t_end - t_begin;
    RkStep(fun, t_begin, y_0, h);
  }

  mapra::CheckSolution(t_begin, y_0);

  return 0;
}

// f: R^{n+1} \to R^m
// y ist der Funktionswert der Funktion y: R^1 \to R^n an der Stelle y(t)
void RkStep(VFFunction f, real& t, RealVector& y, real& h) {
  /** Calculate K_j's **/
  const size_t n = y.GetLength();
  const size_t m = mapra::rk_gamma.GetLength();

  std::vector<RealVector> K(m);
  for (size_t j = 0; j < m; j++) {
    K[j].Redim(n);
    RealVector sum;
    for (size_t l = 0; l < j - 1 && j != 0; l++) {
      sum += mapra::rk_beta(j, l) * K[l];
    }
    K[j] = f(t + mapra::rk_alpha(j) * h, y);
  }
  RealVector k_sum(n);
  for (size_t l = 1; l < m; l++) {
    k_sum += mapra::rk_gamma(l) * K[l];
  }
  // Get value of y(t+h)
  auto y_new = y + h * k_sum;

  /** Update Parameters **/
  t += h;
  y = y_new;
  /* Update h */
  // e(t+h)
  // TODO: Wie berechnet man y quer??
  const RealVector e_th = y - y;
  const real eps = e_th.NormMax();
  const real eps_max = mapra::eps;
  const real c = 0.9 * pow(eps_max / eps, (real)1 / (mapra::rk_p + 1));
  if (c < 0.1) {
    h = 0.1;
  } else if (c > 5) {
    h = 5;
  } else {
    h = c;
  }

  // Recalculate Step with updated h, if error was too big
  if (eps > eps_max) {
    std::cout << "Recalculate step" << std::endl;
    RkStep(f, t, y, h);
  }
}
