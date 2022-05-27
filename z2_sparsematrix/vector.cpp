/************************************************
 *  Name       : vektor.cpp                     *
 *  Verwendung : Vektorklasse                   *
 *  Autor      :                                *
 *  Datum      :                                *
 ************************************************/

#include "vector.h"

#include <cmath>
#include <cstdlib>
#include <iomanip>

// =======================
//      Konstruktoren
// =======================

// ----- Konstruktor -----

Vector::Vector(size_t l) {
#ifndef NDEBUG
  if (l <= 0) vecError("Nur Vektoren mit positiver Laenge!");
#endif

  length = l;

  vec = new double[l];
  if (vec == NULL) vecError("Nicht genuegend Speicher!");

  for (size_t i = 0; i < l; i++) (*this)(i) = 0;
}

// ----- Destruktor -----

Vector::~Vector() {
  // Free space on heap
  delete[] vec;
}

// ----- Kopierkonstruktor -----

Vector::Vector(const Vector &x) {
  length = x.length;

  vec = new double[length];
  if (vec == NULL) vecError("Nicht genuegend Speicher!");

  for (size_t i = 0; i < length; i++) (*this)(i) = x(i);
}

// ===========================================
//      Vektorelement schreiben und lesen
// ===========================================

// ----- Standardzugriff auf Vektorelemente -----

double &Vector::operator()(size_t i) {
#ifndef NDEBUG
  if (i >= length) vecError("Ungueltiger Index!");
#endif

  return vec[i];
}

// ----- Lesezugriff auf Elemente eines const Vektors -----

double Vector::operator()(size_t i) const {
#ifndef NDEBUG
  if (i >= length) vecError("Ungueltiger Index!");
#endif

  return vec[i];
}

// =====================
//      Zuweisungen
// =====================

// ----- Zuweisungsoperator "=" ----

Vector &Vector::operator=(const Vector &x) {
  if (length != x.length) {
    delete[] vec;
    length = x.getLength();
    vec = new (std::nothrow) double[length];
    if (vec == NULL) vecError("Nicht genuegend Speicher!");
  }

  for (size_t i = 0; i < length; i++) (*this)(i) = x(i);

  return *this;
}

// ----- Zuweisungsoperator mit Addition "+=" ----

Vector &Vector::operator+=(const Vector &x) {
#ifndef NDEBUG
  if (x.getLength() != getLength()) vecError("Illegal dimensions");
#endif
  for (size_t i = 0; i < getLength(); i++) {
    (*this)(i) += x(i);
  }
  return *this;
}

// ----- Zuweisungsoperator mit Subtraktion "-=" ----

Vector &Vector::operator-=(const Vector &x) {
#ifndef NDEBUG
  if (x.getLength() != getLength()) vecError("Illegal dimensions");
#endif

  (*this) += -1 * x;
  return *this;
}

// ----- Zuweisungsoperator mit Multiplikation "*=" ----

Vector &Vector::operator*=(double c) {
  for (size_t i = 0; i < getLength(); i++) {
    (*this)(i) *= c;
  }
  return *this;
}

// ----- Zuweisungsoperator mit Divsion "/=" ----

Vector &Vector::operator/=(double c) {
  (*this) *= (1 / c);
  return *this;
}

// ==============================
//      Vektorlaenge aendern
// ==============================

// ----- Vektorlaenge aendern -----

Vector &Vector::redim(size_t l) {
  length = l;
  delete[] vec;
  vec = new double[l];
  if (vec == NULL) vecError("Nicht genuegend Speicher!");
  return *this;
}

// ======================
//      Vektornormen
// ======================

// ----- Euklidische Norm -----

double Vector::norm2() const {
  double res = 0;
  for (size_t i = 0; i < getLength(); i++) {
    res += fabs((*this)(i));
  }
  return res;
}

// ----- Maximum-Norm -----

double Vector::normMax() const {
  double res = 0;
  for (size_t i = 0; i < getLength(); i++) {
    if (fabs((*this)(i)) > res) {
      res = fabs((*this)(i));
    }
  }
  return res;
}

// ==================================
//      arithmetische Operatoren
// ==================================

// ----- Addition "+" -----

Vector operator+(const Vector &x, const Vector &y) {
  Vector res(x);
  res += y;
  return res;
}

// ----- Subtraktion "-" -----

Vector operator-(const Vector &x, const Vector &y) {
  Vector res(x);
  res -= y;
  return res;
}

// ----- Vorzeichen wechseln "-" -----

Vector operator-(const Vector &x) {
  Vector res(x);
  res *= -1;
  return res;
}

// ----- Skalarprodukt "*" -----

double operator*(const Vector &x, const Vector &y) {
#ifndef NDEBUG
  if (x.getLength() != y.getLength()) Vector::vecError("Illegal dimensions");
#endif
  double res = 0;
  for (size_t i = 0; i < x.getLength(); i++) {
    res += x(i) * y(i);
  }
  return res;
}

// ----- Multiplikation Skalar*Vector "*" -----

Vector operator*(double c, const Vector &x) {
  Vector res(x);
  res *= c;
  return res;
}

// ----- Multiplikation Vector*Skalar "*" -----

Vector operator*(const Vector &x, double c) { return c * x; }

// ----- Division Vector/Skalar "/" -----

Vector operator/(const Vector &x, double c) { return ((double)1 / c) * x; }

// ----- Division Vector/Vector "/"  <-->  D^(-1)*x -----

Vector operator/(const Vector &x, const Vector &d) {
  // ???
  return x + d;
}

// ----- Vector*.Vector "%"  <--> komponentenweise Multiplikation -----

Vector operator%(const Vector &x, const Vector &d) {
  // ???
  return x + d;
}

// ==============================
//      Vergleichsoperatoren
// ==============================

// ----- Test auf Gleichheit "==" -----

bool operator==(const Vector &x, const Vector &y) {
  if (x.length != y.length) return false;

  for (size_t i = 0; i < x.length; i++)
    if (x(i) != y(i)) return false;

  return true;
}

// ----- Test auf Ungleichheit "!=" -----

bool operator!=(const Vector &x, const Vector &y) { return !(x == y); }

// ==========================
//      Ein- und Ausgabe
// ==========================

// ----- Ausgabe "<<" -----

std::ostream &operator<<(std::ostream &s, const Vector &x) {
  s << std::setiosflags(std::ios::right);
  for (size_t i = 0; i < x.length; i++)
    s << "\n(" << std::setw(4) << i << ") " << x(i);

  return s << std::endl;
}

// ----- Eingabe ">>" -----

std::istream &operator>>(std::istream &s, Vector &x) {
  std::cout << std::setiosflags(std::ios::right);
  for (size_t i = 0; i < x.length; i++) {
    std::cout << "\n(" << std::setw(4) << i << ") ";
    s >> x(i);
  }
  return s;
}

// ==========================
//      Fehlerbehandlung
// ==========================

// ----- Ausgabe der Fehlermeldung "str" -----

void Vector::vecError(const char str[]) {
  std::cerr << "\nVektorfehler: " << str << '\n' << std::endl;
  std::abort();
}
