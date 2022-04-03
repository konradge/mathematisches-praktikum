#include <fstream>
#include <iomanip>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

#include "PrimeTester.h"

const int kRowsPerPage = 50;
const int kColumnsPerRow = 4;

// Generate prime_count prime numbers as a std::vector
std::vector<int> GeneratePrimes(int prime_count) {
  std::vector<int> primes(prime_count);

  PrimeTester prime_tester(prime_count);

  int found_primes = 0;
  int number = 2;

  while (found_primes < prime_count) {
    if (prime_tester.is_prime(number)) {
      primes[found_primes] = number;
      found_primes++;
    }
    number++;
  }

  return primes;
}

void PrintRow(const int kPrimeCount, const int kRowsPerPage,
              const int kColumnsPerRow, const int kPageOffset,
              const std::vector<int>& kPrimes) {
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
}

void PrintPage(const int kPageNumber, const int kPrimeCount,
               const int kRowsPerPage, const int kColumnsPerRow,
               const int kPageOffset, const std::vector<int>& kPrimes) {
  std::cout << "The First ";
  std::cout << kPrimeCount;
  std::cout << " Prime Numbers --- Page ";
  std::cout << kPageNumber;
  std::cout << std::endl;
  PrintRow(kPrimeCount, kRowsPerPage, kColumnsPerRow, kPageOffset, kPrimes);
  std::cout << "\f" << std::endl;
}

// Print out prime_count primes
void Print(int prime_count) {
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
