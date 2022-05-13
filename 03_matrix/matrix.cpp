#include "matrix.h"

#include <iostream>
#include <vector>

#include "vector.h"

// define save-mode to prevent access to non-existant indices
#define SAVE_MODE

#define NOOP

#define ITERATE_MATRIX(m, fun) ITERATE_MATRIX_COL_END(m, fun, NOOP)

#define ITERATE_MATRIX_COL_END(m, fun_each, fun_col_end) \
  for (int i = 0; i < m.GetRows(); i++) {                \
    for (int j = 0; j < m.GetCols(); j++) {              \
      fun_each;                                          \
    }                                                    \
    fun_col_end;                                         \
  }

namespace mapra {

Matrix::Matrix(std::size_t r, std::size_t c) {
  // Constructor of Matrix
  rows_ = r;
  cols_ = c;
  elems_ = std::vector<double>(r * c);
}

double& Matrix::operator()(std::size_t i, std::size_t j) {
  // Return reference of entry A_ij, where i is the row and j is the column
#ifdef SAVE_MODE
  if (i >= GetRows() || j >= GetCols()) throw(1);
#endif
  double& value = elems_[i * GetRows() + j];
  return value;
}

double Matrix::operator()(std::size_t i, std::size_t j) const {
  // Return value of entry A_ij, where i is the row and j is the column
#ifdef SAVE_MODE
  if (i >= GetRows() || j >= GetCols()) throw(1);
#endif
  return elems_[i * GetRows() + j];
};

// M += N
Matrix& Matrix::operator+=(const Matrix& m) {
  ITERATE_MATRIX((*this), (*this)(i, j) += m(i, j));
  return *this;
};
// M -= N
Matrix& Matrix::operator-=(const Matrix& m) {
  ITERATE_MATRIX((*this), (*this)(i, j) -= m(i, j));
  return *this;
};
// M *= N
Matrix& Matrix::operator*=(const Matrix&) { return *this; };
// M *= c??
Matrix& Matrix::operator*=(double) { return *this; };
// M /= c??
Matrix& Matrix::operator/=(double) { return *this; };

Matrix& Matrix::Redim(std::size_t r, std::size_t c) {
  rows_ = r;
  cols_ = c;
  elems_ = std::vector<double>(r * c);
  return *this;
};
std::size_t Matrix::GetRows() const { return rows_; };
std::size_t Matrix::GetCols() const { return cols_; };

void Matrix::MatError(const char str[]){};

// ====== Non member functions =======
// M + N
Matrix operator+(const Matrix& m1, const Matrix& m2) {
  Matrix result(m1.GetRows(), m1.GetCols());
  ITERATE_MATRIX(result, result(i, j) = m1(i, j) + m2(i, j));
  return result;
}
// M - N
Matrix operator-(const Matrix& m1, const Matrix& m2) { return m1 + (-1 * m2); }
// -M
Matrix operator-(const Matrix& m) { return -1 * m; };
// M * N
Matrix operator*(const Matrix&, const Matrix&);
// c * M
Matrix operator*(double c, const Matrix& m) {
  int rows = m.GetRows();
  int cols = m.GetCols();
  Matrix result(m.GetRows(), m.GetCols());
  ITERATE_MATRIX(result, result(i, j) = c * m(i, j));
  return result;
}
// M * c ??
Matrix operator*(const Matrix& m, double c) { return m; };
// M / c ??
Matrix operator/(const Matrix& m, double c) { return m; };

// M == N
bool operator==(const Matrix& m1, const Matrix& m2) {
  ITERATE_MATRIX(m1, if (m1(i, j) != m2(i, j)) return false;);
  return true;
};
// M != N
bool operator!=(const Matrix& m1, const Matrix& m2) { return !(m1 == m2); };

std::ostream& operator<<(std::ostream& out, const Matrix& m) {
  ITERATE_MATRIX_COL_END(m, out << m(i, j), out << std::endl)
  return out;
};
std::istream& operator>>(std::istream& in, Matrix& m) { return in; };

// v * M
Vector operator*(const Vector& v, const Matrix& m) { return v * m; }
// M * v
Vector operator*(const Matrix& m, const Vector& v) { return m * v; }

}  // namespace mapra

int main() {
  mapra::Matrix m1(2, 2);
  mapra::Matrix m2(2, 2);
  m1(0, 0) = 10;
  m2(1, 1) = 5;
  m1 += m2;

  mapra::Matrix mm = -m1;
  return 0;
}