// Copyright (c) 2022, The MaPra Authors.

#include "vector.h"

#include <algorithm>
#include <cmath>
#include <iomanip>
#include <iostream>
#include <vector>

namespace mapra {

// =======================
//      Konstruktoren
// =======================

// ----- Konstruktor -----

Vector::Vector(size_t len) : elems_(len, 0) {}

// Copy constructor
Vector::Vector(const Vector& v) : elems_(v.GetLength(), 0) {
  for (size_t i = 0; i < v.GetLength(); i++) {
    (*this)(i) = v(i);
  }
}

// ===========================================
//      Vektorelement schreiben und lesen
// ===========================================

// ----- Schreib- und Lesezugriff auf Vektorelemente -----

double& Vector::operator()(size_t i) {
#ifndef NDEBUG
  if (i >= elems_.size()) {
    Vector::VecError("Ungueltiger Index!");
  }
#endif

  return elems_[i];
}

// ----- Lesezugriff auf Elemente konstanter Vektoren -----

double Vector::operator()(size_t i) const {
#ifndef NDEBUG
  if (i >= elems_.size()) {
    Vector::VecError("Ungueltiger Index!");
  }
#endif

  return elems_[i];
}

// =====================
//      Zuweisungen
// =====================

// ----- Zuweisungsoperator mit Addition "+=" ----

Vector& Vector::operator+=(const Vector& x) {
#ifndef NDEBUG
  if (x.elems_.size() != (*this).GetLength()) {
    Vector::VecError("Inkompatible Dimensionen fuer 'Vektor + Vektor'!");
  }
#endif

  for (size_t i = 0; i < x.GetLength(); i++) {
    (*this)(i) += x(i);
  }

  return (*this);
}

// ----- Zuweisungsoperator mit Subtraktion "-=" ----

Vector& Vector::operator-=(const Vector& x) {
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

// ----- Zuweisungsoperator mit Multiplikation "*=" ----

Vector& Vector::operator*=(double c) {
  for (size_t i = 0; i < GetLength(); i++) {
    (*this)(i) *= c;
  }

  return (*this);
}

// ----- Zuweisungsoperator mit Divsion "/=" ----

Vector& Vector::operator/=(double c) {
  for (size_t i = 0; i < GetLength(); i++) {
    (*this)(i) /= c;
  }

  return (*this);
}

// ==============================
//      Vektorlaenge aendern
// ==============================

// ----- Vektorlaenge aendern -----

Vector& Vector::Redim(size_t l) {
  elems_ = std::vector<double>(l, 0);
  return (*this);
}

std::size_t Vector::GetLength() const { return elems_.size(); }

// ======================
//      Vektornormen
// ======================

// ----- Euklidische Norm -----

double Vector::Norm2() const {
  double squaresum = 0;

  for (size_t i = 0; i < (*this).GetLength(); i++) {
    squaresum += pow((*this)(i), 2);
  }

  return sqrt(squaresum);
}

// ----- Maximum-Norm -----

double Vector::NormMax() const {
  double max = fabs((*this)(0));

  for (size_t i = 1; i < (*this).GetLength(); i++) {
    if (fabs((*this)(i)) > max) max = fabs((*this)(i));
  }

  return max;
}

// ==================================
//      arithmetische Operatoren
// ==================================

// ----- Addition "+" -----

Vector operator+(const Vector& x, const Vector& y) {
#ifndef NDEBUG
  if (x.elems_.size() != y.elems_.size()) {
    Vector::VecError("Inkompatible Dimensionen fuer 'Vektor + Vektor'!");
  }
#endif

  Vector z = x;
  return z += y;
}

// ----- Subtraktion "-" -----

Vector operator-(const Vector& x, const Vector& y) {
#ifndef NDEBUG
  if (x.elems_.size() != y.elems_.size()) {
    Vector::VecError("Inkompatible Dimensionen fuer 'Vektor - Vektor'!");
  }
#endif

  Vector z = x;
  return z -= y;
}

// ----- Vorzeichen wechseln "-" -----

Vector operator-(const Vector& x) {
  Vector v(x.GetLength());
  for (size_t i = 0; i < x.GetLength(); i++) {
    v(i) = -x(i);
  }
  return v;
}

// ----- Skalarprodukt "*" -----

double operator*(const Vector& x, const Vector& y) {
#ifndef NDEBUG
  if (x.GetLength() != y.GetLength()) {
    Vector::VecError("Inkompatible Dimensionen fuer 'Vektor x Vektor'!");
  }
#endif
  double multsum = 0;

  for (size_t i = 0; i < x.GetLength(); i++) {
    multsum += x(i) * y(i);
  }

  return multsum;
}

// ----- Multiplikation Skalar*Vektor "*" -----

Vector operator*(double c, const Vector& x) {
  Vector multiplied(x);

  multiplied *= c;
  return multiplied;
}

// ----- Multiplikation Vektor*Skalar "*" -----

Vector operator*(const Vector& x, double c) {
  Vector multiplied(x);

  multiplied *= c;
  return multiplied;
}

// ----- Division Vektor/Skalar "/" -----

Vector operator/(const Vector& x, double c) {
  Vector multiplied(x);

  multiplied /= c;
  return multiplied;
}

// ==============================
//      Vergleichsoperatoren
// ==============================

// ----- Test auf Gleichheit "==" -----

bool operator==(const Vector& x, const Vector& y) {
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

// ----- Test auf Ungleichheit "!=" -----

bool operator!=(const Vector& x, const Vector& y) { return !(x == y); }

// ==========================
//      Ein- und Ausgabe
// ==========================

// ----- Ausgabe "<<" -----

std::ostream& operator<<(std::ostream& s, const Vector& x) {
  s << std::setiosflags(std::ios::right);
  for (size_t i = 0; i < x.elems_.size(); i++) {
    s << "\n(" << std::setw(4) << i << ") " << x(i);
  }

  return s << std::endl;
}

// ----- Eingabe ">>" -----

std::istream& operator>>(std::istream& s, Vector& x) {
  std::cout << std::setiosflags(std::ios::right);
  for (size_t i = 0; i < x.elems_.size(); i++) {
    std::cout << "\n(" << std::setw(4) << i << ") " << std::flush;
    s >> x(i);
  }
  return s;
}

// ==========================
//      Fehlerbehandlung
// ==========================

// ----- Ausgabe der Fehlermeldung "str" -----

void Vector::VecError(const char str[]) {
  std::cerr << "\nVektorfehler: " << str << '\n' << std::endl;
  exit(1);
}

}  // namespace mapra