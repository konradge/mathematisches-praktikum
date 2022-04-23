#include "Sort.h"

#include <math.h>
#include <stdio.h>
#include <stdlib.h>

#include <iostream>
#include <vector>

#include "mapra_test.h"

// function merge
std::vector<unsigned int> Sort::Merge(std::vector<unsigned int> left,
                                      std::vector<unsigned int> right) {
  unsigned int n_left = left.size();
  unsigned int n_right = right.size();
  unsigned int i_left = 0;   // index of left
  unsigned int i_right = 0;  // index of right
  std::vector<unsigned int> data(n_left + n_right);

  for (unsigned int i_data = 0; i_data < n_left + n_right; i_data++) {
    if (((i_left < n_left) && (left[i_left] <= right[i_right])) ||
        (i_right >= n_right)) {
      data[i_data] = left[i_left];
      i_left++;
    } else {
      data[i_data] = right[i_right];
      i_right++;
    }
  }
  return data;
}

// function mergeSort
std::vector<unsigned int> Sort::Mergesort(std::vector<unsigned int> data) {
  unsigned int n = data.size();
  if (n <= 1) {
    return data;
  }
  std::vector<unsigned int> left(n / 2);
  std::vector<unsigned int> right(n - n / 2);
  // copy the left part of data in left
  copy(data.begin(), data.begin() + n / 2, left.begin());
  // copy the right part of data in right
  copy(data.begin() + n / 2, data.end(), right.begin());
  // sort the left and right part and merge
  return Merge(Mergesort(left), Mergesort(right));
}

// function print_vector
void Sort::print_vector(std::vector<unsigned int> data) {
  for (auto entry : data) std::cout << entry << "  ";
  std::cout << std::endl;
}

// function bubblesort
std::vector<unsigned int> Sort::Bubblesort(std::vector<unsigned int> data) {
  int n = data.size();
  for (auto j = 1; j < n; j++) {
    for (auto i = 0; i < j; i++) {
      if (data[i] > data[j]) {
        std::swap(data[i], data[j]);
      }
    }
  }
  return data;
}

// selectionsort

std::vector<unsigned int> Sort::Selectionsort(std::vector<unsigned int> array) {
  std::vector<unsigned int> data(array.size());
  std::copy(array.begin(), array.end(), data.begin());
  int n = data.size();
  int min = 0;
  // look the minimum in the non sorted Part
  for (auto i = 0; i < n; i++) {
    // and insert it at the next position after
    min = i;
    // the sorted part
    for (auto j = i + 1; j < n; j++) {
      if (data[min] > data[j]) {
        min = j;
      }
    }
    std::swap(data[min], data[i]);
  }

  return data;
}

// function insertionsort

std::vector<unsigned int> Sort::Insertionsort(std::vector<unsigned int> data) {
  int n = data.size();
  for (auto i = 0; i < n; i++) {
    // insert  the next element in the right position in
    for (auto j = i; j > 0; j--) {
      // the sorted part
      if (data[j - 1] > data[j]) {
        std::swap(data[j - 1], data[j]);
      }
    }
  }
  return data;
}
std::vector<unsigned int> Sort::Heapify(std::vector<unsigned int> data,
                                        unsigned int size, unsigned int index) {
  unsigned int left = 2 * index + 1;
  unsigned int right = 2 * index + 2;
  unsigned int maxIndex = index;

  if (left < size && data[maxIndex] < data[left]) {
    maxIndex = left;  // looking for the biggest child
  }
  if (right < size && data[maxIndex] < data[right]) {
    maxIndex = right;
  }

  if (maxIndex != index) {
    std::swap(data[maxIndex], data[index]);  // swap with the parent
    data = Heapify(data, size, maxIndex);
  }
  return data;
}
// function heapsort
std::vector<unsigned int> Sort::Heapsort(std::vector<unsigned int> data) {
  unsigned int n = data.size();

  if (n <= 1) {
    return data;
  }

  // transform the vector to an heap
  for (int i = pow(2, floor(log2(n))) - 2; i >= 0; i--) {
    data = Heapify(data, n, i);
  }

  // sorted by extraying the max element and put it at the end
  for (int i = n - 1; i >= 0; i--) {
    std::swap(data[0], data[i]);
    data = Heapify(data, i, 0);
  }
  return data;
}

std::vector<unsigned int> Sort::Quicksort(std::vector<unsigned int> data) {
  return Quicksort(data, false);
}

std::vector<unsigned int> Sort::QuicksortMedian(
    std::vector<unsigned int> data) {
  return Quicksort(data, true);
}

std::vector<unsigned int> Sort::Quicksort(std::vector<unsigned int> data,
                                          bool medianMode) {
  if (data.size() <= 1) return data;

  std::vector<unsigned int> left;
  std::vector<unsigned int> right;
  unsigned int pivotIndex;

  if (medianMode) {
    pivotIndex = MedianOfThree(data);
    // swap pivot to end to be able to use standard quicksort
    std::swap(data[pivotIndex], data[data.size() - 1]);
  }

  pivotIndex = data.size() - 1;

  for (unsigned int i = 0; i < data.size() - 1; i++) {
    if (data[i] < data[pivotIndex])
      left.push_back(data[i]);
    else
      right.push_back(data[i]);
  }
  std::vector<unsigned int> newLeft = Quicksort(left, medianMode);
  std::vector<unsigned int> newRight = Quicksort(right, medianMode);
  data[newLeft.size()] = data[pivotIndex];
  copy(newLeft.begin(), newLeft.end(), data.begin());
  copy(newRight.begin(), newRight.end(), data.begin() + newLeft.size() + 1);
  return data;
}

unsigned int Sort::MedianOfThree(std::vector<unsigned int> data) { return 0; }
