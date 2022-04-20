#include <stdio.h>
#include <stdlib.h>
#include <vector>
#include <iostream>
#include "Sort.h"
#include "mapra_test.h"

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
	for (unsigned int i = 0; i < n; i++) {                 //look the minimum in the  non sorted Part
		min = i;                                          //and insert it  at  the next position after 
		for (unsigned int j = i+1; j < n ; j++) {        // the sorted part
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
		for (int j = i; j >= 0; j--) {              // insert  the next element in the right position in
			if (data[j] < data[i]) {               // the sorted part 
				std::swap(data[j], data[i]);
			}
	   }
	}
	return data;
}
std::vector <unsigned int> Sort::heapify(std::vector <unsigned int> data, unsigned int n, unsigned int  i) {
	unsigned int left = 2 * i + 1;
	unsigned int right = 2 * i + 2;
	unsigned int max = i;
	
	if (data[max] < data[left] && left < n) {
		max = left;      //looking for the biggest child
	}
	if (data[max] < data[right] && right < n) {
		max = right;
	}

	if (max != i) {
		std::swap(data[max], data[i]);  // swap with the parent 
		data = heapify(data,n, max);
	}
	return data;
}
//function heapsort
std::vector <unsigned int> Sort::heapsort(std::vector <unsigned int> data) {
	unsigned int n = data.size();

	// transform the vector to an heap
	for (int i = n / 2; i >= 0; i--) {
		data = heapify(data,n , i);
	}

	//sorted by extraying the max element and put it at the end
	for (int i =  n - 1; i >= 0; i--) {
		swap(data[0], data[i]);
		n--;
		data = heapify(data, n, 0);
		
	}
	return data;
}

std::vector <unsigned int> Sort::quicksort(std::vector <unsigned int> data) {
	if (data.size() <= 1) return data;
	
	std::vector <unsigned int> left;
	std::vector <unsigned int> right;
	unsigned int pivotIndex = data.size() - 1;
	unsigned int pivot = data[pivotIndex];

	for (unsigned int i = 0; i < pivotIndex; i++) {
		if (data[i] < pivot) {
			left.push_back(data[i]);
		}
		else { 
			right.push_back(data[i]);
		}
	}
	std::vector <unsigned int> newLeft = quicksort(left);
	std::vector <unsigned int> newRight = quicksort(right);
	data[newLeft.size()] = pivot;
	copy(newLeft.begin(), newLeft.end(), data.begin());
	copy(newRight.begin(), newRight.end(), data.begin() + newLeft.size() + 1);
	return data;
}

std::vector <unsigned int> Sort::quicksortMedian(std::vector <unsigned int> data) {
	if (data.size() <= 1) return data;
	
	std::vector <unsigned int> left;
	std::vector <unsigned int> right;
	unsigned int pivot = median(data);
	unsigned int pivotIndex = 0;
	if (pivot == data[data.size() - 1]) 
		pivotIndex = data.size() - 1;
	else if (pivot == data[data.size() / 2]) 
		pivotIndex = data.size() / 2;
	std::swap(data[pivotIndex], data[data.size() - 1]);

	for (unsigned int i = 0; i < data.size() - 1; i++) {
		if (data[i] < pivot) left.push_back(data[i]);
		else right.push_back(data[i]);
	}
	std::vector <unsigned int> newLeft = quicksort(left);
	std::vector <unsigned int> newRight = quicksort(right);
	data[newLeft.size()] = pivot;
	copy(newLeft.begin(), newLeft.end(), data.begin());
	copy(newRight.begin(), newRight.end(), data.begin() + newLeft.size() + 1);
	return data;
}

unsigned int Sort::median(std::vector <unsigned int> data) {
	std::vector <unsigned int> threeNumbers = {data[0], data[data.size() / 2], data[data.size() - 1]};
	threeNumbers = insertionsort(threeNumbers);
	return threeNumbers[1];
}

