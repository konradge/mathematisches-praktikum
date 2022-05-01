#include "generate_primes.h"

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
std::vector<int> GeneratePrimes(const int kPrimeCount) {
  std::vector<int> primes(kPrimeCount);

  PrimeTester prime_tester(kPrimeCount);

  int found_primes = 0;
  int number = 2;

  while (found_primes < kPrimeCount) {
    if (prime_tester.is_prime(number)) {
      primes[found_primes] = number;
      found_primes++;
    }
    number++;
  }

  return primes;
}