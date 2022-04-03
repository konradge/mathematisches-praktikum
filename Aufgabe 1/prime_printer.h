#include <fstream>
#include <iomanip>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

void print() {
  const int kOrdmax = 30;
  const int kM = 300;
  const int kRr = 50;
  const int kCc = 4;

  std::vector<int> p(kM + 1);
  p[1] = 2;

  std::vector<int> mult(kOrdmax + 1);
  int square = 9;
  int ord = 2;
  int j = 1;

  for (int k = 1; k < kM; k++) {
    bool j_prime;
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

    p[k + 1] = j;
  }

  int page_number = 1;
  int page_offset = 1;

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
