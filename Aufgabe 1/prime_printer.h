// TODO: In eigene Klasse, (PrintRow, PrintPage privat?)

std::vector<int> GeneratePrimes(int prime_count);

void PrintRow(const int kPrimeCount, const int kRowsPerPage,
              const int kColumnsPerRow, const int kPageOffset,
              const std::vector<int>& kPrimes);

void PrintPage(const int kPageNumber, const int kPrimeCount,
               const int kRowsPerPage, const int kColumnsPerRow,
               const int kPageOffset, const std::vector<int>& kPrimes);

void Print(const int kPrimeCount);