# Handwritten Makefile for Scheme turtle graphics
# Please use the CMake version in a build directory and leave this as is 

all: tortoise graphics

clean:
	rm -f tortoise tortoise.o
	rm -f main main.o


tortoise: tortoise.c
	gcc $< -lguile-3.0.1 -o $@


graphics: graphics.cpp
	g++ $< -lSDL2 -o $@




