#include "PrimeTester.h"

#include <algorithm>
#include <iostream>
#include <vector>

PrimeTester::PrimeTester(int prime_count) {
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

  // Save the highest calculated prime number, as all numbers above may or may
  // not be primes
  max_prime = *p.end();

  // For performance regarding the is_prime function, the primes are stored in a
  // map --> Lookup will need constant time
  for (auto pr = p.begin(); pr != p.end(); ++pr) {
    primes[*pr] = true;
  }
}

bool PrimeTester::is_prime(int number) {
  if (number > max_prime) {
    // It has not been tested, if the number is a prime
    throw 1;
  }
  return primes[number];
}