CXXFLAGS = -std=c++17 -Wall -Wextra -Wpedantic -O2 -fno-inline -fPIC -fPIE

precompiledTests : vector.o matrix.o test.o unit.h
	$(CXX) $(CXXFLAGS) -o precompiledTests unit.o vector.o matrix.o test.o

eigenvectorTests: loesung.o vector.o matrix.o
	$(CXX) $(CXXFLAGS) -o eigenvectorTests unit.o vector.o matrix.o loesung.o

vectorMatrixTests: vector.o matrix.o example_tests.o
	$(CXX) $(CXXFLAGS) -o vectorMatrixTests vector.o matrix.o example_tests.o

example_tests.o: example_tests.cpp
	$(CXX) $(CXXFLAGS) -c example_tests.cpp

vector.o: vector.cpp vector.h
	$(CXX) $(CXXFLAGS) -c vector.cpp

matrix.o: matrix.cpp matrix.h
	$(CXX) $(CXXFLAGS) -c matrix.cpp

loesung.o: loesung.cpp
	${CXX} ${CXXFLAGS} -c loesung.cpp

clean:
	rm -f matrix.o test loesung.o precompiledTests vector.o eigenvectorTests

.PHONY: clean