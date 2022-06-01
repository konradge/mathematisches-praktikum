#include <cmath>

#include "sparse_matrix.h"
#include "vector.h"

#define K_MAX 200

double residuum(Sparse_Matrix& A, Vector& x, Vector& b) {
  return (b - A * x).norm2();
}

int gsv(Sparse_Matrix A, Vector& b, Vector& x0, const int k_max, double eps) {
  // Konvergenzkriterium überprüfen
  for (size_t i = 0; i < A.getCols(); i++) {
    double sum = 0;
    for (size_t j = 0; j < A.getCols(); j++) {
      if (j != i) {
        sum += fabs(A.get(i, j));
      }
    }
    if (fabs(A.get(i, i)) <= sum) return 0;
  }
  // Diagnonalmatrix erhalten und aus A löschen
  Vector d(A.getCols());
  for (size_t i = 0; i < A.getCols(); i++) {
    d(i) = A.get(i, i);
    A.put(i, i, 0);
  }

  Vector x(x0);
  Vector residuum_vec;
  for (unsigned int k = 0; (k < K_MAX) && (residuum(A, x, b) > eps); k++) {
    x = (b - A * x) / d;
  }

  return 0;
}

void cg(Sparse_Matrix A, Vector& b, Vector& x0, const int k_max, double eps) {
  Vector r = b - A * x0;
  Vector d(r), x(x0);
  double alpha, beta;
  double norm_r_squared = pow(r.norm2(), 2);

  for (int k = 0; (k < K_MAX) && (residuum(A, x, b) > eps); k++) {
    Vector Ad(A * d);
    double energy_scalar_product = Ad * Ad;
    alpha = norm_r_squared / energy_scalar_product;
    x += alpha * d;
    r -= alpha * Ad;
    double norm_r_squared_next = pow(r.norm2(), 2);
    beta = norm_r_squared_next / norm_r_squared;
    d *= beta;
    d += r;
    norm_r_squared = norm_r_squared_next;
  }
}