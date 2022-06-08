// Copyright (c) 2022, The MaPra Authors.

#ifndef MATRIX_H_
#define MATRIX_H_

#include <cmath>
#include <cstddef>
#include <iostream>
#include <vector>

#include "mapra/vector.h"

namespace mapra {

template <typename T = double>
class Matrix {
 public:
  explicit Matrix(std::size_t r = 1, std::size_t c = 1);

  T& operator()(std::size_t i, std::size_t j) {
#ifndef NDEBUG
  /* hier fehlt das range checking! */
#endif
    return elems_[i + rows_ * j];
  }

  T operator()(std::size_t i, std::size_t j) const {
#ifndef NDEBUG
  /* hier fehlt das range checking! */
#endif
    return elems_[i + rows_ * j];
  }


  Matrix<T>& operator+=(const Matrix<T>&);
  Matrix<T>& operator-=(const Matrix<T>&);
  Matrix<T>& operator*=(const Matrix<T>&);
  Matrix<T>& operator*=(T);
  Matrix<T>& operator/=(T);

  Matrix<T>& Redim(std::size_t, std::size_t);
  std::size_t GetRows() const;
  std::size_t GetCols() const;

  static void MatError(const char str[]);

  friend Matrix<T> operator+(const Matrix<T>&, const Matrix<T>&);
  friend Matrix<T> operator-(const Matrix<T>&, const Matrix<T>&);
  friend Matrix<T> operator-(const Matrix<T>&);

  friend Matrix<T> operator*(const Matrix<T>&, const Matrix<T>&);
  friend Matrix<T> operator*(T, const Matrix<T>&);
  friend Matrix<T> operator*(const Matrix<T>&, T);
  friend Matrix<T> operator/(const Matrix<T>&, T);

  friend bool operator==(const Matrix<T>&, const Matrix<T>&);
  friend bool operator!=(const Matrix<T>&, const Matrix<T>&);

  friend std::istream& operator>>(std::istream&, Matrix<T>&);
  friend std::ostream& operator<<(std::ostream&, const Matrix<T>&);

  friend Vector<T> operator*(const Matrix<T>&, const Vector<T>&);
  friend Vector<T> operator*(const Vector<T>&, const Matrix<T>&);

 private:
  std::size_t rows_;
  std::size_t cols_;
  std::vector<T> elems_;
};

}  // namespace mapra

#endif  // MATRIX_H_
