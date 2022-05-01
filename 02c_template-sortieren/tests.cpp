#include "Sort.h"
#include "main.h"
#include "mapra_test.h"
#include "student.h"
#include "unit.h"

int main() {
  mapra::MapraTest tests("Template sortieren");

  mapra::Student s1 = {"Max", "Mustermann", 12345, 5};
  mapra::Student s2 = {"Maxi", "Mustermann", 12345, 5};
  mapra::Student s3 = {"Max", "Mastermann", 12345, 5};
  mapra::Student s4 = {"Max", "Mastermann", 98765, 1};

  tests.Assert("Vorname: Max < Maxi ", s1 < s2);
  tests.Assert("Vorname: Max <= Maxi ", s1 <= s2);
  tests.Assert("Nachname: Mustermann > Mastermann ", s1 > s3);
  tests.Assert("Gleiche Namen: == ", s3 == s4);
  tests.Assert("Gleiche Namen: Auch <= ", s3 <= s4);
  tests.Assert("Ungleiche Namen ", s1 != s4);

  for (auto algorithm : {mapra::SortingAlgorithm::BUBBLE_SORT,
                         mapra::SortingAlgorithm::MERGE_SORT,
                         mapra::SortingAlgorithm::SELECTION_SORT}) {
    auto out = GetFromFileAndSort<double>("doubles.txt", algorithm);
    tests.Assert("Sortiere doubles ", !mapra::CheckSolution(out));
  }

  for (auto algorithm : {mapra::SortingAlgorithm::BUBBLE_SORT,
                         mapra::SortingAlgorithm::MERGE_SORT,
                         mapra::SortingAlgorithm::SELECTION_SORT}) {
    auto out = GetFromFileAndSort<std::string>("strings.txt", algorithm);

    tests.Assert("Sortiere Strings ", !mapra::CheckSolution(out));
  }

  for (auto algorithm : {mapra::SortingAlgorithm::BUBBLE_SORT,
                         mapra::SortingAlgorithm::MERGE_SORT,
                         mapra::SortingAlgorithm::SELECTION_SORT}) {
    auto out = GetFromFileAndSort<mapra::Student>("studenten.txt", algorithm);

    tests.Assert("Sortiere Studenten ", !mapra::CheckSolution(out));
  }
  return 0;
}