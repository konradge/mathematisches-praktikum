CXX = g++
CXXFLAGS = -std=c++17 -Wall -Wextra -Wpedantic -O2 -fno-inline -fPIC -fPIE
test : matrix.o test.o
	$(CXX) $(CXXFLAGS) -o test test.o matrix.o

matrix.o: matrix.cpp matrix.h
	$(CXX) $(CXXFLAGS) -c matrix.cpp

clean:
	rm -f matrix.o test

.PHONY: clean