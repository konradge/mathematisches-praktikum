#include <stdio.h>
#include <stdlib.h>
#include <vector>
#include <iostream>
#include "Sort.h"

using namespace std;


// function merge
vector < unsigned int> Sort::merge(vector < unsigned int> left,
							 unsigned int n_left,
	                         vector < unsigned int> right,
                             unsigned int n_right) {
	unsigned int i = 0;  // index of data
	unsigned int l = 0;  // index of left
	unsigned int r = 0;  // index of right
	std::vector <unsigned int> data(n_left + n_right);

	while (i < n_left + n_right) {                    
		if (((left[l] <= right[r]) && (l < n_left)) || (r >= n_right)) {
			data[i] = left[l];
			i++;
			l++;
		}
		else {
			data[i] = right[r];
			i++; 
			r++;
		}
	}
	return data;

}


// function mergeSort
vector < unsigned int> Sort::mergeSort(vector <unsigned int> data, unsigned int n) {
	if (n == 0) {
		cout << "the vector is empty" << endl;                //case the vector is empty
		return data;
	}
	if (n == 1) {       
		return data;                                         // case the vector has only one element
	}	
	std::vector <unsigned int> left(n/2);
	std::vector <unsigned int> right(n - n/2);
	copy(data.begin(), data.begin() + n / 2, left.begin());  //copy the left part of data in left
	copy(data.begin() + n / 2 , data.end(), right.begin());  //copy the right part of data in right
	return merge(mergeSort(left, n / 2), n / 2, mergeSort(right, n - n / 2), n - n / 2);  //sort the left and right part and merge
}



void Sort::print_vector(std::vector <unsigned int> data) {
	for (long unsigned int i = 0; i < data.size(); i++)
		cout << data[i] << "  ";
	cout << endl;

}