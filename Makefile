CXX = g++
CXXFLAGS = -std=c++0x -Wall

OBJECTS = main.o colour.o newtonfractal.o newton.o polynomial.o complex.o

main: $(OBJECTS)
	$(CXX) $(CXXFLAGS) -o $@ $^

$(OBJECTS): colour.hpp newtonfractal.hpp newton.hpp polynomial.hpp complex.hpp