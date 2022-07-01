CXXFLAGS = -std=c++17 -Wall -g  -Wextra -Wpedantic
LIBS = -lGL -lpthread -lX11


all: nullstellen

nullstellen.o: nullstellen.cpp unit.h
	$(CXX) $(CXXFLAGS)  -c $<

nullstellen: nullstellen.o unit.o IGL.o
	$(CXX) $(CXXFLAGS) -o $@ $^ $(LIBS)

clean:
	rm -f nullstellen nullstellen.o

.PHONY: all clean
