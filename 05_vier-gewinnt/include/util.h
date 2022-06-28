int randomInt(int min, int max) {
  std::default_random_engine generator(std::random_device{}());
  std::uniform_int_distribution<int> distribution(min, max);
  return distribution(generator);
}

template <typename T>
bool vector_contains(std::vector<T> v, T elem) {
  return (std::find(v.begin(), v.end(), elem) != v.end());
}

template <typename T>
size_t vector_count(std::vector<T> v, T elem) {
  int count = 0;
  for (T e : v) {
    if (e == elem) {
      count++;
    }
  }
  return count;
}