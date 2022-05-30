#include "sparse_matrix.h"

#include "vector.h"

#define CHECK_INDEX \
  if (i >= rows || j >= cols) matError("Index not allowed")

void copy_map(hashmap_t* target, const hashmap_t& source) {
  for (auto entry : source) {
    (*target)[entry.first] = entry.second;
  }
}

Sparse_Matrix::Sparse_Matrix(size_t r, size_t c) {
  rows = r;
  cols = c;
}
Sparse_Matrix::Sparse_Matrix(const Sparse_Matrix& m) {
  rows = m.rows;
  cols = m.cols;
  // Copy the hash map
  copy_map(&this->mat, m.mat);
}

void Sparse_Matrix::put(size_t i, size_t j, double x) {
  CHECK_INDEX;
  if (x != 0) {
    mat[std::make_pair(i, j)] = x;
  } else {
    mat.erase(std::make_pair(i, j));
  }
}
double Sparse_Matrix::operator()(size_t i, size_t j) const {
  CHECK_INDEX;
  // Check if the entry exists
  if (mat.find(std::make_pair(i, j)) == mat.end()) return 0;
  return mat.at(std::make_pair(i, j));
}
double Sparse_Matrix::get(size_t i, size_t j) const { return (*this)(i, j); }

Sparse_Matrix& Sparse_Matrix::operator=(const Sparse_Matrix& m) {
  rows = m.rows;
  cols = m.cols;
  mat.clear();
  copy_map(&this->mat, m.mat);
  return *this;
}
Sparse_Matrix& Sparse_Matrix::operator+=(const Sparse_Matrix& m) {
  if (cols != m.cols || rows != m.rows) matError("Illegal dimensions!");
  for (auto& [key, value] : m.mat) {
    auto& [i, j] = key;
    this->put(i, j, (*this)(i, j) + value);
  }
  return *this;
}
Sparse_Matrix& Sparse_Matrix::operator-=(const Sparse_Matrix& m) {
  if (cols != m.cols || rows != m.rows) matError("Illegal dimensions!");
  for (auto& [key, value] : m.mat) {
    auto& [i, j] = key;
    this->put(i, j, (*this)(i, j) - value);
  }
  return *this;
}
Sparse_Matrix& Sparse_Matrix::operator*=(const Sparse_Matrix& m) {
  if (cols != m.rows) matError("Illegal dimensions!");
  // c_ij = \sum_{k=0}^{n-1}a_{i,k} * b_{k,j}
  for (size_t i = 0; i < rows; i++) {
    for (size_t j = 0; j < cols; j++) {
      double c_ij = 0;
      for (size_t k = 0; k < cols; k++) {
        c_ij += (*this)(i, k) * m(k, j);
      }
      this->put(i, j, c_ij);
    }
  }
  return *this;
}
Sparse_Matrix& Sparse_Matrix::operator*=(double c) {
  for (auto& [key, value] : mat) {
    auto& [i, j] = key;
    put(i, j, (*this)(i, j) * c);
  }
  return *this;
}

Sparse_Matrix& Sparse_Matrix::operator/=(double c) {
  (*this) *= 1 / c;
  return *this;
}

Sparse_Matrix& Sparse_Matrix::redim(size_t r, size_t c) {
  rows = r;
  cols = c;
  mat.clear();

  return *this;
}

Sparse_Matrix operator+(const Sparse_Matrix& m, const Sparse_Matrix& n) {
  Sparse_Matrix res(m);
  res += n;
  return res;
}
Sparse_Matrix operator-(const Sparse_Matrix& m, const Sparse_Matrix& n) {
  Sparse_Matrix res(m);
  res -= n;
  return res;
}
Sparse_Matrix operator-(const Sparse_Matrix& m) {
  Sparse_Matrix res(m.rows, m.cols);
  res -= m;
  return res;
}

Sparse_Matrix operator*(double c, const Sparse_Matrix& m) {
  Sparse_Matrix res(m);
  res *= c;
  return res;
}
Sparse_Matrix operator*(const Sparse_Matrix& m, double c) { return c * m; }
Sparse_Matrix operator/(const Sparse_Matrix& m, double d) {
  return m * (1 / d);
}

bool operator==(const Sparse_Matrix& m, const Sparse_Matrix& n) {
  if (m.rows != n.rows || m.cols != n.cols || m.mat.size() != n.mat.size()) {
    return false;
  } else {
    for (auto& [key, val] : m.mat) {
      if (n(key.first, key.second) != val) return false;
    }
    return true;
  }
}
bool operator!=(const Sparse_Matrix& m, const Sparse_Matrix& n) {
  return !(m == n);
}

std::istream& operator>>(std::istream& is, Sparse_Matrix& m) { return is; }
std::ostream& operator<<(std::ostream& os, const Sparse_Matrix& m) {
  for (size_t i = 0; i < m.rows; i++) {
    for (size_t j = 0; j < m.cols; j++) {
      os << m(i, j);
    }
    os << std::endl;
  }
  return os;
}

Vector operator*(const Sparse_Matrix& m, const Vector& v) { return v; }
Vector operator*(const Vector& v, const Sparse_Matrix& m) { return v; }

void Sparse_Matrix::matError(const char str[]) {
  std::cerr << "\nMatrixfehler: " << str << '\n' << std::endl;
  std::abort();
}