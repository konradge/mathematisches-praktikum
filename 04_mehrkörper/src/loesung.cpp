// Copyright (c) 2022, The MaPra Authors.

#include <iostream>

#include "mapra/matrix.h"
#include "mapra/unit.h"
#include "mapra/vector.h"

#define DRAW false

void RkStep(const VFFunction& f, real& t, RealVector& y, real& h,
            const real& t_end);

VFFunction getFunction(const RealVector& m);

int main() {
  std::cout << "Welches Beispiel soll gerechnet werden?" << std::endl;
  int example_id;
  std::cin >> example_id;

  auto [mass, fun, y_0, t_begin, t_end, h_0] =
      mapra::GetExample(example_id, DRAW, DRAW);

  std::cout << "h0:" << h_0 << std::endl;
  std::cout << "t_begin:" << t_begin << std::endl;

  if (mass.Norm2() != 0) {
    // Mass is not the 0-Vector => fun must be calculated
    std::cout << "Function is being calculated" << std::endl;

    fun = getFunction(mass);
  }

  mapra::CheckStep(t_begin, y_0, DRAW);
  while (t_begin < t_end) {
    // std::cout << "\033[1;31m New Step \033[0m\n" << std::endl;
    RkStep(fun, t_begin, y_0, h_0, t_end);
    // std::cout << "REDChecking step..." << std::endl;
    mapra::CheckStep(t_begin, y_0, false);
    // std::cout << "Check completed" << std::endl;
  }

  // Hier ist t_begin genau t_end

  mapra::CheckSolution(t_begin, y_0);

  return 0;
}

VFFunction getFunction(const RealVector& m) {
  return [m](real y_1, const RealVector& y_0) {
    RealVector res(y_0);
    return res;
  };
}

// f: R^{n+1} \to R^n
// y ist der Funktionswert der Funktion y: R^1 \to R^n an der Stelle y(t)
void RkStep(const VFFunction& f, real& t, RealVector& y, real& h,
            const real& t_end) {
  // std::cout << "Execute step" << std::endl;
  if (t + h > t_end) {
    h = t_end - t;
  }
  /** Calculate K_j's **/
  const size_t n = y.GetLength();
  const size_t m = mapra::rk_gamma.GetLength();

  std::vector<RealVector> K(m);
  for (size_t j = 1; j <= m; j++) {
    K[j - 1].Redim(n);
    RealVector sum(n);
    for (size_t l = 1; l <= j - 1; l++) {
      sum += mapra::rk_beta(j - 1, l - 1) * K[l - 1];
    }
    K[j - 1] = f(t + mapra::rk_alpha(j - 1) * h, y + h * sum);
  }
  RealVector k_sum(n);
  for (size_t l = 1; l <= m; l++) {
    k_sum += mapra::rk_gamma(l - 1) * K[l - 1];
  }
  // Get value of y(t+h)
  auto y_new = y + h * k_sum;

  auto old_t = t;

  // Must be calculated here, because later, the h is updated
  t += h;

  // std::cout << "y(" << t + h << ") = " << y_new << std::endl;

  /* Update h */
  // e(t+h)
  RealVector delta_sum(n);
  for (size_t l = 1; l <= m; l++) {
    delta_sum += mapra::rk_delta(l - 1) * K[l - 1];
  }
  const RealVector e_th = h * delta_sum;
  const real eps = e_th.NormMax();
  const real eps_max = mapra::eps;

  const real c = 0.9 * pow(eps_max / eps, (real)1 / (mapra::rk_p + 1));

  std::cout << "c= " << c << std::endl;
  if (c < 0.1) {
    h *= 0.1;
  } else if (c > 5) {
    h *= 5;
  } else {
    h *= c;
  }

  std::cout << "Fehler: " << eps << std::endl;

  // Recalculate Step with updated h, if error was too big
  if (eps > eps_max) {
    std::cout << "Recalculate step with h=" << h << std::endl;
    t = old_t;
    RkStep(f, t, y, h, t_end);
  } else {
    y = y_new;
  }
}
