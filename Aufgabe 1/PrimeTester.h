#include <map>

class PrimeTester {
  std::map<int, bool> primes;
  int found_primes = 0;

 public:
  PrimeTester(int prime_count);
  bool is_prime(int number);
};