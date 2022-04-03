#include "PrimeTester.h"
#include "fstream"
#include "mapra_test.h"
#include "prime_printer.h"
#include "sstream"

// Concatenate strings in the given vector to one string
std::string StringConcatHelper(const std::vector<std::string> kStrings) {
  std::stringstream ss;
  for (const auto kStr : kStrings) {
    ss << kStr;
  }
  return ss.str();
}

void TestPrintPrimes() {
  mapra::MapraTest test("PrimePrintTester");

  std::ofstream out("YourPrint.txt");
  std::streambuf *cout_buffer = std::cout.rdbuf();
  std::cout.rdbuf(out.rdbuf());  // cout auf Datei "YourPrint.txt" umleiten
  Print(300);
  out.close();

  std::ifstream expected_file("PerfectPrint.txt");
  std::ifstream got_file("YourPrint.txt");

  std::string expected_line;
  std::string got_line;
  int i = 1;
  // Zeile fuer Zeile vergleichen
  while (std::getline(expected_file, expected_line)) {
    std::getline(got_file, got_line);
    std::string test_name =
        StringConcatHelper({"Line ", std::to_string(i), "\t:"});
    test.AssertEq(test_name, expected_line, got_line);
    i++;
  }
  std::getline(got_file, got_line);
  test.Assert("No more lines :", got_file.eof());
  remove("YourPrint.txt");
  std::cout.rdbuf(cout_buffer);  // cout wieder auf Bildschirm leiten
}

void TestGeneratePrimes() {
  mapra::MapraTest test("PrimeGenerateTester");

  const std::vector<int> kPrimes = {2, 3, 5, 7, 11, 13, 17, 19, 23, 29};
  const std::vector<int> kGeneratedPrimes = GeneratePrimes(10);

  test.AssertEq("Generated primes", kPrimes, kGeneratedPrimes);
}

void TestIsPrime() {
  mapra::MapraTest test("IsPrimeTester");
  PrimeTester prime_tester(20);
  const std::vector<int> kPrimes = {2, 3, 5, 7, 11, 13, 17, 19, 23, 29};
  const std::vector<int> kNonPrimes = {1,  4,  6,  8,  9,  10, 12, 14,
                                       15, 16, 18, 20, 21, 22, 24, 25};
  std::vector<int> to_big_numbers = {1000, 2000};
  for (const auto p : kPrimes) {
    test.AssertEq("Positive test", prime_tester.is_prime(p), true);
  }

  for (const auto np : kNonPrimes) {
    test.AssertEq("Negative test", prime_tester.is_prime(np), false);
  }

  for (const auto tbn : to_big_numbers) {
    bool catched;
    try {
      prime_tester.is_prime(tbn);
      catched = false;
    } catch (int err) {
      catched = true;
    }

    test.Assert("To big number", catched);
  }
}

int main() {
  TestPrintPrimes();
  TestGeneratePrimes();
  TestIsPrime();
  return 0;
}
