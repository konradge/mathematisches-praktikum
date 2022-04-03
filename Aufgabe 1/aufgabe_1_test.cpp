#include "PrimeTester.h"
#include "fstream"
#include "mapra_test.h"
#include "prime_printer.h"
#include "sstream"

void TestPrintPrimes() {
  mapra::MapraTest test("PrimePrintTester");

  std::ofstream out("YourPrint.txt");
  std::streambuf *cout_buffer = std::cout.rdbuf();
  std::cout.rdbuf(out.rdbuf());  // cout auf Datei "YourPrint.txt" umleiten
  Print(300);
  out.close();
  std::cout.rdbuf(cout_buffer);

  std::ifstream gold_file("PerfectPrint.txt");
  std::ifstream lead_file("YourPrint.txt");

  std::string gold_line;
  std::string lead_line;
  int i = 1;
  // Zeile fuer Zeile vergleichen
  while (std::getline(gold_file, gold_line)) {
    std::stringstream ss;
    ss << "Line " << std::to_string(i) << "xxx";
    std::getline(lead_file, lead_line);
    std::cout << "EXP: ";
    std::cout << gold_line << std::endl;
    std::cout << "GOT: ";
    std::cout << lead_line << std::endl;
    test.AssertEq(ss.str(), gold_line, lead_line);
    i++;
  }

  test.AssertEq("Test:", "EXP", "GOT");
  std::getline(lead_file, lead_line);
  test.Assert("No more lines :", lead_file.eof());
  remove("YourPrint.txt");
  //  std::cout.rdbuf(cout_buffer);  // cout wieder auf Bildschirm leiten
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
    test.Assert("To big number", !prime_tester.is_prime(tbn));
  }
}

int main() {
  TestPrintPrimes();
  // TestGeneratePrimes();
  // TestIsPrime();
  return 0;
}
