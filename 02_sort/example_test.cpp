// Copyright (c) 2022, The MaPra Authors.

#include "mapra_test.h"

#include <algorithm>
#include <iostream>
#include <string>

#include "Sort.h"
#include "unit.h"

void test_bubblesort();
void test_mergesort();
void test_quicksort();
void test_selectionsort();
void test_insertionsort();
void test_heapsort();
void test_quicksortMedian();

int main() {
	test_bubblesort();

  return 0;
}


void test_bubblesort() {
	mapra::MapraTest test("bubblesort");
	cout << "-----test with  empty vector-----" << endl;
	std::vector <unsigned int> data0;
	test.AssertEq(" ", Sort::bubblesort(data0), data0);
	cout << endl;

	cout << "-----test with a vector with one element-----" << endl;
	std::vector <unsigned int> data1 = { 1 };

	test.AssertEq(" ", Sort::bubblesort(data1), data1);
	cout << endl;

	cout << "-----test with a vector with a even number of element-----" << endl;
	std::vector <unsigned int> data2 = mapra::GetExample(1, 10);
	data2 = Sort::bubblesort(data2);
	mapra::CheckSolution(*&data2);
	cout << endl;


	cout << "-----test with a vector with a uneven number of element1 -----" << endl;
	std::vector <unsigned int> data3 = mapra::GetExample(1, 11);
	data3 = Sort::bubblesort(data3);
	mapra::CheckSolution(*&data3);
	cout << endl;

	cout << "-----test with a sorted vector-----" << endl;
	std::vector <unsigned int> data4 = mapra::GetExample(2, 10);
	data4 = Sort::bubblesort(data4);
	mapra::CheckSolution(*&data4);
	cout << endl;

	cout << "-----test with a inverse sorted vector-----" << endl;
	std::vector <unsigned int> data5 = mapra::GetExample(3, 10);
	data5 = Sort::bubblesort(data5);
	mapra::CheckSolution(*&data5);
	cout << endl;

	cout << "-----test with quicksort median aus 3 killer----- " << endl;
	std::vector <unsigned int> data6 = mapra::GetExample(4, 10);
	data6 = Sort::bubblesort(data6);
	mapra::CheckSolution(*&data6);
	cout << endl;


}

void test_mergesort() {
	mapra::MapraTest test("mergesort");
	cout << "-----test with  empty vector-----" << endl;
	std::vector <unsigned int> data0;
	test.AssertEq(" ", Sort::mergesort(data0), data0);
	cout << endl;

	cout << "-----test with a vector with one element-----" << endl;
	std::vector <unsigned int> data1 = { 1 };

	test.AssertEq(" ", Sort::mergesort(data1), data1);
	cout << endl;

	cout << "-----test with a vector with a even number of element-----" << endl;
	std::vector <unsigned int> data2 = mapra::GetExample(1, 10);
	data2 = Sort::mergesort(data2);
	mapra::CheckSolution(*&data2);
	cout << endl;


	cout << "-----test with a vector with a uneven number of element1 -----" << endl;
	std::vector <unsigned int> data3 = mapra::GetExample(1, 11);
	data3 = Sort::mergesort(data3);
	mapra::CheckSolution(*&data3);
	cout << endl;

	cout << "-----test with a sorted vector-----" << endl;
	std::vector <unsigned int> data4 = mapra::GetExample(2, 10);
	data4 = Sort::mergesort(data4);
	mapra::CheckSolution(*&data4);
	cout << endl;

	cout << "-----test with a inverse sorted vector-----" << endl;
	std::vector <unsigned int> data5 = mapra::GetExample(3, 10);
	data5 = Sort::merge(data5);
	mapra::CheckSolution(*&data5);
	cout << endl;

	cout << "-----test with quicksort median aus 3 killer----- " << endl;
	std::vector <unsigned int> data6 = mapra::GetExample(4, 10);
	data6 = Sort::mergesort(data6);
	mapra::CheckSolution(*&data6);
	cout << endl;
}
void test_quicksort() {
	mapra::MapraTest test("quicksort");
	cout << "-----test with  empty vector-----" << endl;
	std::vector <unsigned int> data0;
	test.AssertEq(" ", Sort::quicksort(data0), data0);
	cout << endl;

	cout << "-----test with a vector with one element-----" << endl;
	std::vector <unsigned int> data1 = { 1 };

	test.AssertEq(" ", Sort::quicksort(data1), data1);
	cout << endl;

	cout << "-----test with a vector with a even number of element-----" << endl;
	std::vector <unsigned int> data2 = mapra::GetExample(1, 10);
	data2 = Sort::quicksort(data2);
	mapra::CheckSolution(*&data2);
	cout << endl;


	cout << "-----test with a vector with a uneven number of element1 -----" << endl;
	std::vector <unsigned int> data3 = mapra::GetExample(1, 11);
	data3 = Sort::quicksort(data3);
	mapra::CheckSolution(*&data3);
	cout << endl;

	cout << "-----test with a sorted vector-----" << endl;
	std::vector <unsigned int> data4 = mapra::GetExample(2, 10);
	data4 = Sort::quicksort(data4);
	mapra::CheckSolution(*&data4);
	cout << endl;

	cout << "-----test with a inverse sorted vector-----" << endl;
	std::vector <unsigned int> data5 = mapra::GetExample(3, 10);
	data5 = Sort::quicksort(data5);
	mapra::CheckSolution(*&data5);
	cout << endl;

	cout << "-----test with quicksort median aus 3 killer----- " << endl;
	std::vector <unsigned int> data6 = mapra::GetExample(4, 10);
	data6 = Sort::quicksort(data6);
	mapra::CheckSolution(*&data6);
	cout << endl;
}
void test_selectionsort() {
	mapra::MapraTest test("");
	cout << "-----test with  empty vector-----" << endl;
	std::vector <unsigned int> data0;
	test.AssertEq(" ", Sort::(data0), data0);
	cout << endl;

	cout << "-----test with a vector with one element-----" << endl;
	std::vector <unsigned int> data1 = { 1 };

	test.AssertEq(" ", Sort::(data1), data1);
	cout << endl;

	cout << "-----test with a vector with a even number of element-----" << endl;
	std::vector <unsigned int> data2 = mapra::GetExample(1, 10);
	data2 = Sort::(data2);
	mapra::CheckSolution(*&data2);
	cout << endl;


	cout << "-----test with a vector with a uneven number of element1 -----" << endl;
	std::vector <unsigned int> data3 = mapra::GetExample(1, 11);
	data3 = Sort::(data3);
	mapra::CheckSolution(*&data3);
	cout << endl;

	cout << "-----test with a sorted vector-----" << endl;
	std::vector <unsigned int> data4 = mapra::GetExample(2, 10);
	data4 = Sort::(data4);
	mapra::CheckSolution(*&data4);
	cout << endl;

	cout << "-----test with a inverse sorted vector-----" << endl;
	std::vector <unsigned int> data5 = mapra::GetExample(3, 10);
	data5 = Sort::(data5);
	mapra::CheckSolution(*&data5);
	cout << endl;

	cout << "-----test with quicksort median aus 3 killer----- " << endl;
	std::vector <unsigned int> data6 = mapra::GetExample(4, 10);
	data6 = Sort::(data6);
	mapra::CheckSolution(*&data6);
	cout << endl;
}
void test_insertionsort();
void test_heapsort();
void test_quicksortMedian();