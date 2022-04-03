#include "mapra_test.h"
#include "prime_printer.h"

void TestPrintPrimes() {
  mapra::MapraTest test("PrimePrintTester");

  std::ofstream out("YourPrint.txt");
  std::streambuf *cout_buffer = std::cout.rdbuf();
  std::cout.rdbuf(out.rdbuf());  // cout auf Datei "YourPrint.txt" umleiten
  print(300);
  out.close();

  std::ifstream gold_file("PerfectPrint.txt");
  std::ifstream lead_file("YourPrint.txt");

  std::string gold_line;
  std::string lead_line;
  int i = 1;
  // Zeile fuer Zeile vergleichen
  while (std::getline(gold_file, gold_line)) {
    std::stringstream ss;
    ss << "Line " << std::to_string(i) << "\t:";
    std::getline(lead_file, lead_line);
    test.AssertEq(ss.str(), gold_line, lead_line);
    i++;
  }
  std::getline(lead_file, lead_line);
  test.Assert("No more lines :", lead_file.eof());
  remove("YourPrint.txt");
  std::cout.rdbuf(cout_buffer);  // cout wieder auf Bildschirm leiten
}

int main() {
  TestPrintPrimes();
  return 0;
}
