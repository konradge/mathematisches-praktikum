CXX = g++
CXXFLAGS = -std=c++17 -Wall -Wextra -Wpedantic -O2 -fno-inline -fPIC -fPIE -g

precompiledTests : vector.o matrix.o test.o unit.h
	$(CXX) $(CXXFLAGS) -o precompiledTests unit.o vector.o matrix.o test.o

eigenvectorTests: loesung.o vector.o matrix.o
	$(CXX) $(CXXFLAGS) -o eigenvectorTests unit.o vector.o matrix.o loesung.o

vector.o: vector.cpp vector.h
	$(CXX) $(CXXFLAGS) -c vector.cpp

matrix.o: matrix.cpp matrix.h
	$(CXX) $(CXXFLAGS) -c matrix.cpp

loesung.o: loesung.cpp
	${CXX} ${CXXFLAGS} -c loesung.cpp

clean:
	rm -f matrix.o test loesung.o precompiledTests vector.o eigenvectorTests

.PHONY: clean