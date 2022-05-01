#include <fstream>
#include <vector>

namespace mapra {
template <typename T>
void Read(std::ifstream& ifs, std::vector<T>& array);

template <typename T>
void Print(std::ostream& os, const std::vector<T>& array);
}  // namespace mapra