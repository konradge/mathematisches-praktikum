// Copyright (c) 2022, The MaPra Authors.

#ifndef MATRIX_H_
#define MATRIX_H_

#include <cstddef>
#include <iostream>
#include <vector>

#include "vector.h"

namespace mapra {

class Matrix {
 public:
  explicit Matrix(std::size_t r = 1, std::size_t c = 1);

  double& operator()(std::size_t, std::size_t);
  double operator()(std::size_t, std::size_t) const;

  Matrix& operator+=(const Matrix&);
  Matrix& operator-=(const Matrix&);
  Matrix& operator*=(const Matrix&);
  Matrix& operator*=(double);
  Matrix& operator/=(double);

  Matrix& Redim(std::size_t, std::size_t);
  std::size_t GetRows() const;
  std::size_t GetCols() const;

  static void MatError(const char str[]);

  friend Matrix operator+(const Matrix&, const Matrix&);
  friend Matrix operator-(const Matrix&, const Matrix&);
  friend Matrix operator-(const Matrix&);

  friend Matrix operator*(const Matrix&, const Matrix&);
  friend Matrix operator*(double, const Matrix&);
  friend Matrix operator*(const Matrix&, double);
  friend Matrix operator/(const Matrix&, double);

  friend bool operator==(const Matrix&, const Matrix&);
  friend bool operator!=(const Matrix&, const Matrix&);

  friend std::istream& operator>>(std::istream&, Matrix&);
  friend std::ostream& operator<<(std::ostream&, const Matrix&);

  friend Vector operator*(const Matrix&, const Vector&);
  friend Vector operator*(const Vector&, const Matrix&);

 private:
  std::size_t rows_;
  std::size_t cols_;
  std::vector<double> elems_;
};

}  // namespace mapra

#endif  // MATRIX_H_
