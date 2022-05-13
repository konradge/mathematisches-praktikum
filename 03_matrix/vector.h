// Copyright (c) 2022, The MaPra Authors.

#ifndef VECTOR_H_
#define VECTOR_H_

#include <cstddef>
#include <iostream>
#include <vector>

namespace mapra {

class Vector {
 public:
  explicit Vector(std::size_t len = 1);

  double& operator()(std::size_t);
  double operator()(std::size_t) const;

  Vector& operator+=(const Vector&);
  Vector& operator-=(const Vector&);
  Vector& operator*=(double);
  Vector& operator/=(double);

  Vector& Redim(std::size_t);
  std::size_t GetLength() const;
  double Norm2() const;
  double NormMax() const;

  static void VecError(const char str[]);

  friend Vector operator+(const Vector&, const Vector&);
  friend Vector operator-(const Vector&, const Vector&);
  friend Vector operator-(const Vector&);

  friend double operator*(const Vector&, const Vector&);
  friend Vector operator*(double, const Vector&);
  friend Vector operator*(const Vector&, double);
  friend Vector operator/(const Vector&, double);

  friend bool operator==(const Vector&, const Vector&);
  friend bool operator!=(const Vector&, const Vector&);

  friend std::istream& operator>>(std::istream&, Vector&);
  friend std::ostream& operator<<(std::ostream&, const Vector&);

 private:
  std::vector<double> elems_;
};

}  // namespace mapra

#endif  // VECTOR_H_
