#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>

int main() {
    int n = 100000; // number of iterations
    float x = 0.0, y = 0.0; // starting point
    float vertices[3][2] = {{0.0, 0.0}, {1.0, 0.0}, {0.5, 0.866}}; // triangle vertices

    // seed the random number generator
    srand(time(NULL));

    // iterate the chaos game
    for (int i = 0; i < n; i++) {
        // randomly select a vertex
        int r = rand() % 3;
        // move halfway towards the selected vertex
        x = (x + vertices[r][0]) / 2;
        y = (y + vertices[r][1]) / 2;
        // plot the point
        printf("%f,%f\n", x, y);
    }

    return 0;
}
