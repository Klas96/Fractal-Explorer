

# Fractal Explorer

Fractal Generators in C.

Fractals included are MandelBrot, Julia, Generalized Mandelbrot.


## How to Use

./Mandelbrot xMin xMax yMin yMax


# Mandelbrot

$$f_c(z) = z^2 + c$$

MandelBrot Set render

![alt text for screen readers](Images/Mandelbrot.png "Mandelbrot")

## Intresting points to render:

Try rendering

./Mandelbrot 0.425 0.43 -0.2325 -0.23

./Mandelbrot -1.63 -1.62 -0.03 -0.02

-0.761574,-0.0847596
# Julia

Julia Set render

![alt text for screen readers](Images/Julia.png "Mandelbrot")


## Intresting points to render:


# Generalized Mandelbrot

Generalized MandelBrot Set render

![alt text for screen readers](Images/Generalized_Mandelbrot.png "Generalized Mandelbrot")



# Compile and Run

gcc mandelbrot.c -o mandelbrot

## Run

./mandelbrot

## TODO

pack fractal function in function make loop use that function

better make file

Abstact up Color method to use in all fractals
Colors
Argument as parameter x= osv
Out images Argument

Max Iter as argument to getColor