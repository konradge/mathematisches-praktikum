#ifndef SORTIEREN_H_
#define SORTIEREN_H_

#include <vector>
#include <stdio.h>
#include <stdlib.h>
#include <vector>
#include <iostream>

using namespace std;

    

class Sort {
   public :
    	Sort() {}
	          
   public: 
	   void print_vector(std::vector <unsigned int> data);


   public: 
	   std::vector < unsigned int> merge(std::vector < unsigned int> left,
	                                     unsigned int n_left,
	                                     std::vector < unsigned int> right,
	                                     unsigned int n_right);

  public: std::vector < unsigned int> mergeSort(std::vector <unsigned int> data,
	                                            unsigned int n);
};
    
#endif
  

