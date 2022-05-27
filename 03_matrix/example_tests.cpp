// Copyright (c) 2022, The MaPra Authors.

#include <fstream>
#include <iostream>
#include <sstream>
#include <string>

#include "mapra_test.h"
#include "matrix.h"

double fRand(double fMin, double fMax)
{
    double f = (double)rand() / RAND_MAX;
    return fMin + f * (fMax - fMin);
}

void matrixTests();
void vectorTests();

int main() {
  matrixTests();
  vectorTests();
  return 0;
}

void matrixTests() {
  mapra::MapraTest test("Matrizen");

  mapra::Matrix m(2,2);
  bool zeroTester = false;
  for (size_t i = 0; i < m.GetRows(); i++) {
    for (size_t j = 0; j < m.GetCols(); j++) {
      zeroTester = zeroTester || (m(i,j) != 0);
    }
  }
  test.Assert("Neue Matrix ist implizit die Nullmatrix", !zeroTester);

  for (size_t i = 0; i < m.GetRows(); i++) {
    for (size_t j = 0; j < m.GetCols(); j++) {
      m(i,j) = fRand(-69,69);
    }
  }
  m.Redim(3,4);
  zeroTester = false;
  for (size_t i = 0; i < m.GetRows(); i++) {
    for (size_t j = 0; j < m.GetCols(); j++) {
      zeroTester = zeroTester || (m(i,j) != 0);
    }
  }
  test.Assert("Redimensionierte Matrix ist implizit die Nullmatrix", !zeroTester);
  

  mapra::Matrix n(5,4);
  for (size_t i = 0; i < m.GetRows(); i++) {
    for (size_t j = 0; j < m.GetCols(); j++) {
      m(i,j) = fRand(-69,69);
    }
  }
  n = m;
  test.Assert("Zuweisung von Matrix zu Matrix", n == m);

  mapra::Matrix l(m);
  test.Assert("copy-Konstruktor kopiert Matrix", l == m);
}

void vectorTests() {
  mapra::MapraTest test("Vektoren");

  mapra::Vector m(2);
  bool zeroTester = false;
  for (size_t j = 0; j < m.GetLength(); j++) {
    zeroTester = zeroTester || (m(j) != 0);
  }
  test.Assert("Neuer Vektor ist implizit der Nullvektor", !zeroTester);

  for (size_t j = 0; j < m.GetLength(); j++) {
    m(j) = fRand(-69,69);
  }
  m.Redim(4);
  zeroTester = false;
  for (size_t j = 0; j < m.GetLength(); j++) {
    zeroTester = zeroTester || (m(j) != 0);
  }
  test.Assert("Redimensionierter Vektor ist implizit die Nullvektor", !zeroTester);
  

  mapra::Vector n(5);
  for (size_t j = 0; j < m.GetLength(); j++) {
    m(j) = fRand(-69,69);
  }
  n = m;
  test.Assert("Zuweisung von Vektor zu Vektor", n == m);

  mapra::Vector l(m);
  test.Assert("copy-Konstruktor kopiert Vektor", l == m);
}