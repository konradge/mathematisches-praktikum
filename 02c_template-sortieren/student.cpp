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
  s << a.first_name << a.last_name << a.matr_nr << a.grade;
  return s;
}

// Vergleichsoperator "<"
bool mapra::operator<(const mapra::Student& s1, const mapra::Student& s2) {
  auto last_name_cmp = s1.last_name.compare(s2.last_name);
  if (last_name_cmp == 0) {
    return s1.first_name.compare(s2.last_name) < 0;
  } else {
    return last_name_cmp < 0;
  }
}

// Vergleichsoperator ">"
bool mapra::operator>(const mapra::Student& s1, const mapra::Student& s2) {
  return !(s1 < s2) && !(s1 == s2);
}

// Vergleichsoperatoren "==" bzw. "!="
bool mapra::operator==(const mapra::Student& s1, const mapra::Student& s2) {
  return s1.last_name.compare(s2.last_name) == 0 &&
         s1.first_name.compare(s2.first_name) == 0;
}

bool mapra::operator!=(const mapra::Student& s1, const mapra::Student& s2) {
  return !(s1 == s2);
}
