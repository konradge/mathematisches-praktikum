#include "PrimePrinter.h"

#include <iomanip>
#include <iostream>
#include <vector>

#include "generate_primes.h"

void PrimePrinter::PrintRow(const int kPrimeCount, const int kPageOffset,
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

void PrimePrinter::PrintPage(const int kPageNumber, const int kPrimeCount,
                             const int kPageOffset,
                             const std::vector<int>& kPrimes) {
  std::cout << "The First ";
  std::cout << kPrimeCount;
  std::cout << " Prime Numbers --- Page ";
  std::cout << kPageNumber;
  std::cout << std::endl;
  PrintRow(kPrimeCount, kPageOffset, kPrimes);
  std::cout << "\f" << std::endl;
}

// Print out prime_count primes
void PrimePrinter::Print(int prime_count) {
  const auto kPrimes = GeneratePrimes(prime_count);
  int page_number = 1;
  int page_offset = 1;

  while (page_offset <= prime_count) {
    PrintPage(page_number, prime_count, page_offset, kPrimes);
    page_number++;
    page_offset += kRowsPerPage * kColumnsPerRow;
  }
}