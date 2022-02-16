# Scheme turtle graphics

This repo contains the code for my project on how to create [Turtle graphics](https://en.wikipedia.org/wiki/Turtle_graphics) 
in the [Scheme programming language](https://en.wikipedia.org/wiki/Scheme_(programming_language)).

The program uses the GNU Guile implementation of the Scheme programming language. 
You can read more more about Guile on it's [Wikipedia page](https://en.wikipedia.org/wiki/GNU_Guile) or at it's [official GNU website](https://www.gnu.org/software/guile/).

## Installation
The first verison of the program depends on `GnuPlot`. 
This is due to the fact that the first version of the code is closely based on this [Tutorial Introduction to Guile](https://www.gnu.org/software/guile/docs/guile-tut/tutorial.html).

Naturally this code also depends on `libguile`.

The code also depends on the Gnu Multiple precision library `gmp` and `libffi` the Foreigh function call library.

I mainly wrote and tested this code on MacOs 12.01. 
In this version the easiest way (at lease for me) was to install the above mentioned tools and libs through `homebrew`.

At the writing of this `README` file the Homebrew formulae for Guile didn't link the headers and the libraries to the right places so including and linking always give nasty error messages.


The solution for this was to link the proper headers and the dynamic library to `/usr/local/include` and `/usr/local/lib`

Create symbolic link for the libraries
```
cd /usr/local/lib

ln -s ../Cellar/guile/3.0.8/lib/libguile-3.0.1.so libguile-3.0.1.so
ln -s ../Cellar/guile/3.0.8/lib/libguile-3.0.1.dylib libguile-3.0.1.dylib
ln -s ../Cellar/guile/3.0.8/lib/libguile-3.0.a libguile-3.0.a
```


Create symbolic link for the header files 
```
cd /usr/local/include

ln -s ../Cellar/guile/3.0.8/include/guile/3.0/libguile.h libguile.h
```

After this the executable could be linked by explicitely adding libguile to the linker list by `-lguile-3.0.1`




