// Copyright (c) 2022, The MaPra Authors.

#ifndef VECTOR_H_
#define VECTOR_H_

#include <cstddef>
#include <iostream>
#include <vector>

namespace mapra {

template <typename T = double>
class Vector {
 public:
  explicit Vector(std::size_t len = 1);

  T& operator()(std::size_t);
  T operator()(std::size_t) const;

  Vector<T>& operator+=(const Vector<T>&);
  Vector<T>& operator-=(const Vector<T>&);
  Vector<T>& operator*=(T);
  Vector<T>& operator/=(T);

  Vector<T>& Redim(std::size_t);
  std::size_t GetLength() const;
  T Norm2() const;
  T NormMax() const;

  static void VecError(const char str[]);

  friend Vector<T> operator+(const Vector<T>&, const Vector<T>&);
  friend Vector<T> operator-(const Vector<T>&, const Vector<T>&);
  friend Vector<T> operator-(const Vector<T>&);

  friend T operator*(const Vector<T>&, const Vector<T>&);
  friend Vector<T> operator*(T, const Vector<T>&);
  friend Vector<T> operator*(const Vector<T>&, T);
  friend Vector<T> operator/(const Vector<T>&, T);

  friend bool operator==(const Vector<T>&, const Vector<T>&);
  friend bool operator!=(const Vector<T>&, const Vector<T>&);

  friend std::istream& operator>>(std::istream&, Vector<T>&);
  friend std::ostream& operator<<(std::ostream&, const Vector<T>&);

 private:
  std::vector<T> elems_;
};

}  // namespace mapra

#endif  // VECTOR_H_
