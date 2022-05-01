#ifndef SORTIEREN_H_
#define SORTIEREN_H_

#include <stdio.h>
#include <stdlib.h>

#include <iostream>
#include <vector>

namespace Sort {

void print_vector(std::vector<unsigned int> data);

template <typename T>
std::vector<T> Merge(std::vector<T> left, std::vector<T> right);
template <typename T>
std::vector<T> Mergesort(std::vector<T> data);
template <typename T>
std::vector<T> Bubblesort(std::vector<T> data);
template <typename T>
std::vector<T> Selectionsort(std::vector<T> array);
}  // namespace Sort

#endif
