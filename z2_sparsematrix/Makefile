CXX = g++
CXXFLAGS = -std=c++17 -Wall -Wextra -Wpedantic -O0 -fno-inline -fPIC -fPIE -g -fno-stack-protector

.PHONY: clean

custom_tests: vector.o sparse_matrix.o custom_tests.cpp
	${CXX} ${CXXFLAGS} -o $@ $^

test: vector.o sparse_matrix.o test_mv.o
	$(CXX) $(CXXFLAGS) -o $@ $^

loesung: vector.o sparse_matrix.o loesung.cpp
	$(CXX) $(CXXFLAGS) -o $@ unit.o $^
	
sparse_matrix.o: sparse_matrix.cpp sparse_matrix.h vector.h
	$(CXX) $(CXXFLAGS) -c $<

vector.o: vector.cpp vector.h
	$(CXX) $(CXXFLAGS) -c $<

clean:
	rm -f custom_tests test loesung sparse_matrix.o vector.o

