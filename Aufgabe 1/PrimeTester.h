#include <map>

class PrimeTester {
  std::map<int, bool> primes;
  int square = 9;
  int ord = 2;
  int j = 1;
  int found_primes = 0;
  int max_prime;

 public:
  PrimeTester(int prime_count);
  bool is_prime(int number);
};