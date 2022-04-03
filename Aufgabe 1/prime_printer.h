#include <fstream>
#include <iomanip>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

// Generate prime_count prime numbers as a std::vector
std::vector<int> GeneratePrimes(int prime_count) {
  const int kOrdmax = 30;

  std::vector<int> p(prime_count + 1);
  p[1] = 2;

  std::vector<int> mult(kOrdmax + 1);
  int square = 9;
  int ord = 2;
  int j = 1;

  for (int k = 1; k < prime_count; k++) {
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

  // Remove the first element from the vector, as the above function starts the
  // primes with zero
  p.erase(p.begin());

  return p;
}

void PrintPage(const int kPageNumber, const int kPrimeCount,
               const int kRowsPerPage, const int kColumnsPerRow,
               const int kPageOffset, const std::vector<int>& kPrimes) {
  std::cout << "The First ";
  std::cout << kPrimeCount;
  std::cout << " Prime Numbers --- Page ";
  std::cout << kPageNumber;
  std::cout << std::endl;
  for (int row_offset = kPageOffset;
       row_offset <= kPageOffset + kRowsPerPage - 1; row_offset++) {
    for (int c = 0; c <= kColumnsPerRow - 1; c++) {
      if (row_offset + c * kRowsPerPage <= kPrimeCount) {
        std::cout << std::setw(10)
                  << kPrimes[row_offset + c * kRowsPerPage - 1];
      }
    }
    std::cout << std::endl;
  }
  std::cout << "\f" << std::endl;
}

// Print out prime_count primes
void Print(int prime_count) {
  const int kRowsPerPage = 50;
  const int kColumnsPerRow = 4;

  const auto kPrimes = GeneratePrimes(prime_count);
  int page_number = 1;
  int page_offset = 1;

  while (page_offset <= prime_count) {
    PrintPage(page_number, prime_count, kRowsPerPage, kColumnsPerRow,
              page_offset, kPrimes);
    page_number++;
    page_offset += kRowsPerPage * kColumnsPerRow;
  }
}
