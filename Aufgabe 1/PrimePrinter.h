#include <vector>

class PrimePrinter {
 private:
  const int kRowsPerPage;
  const int kColumnsPerRow;
  void PrintRow(const int kPrimeCount, const int kPageOffset,
                const std::vector<int>& kPrimes);

  void PrintPage(const int kPageNumber, const int kPrimeCount,
                 const int kPageOffset, const std::vector<int>& kPrimes);

 public:
  PrimePrinter(const int kRowsPerPage, const int kColumnsPerRow)
      : kRowsPerPage(kRowsPerPage), kColumnsPerRow(kColumnsPerRow) {}
  void Print(const int kPrimeCount);
};