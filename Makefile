LIBS=-lsfml-graphics -lsfml-window -lsfml-system
CXXFLAGS=-O3

all:
	$(CXX) $(CXXFLAGS) main.cpp $(LIBS) -o mandelbrot
