// Copyright (c) 2022, The MaPra Authors.

#include "vector.h"

#include <algorithm>
#include <cmath>
#include <iostream>
#include <vector>

// =======================
//      Konstruktoren
// =======================

// ----- Konstruktor -----

mapra::Vector::Vector(size_t len) : elems_(len, 0) {}

// ===========================================
//      Vektorelement schreiben und lesen
// ===========================================

// ----- Schreib- und Lesezugriff auf Vektorelemente -----

double& mapra::Vector::operator()(size_t i) {
#ifndef NDEBUG
  if (i >= elems_.size()) {
    mapra::Vector::VecError("Ungueltiger Index!");
  }
#endif

  return elems_[i];
}

// ----- Lesezugriff auf Elemente konstanter Vektoren -----

double mapra::Vector::operator()(size_t i) const {
#ifndef NDEBUG
  if (i >= elems_.size()) {
    mapra::Vector::VecError("Ungueltiger Index!");
  }
#endif

  return elems_[i];
}

// =====================
//      Zuweisungen
// =====================

// ----- Zuweisungsoperator mit Addition "+=" ----

mapra::Vector& mapra::Vector::operator+=(const mapra::Vector& x) {
  // ***** Hier fehlt was *****
}

// ----- Zuweisungsoperator mit Subtraktion "-=" ----

mapra::Vector& mapra::Vector::operator-=(const mapra::Vector& x) {
  // ***** Hier fehlt was *****
}

// ----- Zuweisungsoperator mit Multiplikation "*=" ----

mapra::Vector& mapra::Vector::operator*=(double c) {
  // ***** Hier fehlt was *****
}

// ----- Zuweisungsoperator mit Divsion "/=" ----

mapra::Vector& mapra::Vector::operator/=(double c) {
  // ***** Hier fehlt was *****
}

// ==============================
//      Vektorlaenge aendern
// ==============================

// ----- Vektorlaenge aendern -----

mapra::Vector& mapra::Vector::Redim(size_t l) {
  // ***** Hier fehlt was *****
}

std::size_t mapra::Vector::GetLength() const { return elems_.size(); }

// ======================
//      Vektornormen
// ======================

// ----- Euklidische Norm -----

double mapra::Vector::Norm2() const {
  // ***** Hier fehlt was *****
}

// ----- Maximum-Norm -----

double mapra::Vector::NormMax() const {
  // ***** Hier fehlt was *****
}

// ==================================
//      arithmetische Operatoren
// ==================================

// ----- Addition "+" -----

mapra::Vector mapra::operator+(const mapra::Vector& x, const mapra::Vector& y) {
#ifndef NDEBUG
  if (x.elems_.size() != y.elems_.size()) {
    mapra::Vector::VecError("Inkompatible Dimensionen fuer 'Vektor + Vektor'!");
  }
#endif

  mapra::Vector z = x;
  return z += y;
}

// ----- Subtraktion "-" -----

mapra::Vector mapra::operator-(const mapra::Vector& x, const mapra::Vector& y) {
  // ***** Hier fehlt was *****
}

// ----- Vorzeichen wechseln "-" -----

mapra::Vector mapra::operator-(const mapra::Vector& x) {
  // ***** Hier fehlt was *****
}

// ----- Skalarprodukt "*" -----

double mapra::operator*(const mapra::Vector& x, const mapra::Vector& y) {
  // ***** Hier fehlt was *****
}

// ----- Multiplikation Skalar*Vektor "*" -----

mapra::Vector mapra::operator*(double c, const mapra::Vector& x) {
  // ***** Hier fehlt was *****
}

// ----- Multiplikation Vektor*Skalar "*" -----

mapra::Vector mapra::operator*(const mapra::Vector& x, double c) {
  // ***** Hier fehlt was *****
}

// ----- Division Vektor/Skalar "/" -----

mapra::Vector mapra::operator/(const mapra::Vector& x, double c) {
  // ***** Hier fehlt was *****
}

// ==============================
//      Vergleichsoperatoren
// ==============================

// ----- Test auf Gleichheit "==" -----

bool mapra::operator==(const mapra::Vector& x, const mapra::Vector& y) {
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

bool mapra::operator!=(const mapra::Vector& x, const mapra::Vector& y) {
  // ***** Hier fehlt was *****
}

// ==========================
//      Ein- und Ausgabe
// ==========================

// ----- Ausgabe "<<" -----

std::ostream& mapra::operator<<(std::ostream& s, const mapra::Vector& x) {
  s << std::setiosflags(std::ios::right);
  for (size_t i = 0; i < x.elems_.size(); i++) {
    s << "\n(" << std::setw(4) << i << ") " << x(i);
  }

  return s << std::endl;
}

// ----- Eingabe ">>" -----

std::istream& mapra::operator>>(std::istream& s, mapra::Vector& x) {
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

void mapra::Vector::VecError(const char str[]) {
  std::cerr << "\nVektorfehler: " << str << '\n' << std::endl;
  exit(1);
}
