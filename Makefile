LIBS=-lsfml-graphics -lsfml-window -lsfml-system
CXXFLAGS=-O3

all:
	$(CXX) $(CXXFLAGS) mandelbrot.cpp $(LIBS) -o mandelbrot
