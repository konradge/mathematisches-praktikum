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

  if (mass.Norm2() != 0) {
    // Mass is not the 0-Vector => fun must be calculated
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
  // y_0 that we get from the example corresponds with the entire y vector
  // from the example. t remains unused in "Mehrkörperproblem"
  return [m](real, const RealVector& y) {
    size_t half_length = y.GetLength() / 2;
    RealVector res(y.GetLength());
    // copies y1 from the bottom of y to the top of the res vector
    for (size_t i = 0; i < half_length; i++) {
      res(i) = y(i + half_length);
    }
    // computes f(y0) to put on the bottom of res
    // first we group the values into vectors of two so we can apply formula
    
    for (size_t i = 0; i < half_length; i = i + 2) {
      RealVector xi(2);
      xi(0) = y(i);
      xi(1) = y(i + 1);
      RealVector newx(2);
      for (size_t j = 0; j < half_length; j = j + 2) {
        if (j != i) {
          RealVector xj(2);
          xj(0) = y(j);
          xj(1) = y(j + 1);
          real norm = (xj - xi).Norm2();
          newx += (m(j / 2) / pow(norm, 3)) * (xj - xi); 
        }
      }
      newx = mapra::kGrav * newx;
      res(i + half_length) = newx(0);
      res(i + half_length + 1) = newx(1);
    }
    return res;
  };
}

// f: R^{n+1} \to R^n
// y ist der Funktionswert der Funktion y: R^1 \to R^n an der Stelle y(t)
void RkStep(const VFFunction& f, real& t, RealVector& y, real& h,
            const real& t_end) {
  // std::cout << "Execute step" << std::endl;
  bool last_step = false;
  if (t + h > t_end) {
    h = t_end - t;
    last_step = true;
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
  if(!last_step) {
    RealVector delta_sum(n);
    for (size_t l = 1; l <= m; l++) {
      delta_sum += mapra::rk_delta(l - 1) * K[l - 1];
    }
    const RealVector e_th = h * delta_sum;
    const real eps = e_th.NormMax();
    const real eps_max = mapra::eps;

    const real c = 0.9 * pow(eps_max / eps, (real)1 / (mapra::rk_p + 1));

    if (c < 0.1) {
      h *= 0.1;
    } else if (c > 5) {
      h *= 5;
    } else {
      h *= c;
    }

    // Recalculate Step with updated h, if error was too big
    if (eps > eps_max) {
      t = old_t;
      RkStep(f, t, y, h, t_end);
    } else {
      y = y_new;
    }
  } else {
    y = y_new;
  }
}
