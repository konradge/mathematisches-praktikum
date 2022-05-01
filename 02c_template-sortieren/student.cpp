// Copyright (c) 2022, The MaPra Authors.

#include "student.h"

#include <string>

// Eingabeoperator ">>"
std::istream& mapra::operator>>(std::istream& s, mapra::Student& a) {
  s >> a.first_name >> a.last_name >> a.matr_nr >> a.grade;
  return s;
}

// Ausgabeoperator "<<"
std::ostream& mapra::operator<<(std::ostream& s, const mapra::Student& a) {
  s << a.first_name << " " << a.last_name << " " << a.matr_nr << " " << a.grade;
  return s;
}

// Vergleichsoperator "<"
bool mapra::operator<(const mapra::Student& s1, const mapra::Student& s2) {
  return s1.last_name < s2.last_name ||
         (s1.last_name == s2.last_name && s1.first_name < s2.first_name);
}

// Vergleichsoperator ">"
bool mapra::operator>(const mapra::Student& s1, const mapra::Student& s2) {
  return !(s1 < s2) && !(s1 == s2);
}

// Vergleichsoperator "<="
bool mapra::operator<=(const mapra::Student& s1, const mapra::Student& s2) {
  return !(s1 > s2);
}

// Vergleichsoperatoren "==" bzw. "!="
bool mapra::operator==(const mapra::Student& s1, const mapra::Student& s2) {
  return s1.last_name == s2.last_name && s1.first_name == s2.first_name;
}

bool mapra::operator!=(const mapra::Student& s1, const mapra::Student& s2) {
  return !(s1 == s2);
}
