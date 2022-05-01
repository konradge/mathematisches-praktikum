CXXFLAGS = -std=c++17 -Wall -Wextra -Wpedantic -O2 -fno-inline -fPIC -fPIE

tests: main.o tests.o unit.o student.o
	$(CXX) $(CXXFLAGS) -o $@ $^

main: main.o unit.o student.o
	$(CXX) $(CXXFLAGS) -o $@ $^

tests.o: tests.cpp
	${CXX} ${CXXFLAGS} -c $<

main.o: main.cpp main.h sort.h
	${CXX} ${CXXFLAGS} -c $<

student.o: student.cpp student.h
	$(CXX) $(CXXFLAGS) -c $<

clean:
	rm -f student.o main.o tests.o main tests

.PHONY: clean
