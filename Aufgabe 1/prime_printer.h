#include <fstream>
#include <iomanip>
#include <iostream>
#include <sstream>
#include <string>

void print() {
  int m = 300;
  int rr = 50;
  int cc = 4;
  int ordmax = 30;
  int p[m + 1];
  int page_number;
  int page_offset;
  int row_offset;
  int c;
  int j;
  int k;
  bool j_prime;
  int ord;
  int square;
  int n = 0;
  int mult[ordmax + 1];

  j = 1;
  k = 1;
  p[1] = 2;
  ord = 2;
  square = 9;

  while (k < m) {
    do {
      j += 2;
      if (j == square) {
        ord++;
        square = p[ord] * p[ord];
        mult[ord - 1] = j;
      }
      n = 2;
      j_prime = true;
      while (n < ord && j_prime) {
        while (mult[n] < j) {
          mult[n] += p[n] + p[n];
        }
        if (mult[n] == j) {
          j_prime = false;
        }
        n++;
      }
    } while (!j_prime);
    k++;
    p[k] = j;
  }
  page_number = 1;
  page_offset = 1;
  while (page_offset <= m) {
    std::cout << "The First ";
    std::cout << m;
    std::cout << " Prime Numbers --- Page ";
    std::cout << page_number;
    std::cout << std::endl;
    for (row_offset = page_offset; row_offset <= page_offset + rr - 1;
         row_offset++) {
      for (c = 0; c <= cc - 1; c++) {
        if (row_offset + c * rr <= m) {
          std::cout << std::setw(10) << p[row_offset + c * rr];
        }
      }
      std::cout << std::endl;
    }
    std::cout << "\f" << std::endl;
    page_number++;
    page_offset += rr * cc;
  }
}
