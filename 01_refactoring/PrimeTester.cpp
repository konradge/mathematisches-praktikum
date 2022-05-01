#include "PrimeTester.h"

#include <algorithm>
#include <iostream>
#include <vector>

PrimeTester::PrimeTester(const int kPrimeCount) {
  const int kOrdmax = 30;

  std::vector<int> primes_vector(kPrimeCount + 1);

  primes_vector[1] = 2;

  std::vector<int> prime_multiples(kOrdmax + 1);
  int square = 9;
  int num_prime_sieves = 2;
  int j = 1;

  for (int k = 1; k < kPrimeCount; k++) {
    bool j_prime;
    do {
      j += 2;
      if (j == square) {
        num_prime_sieves++;
        square = primes_vector[num_prime_sieves] * primes_vector[num_prime_sieves];
        prime_multiples[num_prime_sieves - 1] = j;
      }
      int n = 2;
      j_prime = true;
      while (n < num_prime_sieves && j_prime) {
        while (prime_multiples[n] < j) {
          prime_multiples[n] += 2 * primes_vector[n];
        }
        if (prime_multiples[n] == j) {
          j_prime = false;
        }
        n++;
      }
    } while (!j_prime);

    primes_vector[k + 1] = j;
  }

  // Remove the first element from the vector, as the above function starts the
  // primes with zero
  primes_vector.erase(primes_vector.begin());

  // Save the highest calculated prime number, as all numbers above may or may
  // not be primes
  max_prime = *primes_vector.end();

  // For performance regarding the is_prime function, the primes are stored
  // in a map --> Lookup will need constant time
  for (int pr : primes_vector) {
    primes[pr] = true;
  }
}

bool PrimeTester::is_prime(int number) { return primes[number]; }