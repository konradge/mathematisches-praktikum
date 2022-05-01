CXXFLAGS = -std=c++17 -Wall -Wextra -Wpedantic -O2 -fno-inline -fPIC -fPIE

main: main.o sort.o unit.o student.o
	$(CXX) $(CXXFLAGS) -o $@ $^

main.o: main.cpp
	${CXX} ${CXXFLAGS} -c $<

sort.o: sort.cpp student.h
	$(CXX) $(CXXFLAGS) -c $<

student.o: student.cpp student.h
	$(CXX) $(CXXFLAGS) -c $<

clean:
	rm -f student.o sort.o sort

.PHONY: clean
