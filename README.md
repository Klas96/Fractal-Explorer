# Fractal Explorer

Fractal Generators in C.

Fractals included are MandelBrot, Julia, Generalized Mandelbrot.


## How to Use

./Mandelbrot xMin xMax yMin yMax


# Mandelbrot

Test if a complex number \( c \) is a member of the Mandelbrot set.

$$f_c(z) = z^2 + c$$

$$z_{n+1} = z_n^2 + c$$

A complex number \( c \) is a member of the Mandelbrot set if, when starting with \( z_0 = 0 \) and applying the iteration repeatedly, the absolute value of \( z_n \) remains bounded for all \( n > 0 \).


Mandelbrot Set render

![alt text for screen readers](Images/Mandelbrot.png "Mandelbrot")

## Interesting points to render:

Try rendering

./Mandelbrot 0.425 0.43 -0.2325 -0.23

./Mandelbrot -1.63 -1.62 -0.03 -0.02

Coordinates: -0.761574, -0.0847596

# Julia

$$f_c(z) = z^2 + c$$

$$z_{n+1} = z_n^2 + c$$

Julia Set render

![alt text for screen readers](Images/Julia.png "Julia")


## Intresting points to render:


# Multibrot

Generalized Mandelbrot Set render

![alt text for screen readers](Images/Multibrot.png "Generalized Mandelbrot")

# Chaos Game

Generate N points, choose a starting point at random between these N points. Choose a vertex at random and move halfway towards that vertex from the current point. Continue this process many times, eventually generating a pattern of points within the polygon.


# Compile and Run

gcc mandelbrot.c -o mandelbrot

## Run

To run the Mandelbrot program, use:

./mandelbrot

## TODO

pack fractal function in function make loop use that function

better make file

Abstact up Color method to use in all fractals
Colors
Argument as parameter x= osv
Out images Argument

Max Iter as argument to getColor