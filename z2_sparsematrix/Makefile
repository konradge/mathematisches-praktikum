CXX = g++
CXXFLAGS = -std=c++17 -Wall -Wextra -Wpedantic -O0 -fno-inline -fPIC -fPIE -g

.PHONY: clean

test: vector.o sparse_matrix.o test_mv.o
	$(CXX) $(CXXFLAGS) -o $@ $^

loesung: vector.o sparse_matrix.o loesung.cpp
	$(CXX) $(CXXFLAGS) -o $@ unit.o $^
	
sparse_matrix.o: sparse_matrix.cpp sparse_matrix.h vector.h
	$(CXX) $(CXXFLAGS) -c $<

vector.o: vector.cpp vector.h
	$(CXX) $(CXXFLAGS) -c $<

clean:
	rm -f vector.o sparse_matrix.o test

