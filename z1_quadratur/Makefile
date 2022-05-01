CXXFLAGS = -std=c++17 -Wall -Wextra -Wpedantic -O2 -fno-inline -fPIC -fPIE


main: main.o
	$(CXX) $(CXXFLAGS) -o $@ IGL.o -lGL -lpthread -lX11 unit.o main.o CalculateIntegral.o

main.o: main.cpp
	${CXX} ${CXXFLAGS} -c $<

CalculateIntegral.o: CalculateIntegral.cpp
	${CXX} ${CXXFLAGS} -c $<

clean:
	rm -f main.o main

.PHONY: clean
