#include <fstream>
#include <iomanip>
#include <iostream>
#include <sstream>
#include <string>

void print() {
  const int kOrdmax = 30;
  const int kM = 300;
  const int kRr = 50;
  const int kCc = 4;
  int p[kM + 1];
  int page_number = 1;
  int page_offset = 1;
  int j = 1;
  int k = 1;
  bool j_prime;
  int ord = 2;
  int square = 9;
  int mult[kOrdmax + 1];

  p[1] = 2;

  while (k < kM) {
    do {
      j += 2;
      if (j == square) {
        ord++;
        square = p[ord] * p[ord];
        mult[ord - 1] = j;
      }
      int n = 2;
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
  while (page_offset <= kM) {
    std::cout << "The First ";
    std::cout << kM;
    std::cout << " Prime Numbers --- Page ";
    std::cout << page_number;
    std::cout << std::endl;
    for (int row_offset = page_offset; row_offset <= page_offset + kRr - 1;
         row_offset++) {
      for (int c = 0; c <= kCc - 1; c++) {
        if (row_offset + c * kRr <= kM) {
          std::cout << std::setw(10) << p[row_offset + c * kRr];
        }
      }
      std::cout << std::endl;
    }
    std::cout << "\f" << std::endl;
    page_number++;
    page_offset += kRr * kCc;
  }
}
