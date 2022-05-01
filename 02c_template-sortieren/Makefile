CXXFLAGS = -std=c++17 -g -Wall -Wextra -Wpedantic -O2 -fno-inline -fPIC -fPIE

main: main.o unit.o student.o
	$(CXX) $(CXXFLAGS) -o $@ $^

main.o: main.cpp main.h
	${CXX} ${CXXFLAGS} -c $<

# sort.o: sort.cpp student.h
# 	$(CXX) $(CXXFLAGS) -c $<

student.o: student.cpp student.h
	$(CXX) $(CXXFLAGS) -c $<

clean:
	rm -f student.o main.o main

.PHONY: clean
