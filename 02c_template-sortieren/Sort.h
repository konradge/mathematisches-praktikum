#ifndef SORTIEREN_H_
#define SORTIEREN_H_

#include <stdio.h>
#include <stdlib.h>

#include <iostream>
#include <vector>

namespace Sort {

void print_vector(std::vector<unsigned int> data);

std::vector<unsigned int> Merge(std::vector<unsigned int> left,
                                std::vector<unsigned int> right);
std::vector<unsigned int> Mergesort(std::vector<unsigned int> data);
std::vector<unsigned int> Bubblesort(std::vector<unsigned int> data);
std::vector<unsigned int> Selectionsort(std::vector<unsigned int> data);
std::vector<unsigned int> Insertionsort(std::vector<unsigned int> data);
std::vector<unsigned int> Heapify(std::vector<unsigned int> data,
                                  unsigned int n, unsigned int i);
std::vector<unsigned int> Heapsort(std::vector<unsigned int> data);
std::vector<unsigned int> Quicksort(std::vector<unsigned int> data);
std::vector<unsigned int> Quicksort(std::vector<unsigned int> data,
                                    bool medianMode);
std::vector<unsigned int> QuicksortMedian(std::vector<unsigned int> data);
unsigned int MedianOfThree(std::vector<unsigned int> data);
}  // namespace Sort

#endif
