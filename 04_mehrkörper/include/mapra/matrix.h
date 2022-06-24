// Copyright (c) 2022, The MaPra Authors.

#ifndef MATRIX_H_
#define MATRIX_H_

#include <cmath>
#include <cstddef>
#include <iostream>
#include <vector>

#include "mapra/vector.h"

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

template <typename T>
class Matrix {
 public:
  explicit Matrix(std::size_t r = 1, std::size_t c = 1) {
    // Constructor of Matrix<T>
    rows_ = r;
    cols_ = c;
    elems_.resize(r * c, 0);
  };

  T &operator()(std::size_t i, std::size_t j) {
#ifndef NDEBUG
    if (i >= rows_ || j >= cols_) MatError("Index is too big");
#endif
    return elems_[i + rows_ * j];
  }

  T operator()(std::size_t i, std::size_t j) const {
#ifndef NDEBUG
    if (i >= rows_ || j >= cols_) MatError("Index is too big");
#endif
    return elems_[i + rows_ * j];
  }

  Matrix<T> &operator+=(const Matrix<T> &m) {
#ifndef NDEBUG
    if (!(GetRows() == m.GetRows() && GetCols() == m.GetCols()))
      Matrix<T>::MatError(
          "Inkompatible Dimensionen fuer 'Matrix<T> + Matrix<T>'!");
#endif
    ITERATE_MATRIX((*this), (*this)(i, j) += m(i, j));
    return *this;
  }
  Matrix<T> &operator-=(const Matrix<T> &m) {
#ifndef NDEBUG
    if (!(GetRows() == m.GetRows() && GetCols() == m.GetCols()))
      Matrix<T>::MatError(
          "Inkompatible Dimensionen fuer 'Matrix<T> - Matrix<T>'!");
#endif
    ITERATE_MATRIX((*this), (*this)(i, j) -= m(i, j));
    return *this;
  }

  Matrix<T> &operator*=(const Matrix<T> &m) {
#ifndef NDEBUG
    if (!(GetCols() == m.GetRows()))
      Matrix<T>::MatError(
          "Inkompatible Dimensionen fuer 'Matrix<T> * Matrix<T>'!");
#endif
    Matrix<T> copy(*this);
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

  Matrix<T> &operator*=(T c) {
    c *(*this);
    return *this;
  }

  Matrix<T> &operator/=(T c) {
    ((T)1 / c) * (*this);
    return *this;
  }

  Matrix<T> &Redim(std::size_t r, std::size_t c) {
    rows_ = r;
    cols_ = c;
    elems_.resize(r * c);
    return *this;
  }

  Matrix<T> &Redim(std::size_t r, std::size_t c, T defaultValue) {
    Redim(r, c);
    for (size_t i = 0; i < elems_.size(); i++) {
      elems_[i] = defaultValue;
    }
    return *this;
  }

  std::size_t GetRows() const { return rows_; }
  std::size_t GetCols() const { return cols_; }

  static void MatError(const char str[]) {
    std::cerr << "\nMatrix<T>fehler: " << str << '\n' << std::endl;
    exit(1);
  }

  friend Matrix<T> operator+(const Matrix<T> &m1, const Matrix<T> &m2) {
    Matrix<T> result(m1);
    result += m2;
    return result;
  }

  friend Matrix<T> operator-(const Matrix<T> &m1, const Matrix<T> &m2) {
    return m1 + -m2;
  }

  friend Matrix<T> operator-(const Matrix<T> &m) { return -1 * m; }

  friend Matrix<T> operator*(const Matrix<T> &m1, const Matrix<T> &m2) {
    Matrix<T> result;
    result = m1;
    result *= m2;
    return result;
  }

  friend Matrix<T> operator*(T c, const Matrix<T> &m) {
    Matrix<T> result(m.GetRows(), m.GetCols());
    ITERATE_MATRIX(result, result(i, j) = c * m(i, j));
    return result;
  }
  friend Matrix<T> operator*(const Matrix<T> &m, T c) { return c * m; }
  friend Matrix<T> operator/(const Matrix<T> &m, T c) {
    return ((T)1 / c) * m;
  }

  friend bool operator==(const Matrix<T> &m1, const Matrix<T> &m2) {
    if (!(m1.GetRows() == m2.GetRows() && m1.GetCols() == m2.GetCols()))
      return false;
    ITERATE_MATRIX(m1, if (m1(i, j) != m2(i, j)) return false);
    return true;
  }

  friend bool operator!=(const Matrix<T> &m1, const Matrix<T> &m2) {
    return !(m1 == m2);
  }

  friend std::istream &operator>>(std::istream &in, Matrix<T> &m) {
    std::cout << std::setiosflags(std::ios::right);
    for (size_t i = 0; i < m.GetCols(); i++) {
      for (size_t j = 0; j < m.GetRows(); j++) {
        std::cout << "\n(" << std::setw(4) << i << ") " << std::flush;
        in >> m(i, j);
      }
    }
    return in;
  }

  friend std::ostream &operator<<(std::ostream &out, const Matrix<T> &m) {
    ITERATE_MATRIX_COL_END(m, out << m(i, j) << "\t", out << std::endl)
    return out;
  }

  friend Vector<T> operator*(const Matrix<T> &m, const Vector<T> &v) {
    Matrix<T> vAsMatrix = VectorTo1xNMatrix(v);
    vAsMatrix *= m;
    return vAsMatrix.ToVector();
  }

  friend Vector<T> operator*(const Vector<T> &v, const Matrix<T> &m) {
    Matrix<T> vAsMatrix = VectorToMx1Matrix(v);
    vAsMatrix = m * vAsMatrix;
    return vAsMatrix.ToVector();
  }

  Vector<T> ToVector() {
#ifndef NDEBUG
    if (GetRows() != 1 && GetCols() != 1) {
      Vector<T>::VecError("Matrix<T> muss 1xn oder mx1 sein!");
    }
#endif
    Vector res(std::max(GetRows(), GetCols()));
    if (GetRows() == 1) {
      for (size_t i = 0; i < GetCols(); i++) {
        res(i) = (*this)(0, i);
      }
    } else {
      for (size_t i = 0; i < GetRows(); i++) {
        res(i) = (*this)(i, 0);
      }
    }
    return res;
  }

 private:
  std::size_t rows_;
  std::size_t cols_;
  std::vector<T> elems_;
};

template <typename T>
Matrix<T> VectorTo1xNMatrix(const Vector<T> &v) {
  Matrix<T> res(1, v.GetLength());
  for (size_t i = 0; i < v.GetLength(); i++) {
    res(0, i) = v(i);
  }
  return res;
}

template <typename T>
Matrix<T> VectorToMx1Matrix(const Vector<T> &v) {
  Matrix<T> res(v.GetLength(), 1);
  for (size_t i = 0; i < v.GetLength(); i++) {
    res(i, 0) = v(i);
  }
  return res;
}

}  // namespace mapra

#endif  // MATRIX_H_
