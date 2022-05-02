CXXFLAGS = -std=c++17 -Wall -Wextra -Wpedantic
LIBS  = -lGL -lpthread -lX11

all: quadratur

quadratur.o: quadratur.cpp unit.h
	$(CXX) $(CXXFLAGS) -c $<

CalculateIntegral.o: CalculateIntegral.cpp CalculateIntegral.h
	$(CXX) $(CXXFLAGS) -c $<

quadratur: quadratur.o CalculateIntegral.o unit.o IGL.o
	$(CXX) $(CXXFLAGS) -o $@ $^ $(LIBS)

clean:
	rm -f quadratur quadratur.o CalculateIntegral.o

.PHONY: clean
