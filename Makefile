# Handwritten Makefile for Scheme turtle graphics
# Please use the CMake version in a build directory and leave this as is 


.PHONY: clean build run

build: tortoise

clean:
	rm -f tortoise tortoise.o

run: tortoise
	./tortoise

tortoise: tortoise.o
	gcc $< -lguile-3.0.1 -o $@ 

tortoise.o: tortoise.c
	gcc -c $< -lguile-3.0.1 -o $@


