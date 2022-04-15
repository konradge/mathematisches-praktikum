#include <stdio.h>
#include <stdlib.h>
#include <vector>
#include <iostream>
#include "Sort.h"

using namespace std;


// function merge
vector < unsigned int> Sort::merge(std::vector < unsigned int> left,
	                              std::vector < unsigned int> right) {
	unsigned int n_left = left.size();
	unsigned int n_right = right.size();
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
vector < unsigned int> Sort::mergesort(vector <unsigned int> data) {
	unsigned int n = data.size();
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
	return merge(mergesort(left), mergesort(right));         //sort the left and right part and merge
}


//function print_vector 
void Sort::print_vector(std::vector <unsigned int> data) {
	for (long unsigned int i = 0; i < data.size(); i++)
		cout << data[i] << "  ";
	cout << endl;

}

//function bubblesort
std::vector < unsigned int> Sort::bubblesort(std::vector <unsigned int> data) {
	unsigned int n = data.size();
	for (unsigned int j = 1; j < n; j++) {
		for (unsigned int i = 0; i < j; i++) {
			if (data[i] > data[j]) {
				std::swap(data[i], data[j]);
			}
	  }
	}
	return data;
}


//selectionsort

std::vector < unsigned int> Sort::selectionsort(std::vector <unsigned int> data) {
	unsigned int n = data.size();
	unsigned int min = 0;
	for (unsigned int i = 0; i < n; i++) {
		min = i;
		for (unsigned int j = i+1; j < n ; j++) {
			if (data[min] > data[j]) {
				min = j;
			}
		}
		swap(data[min], data[i]);
	}

	return data;
}

//function insertionsort

std::vector <unsigned int> Sort::insertionsort(std::vector <unsigned int> data) {
	unsigned int n = data.size();
	for (unsigned int i = 0; i < n; i++) {
		for (int j = i; j >= 0; j--) {
			if (data[j] < data[i]) {
				std::swap(data[j], data[i]);
			}
	   }
	}
	return data;
}