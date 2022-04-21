// Copyright (c) 2022, The MaPra Authors.

#include "mapra_test.h"

#include <algorithm>
#include <iostream>
#include <string>

#include "Sort.h"
#include "unit.h"

void test_algorithm(unsigned int number);

int main() {
	for (auto & number: {0, 1, 2, 3, 4, 5, 6})
		test_algorithm(number);

  return 0;
}


void test_algorithm(unsigned int number) {
	std::vector <unsigned int> (*algorithm)(std::vector <unsigned int>);
	std::string algorithmName = "";
	switch (number) {
		case 0:
			algorithmName = "bubblesort";
			algorithm = &(Sort::bubblesort);
			break;
		case 1:
			algorithmName = "mergesort";
			algorithm = &(Sort::mergesort);
			break;
		case 2:
			algorithmName = "selectionsort";
			algorithm = &(Sort::selectionsort);
			break;
		case 3:
			algorithmName = "insertionsort";
			algorithm = &(Sort::insertionsort);
			break;
		case 4:
			algorithmName = "heapsort";
			algorithm = &(Sort::heapsort);
			break;
		case 5:
			algorithmName = "quicksort";
			algorithm = &(Sort::quicksort);
			break;
		default: // case 6
			algorithmName = "quicksortMedian";
			algorithm = &(Sort::quicksortMedian);	
	}

	

	mapra::MapraTest test(algorithmName);

	for (auto & c: algorithmName) c = toupper(c);

	cout << "-----" + algorithmName + "-----" << endl;
	
	cout << "-----test with empty vector-----" << endl;
	std::vector <unsigned int> data0 = {};
	test.AssertEq(" ", algorithm(data0), data0);
	cout << endl;

	cout << "-----test with a vector with one element-----" << endl;
	std::vector <unsigned int> data1 = { 1 };

	test.AssertEq(" ", algorithm(data1), data1);
	cout << endl;

	cout << "-----test with vector with even number of elements -----" << endl;
	std::vector <unsigned int> data2 = mapra::GetExample(1, 10);
	Sort::print_vector(data2);
	data2 = algorithm(data2);
	Sort::print_vector(data2);
	mapra::CheckSolution(*&data2);
	cout << endl;

	cout << "-----test with vector with uneven number of elements -----" << endl;
	std::vector <unsigned int> data3 = mapra::GetExample(1, 11);
	Sort::print_vector(data3);
	data3 = algorithm(data3);
	Sort::print_vector(data3);
	mapra::CheckSolution(*&data3);
	cout << endl;

	cout << "-----test with a sorted vector-----" << endl;
	std::vector <unsigned int> data4 = mapra::GetExample(2, 10);
	Sort::print_vector(data4);
	data4 = algorithm(data4);
	Sort::print_vector(data4);
	mapra::CheckSolution(*&data4);
	cout << endl;

	cout << "-----test with a inverse sorted vector-----" << endl;
	std::vector <unsigned int> data5 = mapra::GetExample(3, 10);
	Sort::print_vector(data5);
	data5 = algorithm(data5);
	Sort::print_vector(data5);
	mapra::CheckSolution(*&data5);
	cout << endl;

	cout << "-----test with quicksort median aus 3 killer----- " << endl;
	std::vector <unsigned int> data6 = mapra::GetExample(4, 10);
	Sort::print_vector(data6);
	data6 = algorithm(data6);
	Sort::print_vector(data6);
	mapra::CheckSolution(*&data6);
	cout << endl;
}

