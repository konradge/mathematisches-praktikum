#ifndef SORTIEREN_H_
#define SORTIEREN_H_

#include <stdio.h>
#include <stdlib.h>

#include <iostream>
#include <vector>

namespace Sort {

// function merge
template <typename T>
std::vector<T> Merge(std::vector<T> left, std::vector<T> right) {
  unsigned int n_left = left.size();
  unsigned int n_right = right.size();
  unsigned int i_left = 0;   // index of left
  unsigned int i_right = 0;  // index of right
  std::vector<T> data;

  for (unsigned int i_data = 0; i_data < n_left + n_right; i_data++) {
    if ((i_right >= n_right) ||
        ((i_left < n_left) && (left[i_left] <= right[i_right]))) {
      data.push_back(left[i_left]);
      i_left++;
    } else {
      data.push_back(right[i_right]);
      i_right++;
    }
  }

  return data;
}

// function mergeSort
template <typename T>
std::vector<T> Mergesort(std::vector<T> data) {
  unsigned int n = data.size();
  if (n <= 1) {
    return data;
  }
  std::vector<T> left(n / 2);
  std::vector<T> right(n - n / 2);
  // copy the left part of data in left
  copy(data.begin(), data.begin() + n / 2, left.begin());
  // copy the right part of data in right
  copy(data.begin() + n / 2, data.end(), right.begin());

  // sort the left and right part and merge
  return Merge(Mergesort(left), Mergesort(right));
}

// function bubblesort
template <typename T>
std::vector<T> Bubblesort(std::vector<T> data) {
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

template <typename T>
std::vector<T> Selectionsort(std::vector<T> array) {
  int n = array.size();
  int min = 0;
  // look the minimum in the non sorted Part
  for (auto i = 0; i < n; i++) {
    // and insert it at the next position after
    min = i;
    // the sorted part
    for (auto j = i + 1; j < n; j++) {
      if (array[min] > array[j]) {
        min = j;
      }
    }
    std::swap(array[min], array[i]);
  }

  return array;
}

}  // namespace Sort

#endif
