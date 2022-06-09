// Copyright (c) 2022, The MaPra Authors.

#ifndef VECTOR_H_
#define VECTOR_H_

#include <algorithm>
#include <cmath>
#include <cstddef>
#include <iomanip>
#include <iostream>
#include <vector>

namespace mapra {

template <typename T = double>
class Vector {
 public:
  explicit Vector(std::size_t len = 1) : elems_(len, 0){};

  T& operator()(std::size_t i) {
#ifndef NDEBUG
    if (i >= elems_.size()) {
      Vector::VecError("Ungueltiger Index!");
    }
#endif

    return elems_[i];
  }

  T operator()(std::size_t i) const {
#ifndef NDEBUG
    if (i >= elems_.size()) {
      Vector::VecError("Ungueltiger Index!");
    }
#endif

    return elems_[i];
  }

  Vector<T>& operator+=(const Vector<T>& x) {
#ifndef NDEBUG
    if (x.elems_.size() != (*this).GetLength()) {
      Vector<T>::VecError("Inkompatible Dimensionen fuer 'Vektor + Vektor'!");
    }
#endif

    for (size_t i = 0; i < x.GetLength(); i++) {
      (*this)(i) += x(i);
    }

    return (*this);
  }

  Vector<T>& operator-=(const Vector<T>& x) {
#ifndef NDEBUG
    if (x.GetLength() != GetLength()) {
      Vector::VecError("Inkompatible Dimensionen fuer 'Vektor - Vektor'!");
    }
#endif

    for (size_t i = 0; i < x.GetLength(); i++) {
      (*this)(i) += -x(i);
    }

    return (*this);
  }

  Vector<T>& operator*=(T c) {
    for (size_t i = 0; i < GetLength(); i++) {
      (*this)(i) *= c;
    }

    return (*this);
  }

  Vector<T>& operator/=(T c) {
    for (size_t i = 0; i < GetLength(); i++) {
      (*this)(i) /= c;
    }

    return (*this);
  }

  Vector<T>& Redim(std::size_t l) {
    elems_ = std::vector<double>(l, 0);
    return (*this);
  }

  std::size_t GetLength() const { return elems_.size(); }

  T Norm2() const {
    double squaresum = 0;

    for (size_t i = 0; i < (*this).GetLength(); i++) {
      squaresum += pow((*this)(i), 2);
    }

    return sqrt(squaresum);
  }

  T NormMax() const {
    double max = fabs((*this)(0));

    for (size_t i = 1; i < (*this).GetLength(); i++) {
      if (fabs((*this)(i)) > max) max = fabs((*this)(i));
    }

    return max;
  }

  static void VecError(const char str[]) {
    std::cerr << "\nVektorfehler: " << str << '\n' << std::endl;
    exit(1);
  }

  friend Vector<T> operator+(const Vector<T>& x, const Vector<T>& y) {
#ifndef NDEBUG
    if (x.elems_.size() != y.elems_.size()) {
      Vector::VecError("Inkompatible Dimensionen fuer 'Vektor + Vektor'!");
    }
#endif

    Vector<T> z = x;
    return z += y;
  }

  friend Vector<T> operator-(const Vector<T>& x, const Vector<T>& y) {
#ifndef NDEBUG
    if (x.elems_.size() != y.elems_.size()) {
      Vector<T>::VecError("Inkompatible Dimensionen fuer 'Vektor - Vektor'!");
    }
#endif

    Vector<T> z = x;
    return z -= y;
  }

  friend Vector<T> operator-(const Vector<T>& x) {
    Vector v(x.GetLength());
    for (size_t i = 0; i < x.GetLength(); i++) {
      v(i) = -x(i);
    }
    return v;
  }

  friend T operator*(const Vector<T>& x, const Vector<T>& y) {
#ifndef NDEBUG
    if (x.GetLength() != y.GetLength()) {
      Vector::VecError("Inkompatible Dimensionen fuer 'Vektor x Vektor'!");
    }
#endif
    T multsum = 0;

    for (size_t i = 0; i < x.GetLength(); i++) {
      multsum += x(i) * y(i);
    }

    return multsum;
  }

  friend Vector<T> operator*(T c, const Vector<T>& x) {
    Vector multiplied(x);

    multiplied *= c;
    return multiplied;
  }

  friend Vector<T> operator*(const Vector<T>& x, T c) { return c * x; }

  friend Vector<T> operator/(const Vector<T>& x, T c) {
    Vector multiplied(x);

    multiplied /= c;
    return multiplied;
  }

  friend bool operator==(const Vector<T>& x, const Vector<T>& y) {
    if (x.elems_.size() != y.elems_.size()) {
      return false;
    }

    for (size_t i = 0; i < x.elems_.size(); i++) {
      if (x(i) != y(i)) {
        return false;
      }
    }

    return true;
  }

  friend bool operator!=(const Vector<T>& x, const Vector<T>& y) {
    return !(x == y);
  }

  friend std::istream& operator>>(std::istream& s, Vector<T>& x) {
    std::cout << std::setiosflags(std::ios::right);
    for (size_t i = 0; i < x.elems_.size(); i++) {
      std::cout << "\n(" << std::setw(4) << i << ") " << std::flush;
      s >> x(i);
    }
    return s;
  }

  friend std::ostream& operator<<(std::ostream& s, const Vector<T>& x) {
    s << std::setiosflags(std::ios::right);
    for (size_t i = 0; i < x.elems_.size(); i++) {
      s << "\n(" << std::setw(4) << i << ") " << x(i);
    }

    return s << std::endl;
  }

 private:
  std::vector<T> elems_;
};

}  // namespace mapra

#endif  // VECTOR_H_
