#include <cmath>

#include "sparse_matrix.h"
#include "unit.h"
#include "vector.h"

bool isSymmetric(Sparse_Matrix& A) {
  if (A.getCols() != A.getRows()) return false;

  for (size_t i = 0; i < A.getCols(); i++) {
    for (size_t j = 0; j < i; j++) {
      if (A(i, j) != A(j, i)) return false;
    }
  }
  return true;
}

double residuum(Sparse_Matrix A, Vector& x, Vector& b) {
  return (b - A * x).norm2();
}

Sparse_Matrix diagonalMatrix(Vector& d) {
  Sparse_Matrix res(d.getLength(), d.getLength());
  for (size_t i = 0; i < d.getLength(); i++) {
    res.put(i, i, d(i));
  }
  return res;
}

int gsv(Sparse_Matrix& A, Vector& b, Vector& x0, const int k_max, double eps) {
  // Konvergenzkriterium überprüfen
  for (size_t i = 0; i < A.getCols(); i++) {
    double sum = 0;
    for (size_t j = 0; j < A.getCols(); j++) {
      if (j != i) {
        sum += fabs(A.get(i, j));
      }
    }
    if (fabs(A.get(i, i)) <= sum) {
      std::cerr << "Matrix ist nicht streng diagonal dominant" << std::endl;
      return 0;
    }
  }
  // Diagnonalmatrix erhalten und aus A löschen
  Vector d(A.getCols());
  for (size_t i = 0; i < A.getCols(); i++) {
    d(i) = A.get(i, i);
    A.put(i, i, 0);
  }
  Vector residuum_vec;
  int k;
  for (k = 0; k < k_max; k++) {
    x0 = (b - (A * x0)) / d;
    double resid = residuum(A + diagonalMatrix(d), x0, b);
    if (resid <= eps) {
      eps = resid;
      break;
    }
  }

  // Restore matrix A
  for (size_t i = 0; i < A.getCols(); i++) {
    A.put(i, i, d(i));
  }

  return k;
}

int cg(Sparse_Matrix& A, Vector& b, Vector& x0, const int k_max, double eps) {
  if (!isSymmetric(A)) {
    std::cerr << "Matrix not symmetric" << std::endl;
    return 0;
  }
  if (A.getCols() != b.getLength() || b.getLength() != x0.getLength()) {
    return -1;
  }
  Vector r = b - A * x0;
  Vector d(r);
  double alpha, beta;
  double norm_r_squared = pow(r.norm2(), 2);
  int k;
  for (k = 0; k < k_max; k++) {
    std::cout << x0 << std::endl;
    // Line 4
    Vector Ad(A * d);
    double scalar_product = Ad * d;
    alpha = norm_r_squared / scalar_product;
    // Line 5
    x0 += alpha * d;
    // Line 6
    r -= alpha * Ad;
    // Line 7
    double norm_r_squared_next = pow(r.norm2(), 2);
    beta = norm_r_squared_next / norm_r_squared;
    // Line 8
    d *= beta;
    d += r;
    // Update ||r||_2^2 for next iteration
    norm_r_squared = norm_r_squared_next;

    if (residuum(A, x0, b) < eps) {
      // Set eps to the reached residuum
      eps = residuum(A, x0, b);
      return k + 1;
    }
  }
  std::cout << "Max iterations reached!" << std::endl;
  // k_max Iterations have been reached
  eps = residuum(A, x0, b);
  return k;
}

int main() {
  Sparse_Matrix A;
  Vector x0, b;
  double tol;
  int max_iter;
  std::cout << num_examples << " Examples" << std::endl;

  for (int i = 1; i <= num_examples; i++) {
      getExample(i, A, x0, b, tol, max_iter);
      int res = gsv(A, b, x0, max_iter, tol);
      checkSolution(x0, res, 0);
  }

  for (int i = 1; i <= num_examples; i++) {
      getExample(i, A, x0, b, tol, max_iter);
      int res = cg(A, b, x0, max_iter, tol);
      checkSolution(x0, res, 1);
  }
  
  return 0;
}