#include "matrix.h"

#include <iostream>
#include <vector>

#include "vector.h"

// define save-mode to prevent access to non-existant indices
#define NDEBUG

#define NOOP

#define ITERATE_MATRIX(m, fun)                      \
  for (std::size_t i = 0; i < m.GetRows(); i++) {   \
    for (std::size_t j = 0; j < m.GetCols(); j++) { \
      fun;                                          \
    }                                               \
  }

#define ITERATE_MATRIX_COL_END(m, fun_each, fun_col_end) \
  for (std::size_t i = 0; i < m.GetRows(); i++) {        \
    for (std::size_t j = 0; j < m.GetCols(); j++) {      \
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

Matrix::Matrix(const Matrix& m) {
  rows_ = m.GetRows();
  cols_ = m.GetCols();
  ITERATE_MATRIX((*this), (*this)(i, j) = m(i, j));
}

double& Matrix::operator()(std::size_t i, std::size_t j) {
  // Return reference of entry A_ij, where i is the row and j is the column
#ifdef NDEBUG
  if (i >= GetRows() || j >= GetCols()) throw(1);
#endif
  double& value = elems_[i * GetRows() + j];
  return value;
}

double Matrix::operator()(std::size_t i, std::size_t j) const {
  // Return value of entry A_ij, where i is the row and j is the column
#ifdef NDEBUG
  if (i >= GetRows() || j >= GetCols()) throw(1);
#endif
  return elems_[i * GetRows() + j];
}

// M += N
Matrix& Matrix::operator+=(const Matrix& m) {
#ifdef NDEBUG
  if (!(GetRows() == m.GetRows() && GetCols() == m.GetCols())) throw(1);
#endif
  ITERATE_MATRIX((*this), (*this)(i, j) += m(i, j));
  return *this;
}
// M -= N
Matrix& Matrix::operator-=(const Matrix& m) {
#ifdef NDEBUG
  if (!(GetRows() == m.GetRows() && GetCols() == m.GetCols())) throw(1);
#endif
  ITERATE_MATRIX((*this), (*this)(i, j) -= m(i, j));
  return *this;
}
// M *= N
Matrix& Matrix::operator*=(const Matrix& m) {
#ifdef NDEBUG
  if (!(GetCols() == m.GetRows())) throw(1);
#endif
  Matrix copy;
  copy = (*this);
  Redim(GetRows(), m.GetCols());
  for (std::size_t i = 0; i < GetRows(); i++) {
    for (std::size_t j = 0; j < GetCols(); j++) {
      for (std::size_t k = 0; k < copy.GetCols(); k++) {
        (*this)(i, j) += copy(i, k) * m(k, j);
      }
    }
  }
  return *this;
}

// N = M
Matrix& Matrix::operator=(const Matrix& m) {
  Redim(m.GetRows(), m.GetCols());
  ITERATE_MATRIX((*this), (*this)(i, j) = m(i, j));
  return *this;
}
// M *= c??
Matrix& Matrix::operator*=(double c) {
  c*(*this);
  return *this;
}
// M /= c??
Matrix& Matrix::operator/=(double c) {
  ((double)1 / c) * (*this);
  return *this;
}

Matrix& Matrix::Redim(std::size_t r, std::size_t c) {
  rows_ = r;
  cols_ = c;
  elems_ = std::vector<double>(r * c, 0);
  return *this;
}
std::size_t Matrix::GetRows() const { return rows_; }
std::size_t Matrix::GetCols() const { return cols_; }

void Matrix::MatError(const char str[]) {}

// ====== Non member functions =======
// M + N
Matrix operator+(const Matrix& m1, const Matrix& m2) {
#ifdef NDEBUG
  if (!(m1.GetRows() == m2.GetRows() && m1.GetCols() == m2.GetCols())) throw(1);
#endif
  Matrix result(m1);
  result += m2;
  return result;
}
// M - N
Matrix operator-(const Matrix& m1, const Matrix& m2) { return m1 + -m2; }
// -M
Matrix operator-(const Matrix& m) { return -1 * m; }
// M * N
Matrix operator*(const Matrix& m1, const Matrix& m2) {
  Matrix result;
  result = m1;
  result *= m2;
  return result;
}
// c * M
Matrix operator*(double c, const Matrix& m) {
  Matrix result(m.GetRows(), m.GetCols());
  ITERATE_MATRIX(result, result(i, j) = c * m(i, j));
  return result;
}
// M * c ??
Matrix operator*(const Matrix& m, double c) { return c * m; }
// M / c ??
Matrix operator/(const Matrix& m, double c) { return ((double)1 / c) * m; }

// M == N
bool operator==(const Matrix& m1, const Matrix& m2) {
  if (!(m1.GetRows() == m2.GetRows() && m1.GetCols() == m2.GetCols()))
    return false;
  ITERATE_MATRIX(m1, if (m1(i, j) != m2(i, j)) return false);
  return true;
}
// M != N
bool operator!=(const Matrix& m1, const Matrix& m2) { return !(m1 == m2); }

std::ostream& operator<<(std::ostream& out, const Matrix& m) {
  ITERATE_MATRIX_COL_END(m, out << m(i, j) << "\t", out << std::endl)
  return out;
}
std::istream& operator>>(std::istream& in, Matrix& m) {
  // TODO
  return in;
}

// v * M
Vector operator*(const Vector& v, const Matrix& m) { return v * m; }
// M * v
Vector operator*(const Matrix& m, const Vector& v) { return m * v; }

}  // namespace mapra

// int main() {
//   mapra::Matrix m1(1, 2);
//   mapra::Matrix m2(2, 1);
//   m1(0, 0) = 1;
//   m1(0, 1) = 2;
//   m2(0, 0) = 5;
//   m2(1, 0) = 7;

//   m1 *= m2;

//   return 0;
// }