CXX = g++
CXXFLAGS = -std=c++17 -Wall -Wextra -Wpedantic -O2 -fno-inline -fPIC -fPIE

precompiledTests : vector.o matrix.o test.o
	$(CXX) $(CXXFLAGS) -o precompiledTests vector.o matrix.o test.o

vector.o: vector.cpp vector.h
	$(CXX) $(CXXFLAGS) -c vector.cpp

matrix.o: matrix.cpp matrix.h
	$(CXX) $(CXXFLAGS) -c matrix.cpp

loesung.o: loesung.cpp
	${CXX} ${CXXFLAGS} -c loesung.cpp

clean:
	rm -f matrix.o test loesung.o

.PHONY: clean