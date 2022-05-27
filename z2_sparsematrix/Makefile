CXX = g++
CXXFLAGS = -std=c++17 -Wall -Wextra -Wpedantic -O2 -fno-inline -fPIC -fPIE

.PHONY: clean

test: vector.o sparse_matrix.o
	$(CXX) $(CXXFLAGS) -o $@ test_mv $<
	
sparse_matrix.o: sparse_matrix.cpp sparse_matrix.h vector.h
	$(CXX) $(CXXFLAGS) -c $<

vector.o: vector.cpp vector.h
	$(CXX) $(CXXFLAGS) -c $<

clean:
	rm -f vector.o sparse_matrix.o

