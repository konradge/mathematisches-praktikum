#ifndef SORTIEREN_H_
#define SORTIEREN_H_

#include <vector>
#include <stdio.h>
#include <stdlib.h>
#include <vector>
#include <iostream>

using namespace std;

    

namespace Sort {
   
   void print_vector(std::vector <unsigned int> data);

   std::vector < unsigned int> merge(std::vector < unsigned int> left,
	                                     unsigned int n_left,
	                                     std::vector < unsigned int> right,
	                                     unsigned int n_right);
   std::vector < unsigned int> mergesort(std::vector <unsigned int> data,
	                                        unsigned int n);

   std::vector < unsigned int> bubblesort(std::vector <unsigned int> data,
		  unsigned int n);

}
    
#endif
  

