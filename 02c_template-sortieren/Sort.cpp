// #include "Sort.h"

// #include <math.h>
// #include <stdio.h>
// #include <stdlib.h>

// #include <iostream>
// #include <vector>

// #include "mapra_test.h"

// // function merge
// template <typename T>
// std::vector<T> Sort::Merge(std::vector<T> left, std::vector<T> right) {
//   unsigned int n_left = left.size();
//   unsigned int n_right = right.size();
//   unsigned int i_left = 0;   // index of left
//   unsigned int i_right = 0;  // index of right
//   std::vector<T> data(n_left + n_right);

//   for (unsigned int i_data = 0; i_data < n_left + n_right; i_data++) {
//     if (((i_left < n_left) && (left[i_left] <= right[i_right])) ||
//         (i_right >= n_right)) {
//       data[i_data] = left[i_left];
//       i_left++;
//     } else {
//       data[i_data] = right[i_right];
//       i_right++;
//     }
//   }
//   return data;
// }

// // function mergeSort
// template <typename T>
// std::vector<T> Sort::Mergesort(std::vector<T> data) {
//   unsigned int n = data.size();
//   if (n <= 1) {
//     return data;
//   }
//   std::vector<T> left(n / 2);
//   std::vector<T> right(n - n / 2);
//   // copy the left part of data in left
//   copy(data.begin(), data.begin() + n / 2, left.begin());
//   // copy the right part of data in right
//   copy(data.begin() + n / 2, data.end(), right.begin());
//   // sort the left and right part and merge
//   return Merge(Mergesort(left), Mergesort(right));
// }

// // function print_vector
// void Sort::print_vector(std::vector<unsigned int> data) {
//   for (auto entry : data) std::cout << entry << "  ";
//   std::cout << std::endl;
// }

// // function bubblesort
// template <typename T>
// std::vector<T> Sort::Bubblesort(std::vector<T> data) {
//   int n = data.size();
//   for (auto j = 1; j < n; j++) {
//     for (auto i = 0; i < j; i++) {
//       if (data[i] > data[j]) {
//         std::swap(data[i], data[j]);
//       }
//     }
//   }
//   return data;
// }

// // selectionsort

// template <typename T>
// std::vector<T> Sort::Selectionsort(std::vector<T> array) {
//   std::vector<unsigned int> data(array.size());
//   std::copy(array.begin(), array.end(), data.begin());
//   int n = data.size();
//   int min = 0;
//   // look the minimum in the non sorted Part
//   for (auto i = 0; i < n; i++) {
//     // and insert it at the next position after
//     min = i;
//     // the sorted part
//     for (auto j = i + 1; j < n; j++) {
//       if (data[min] > data[j]) {
//         min = j;
//       }
//     }
//     std::swap(data[min], data[i]);
//   }

//   return data;
// }
