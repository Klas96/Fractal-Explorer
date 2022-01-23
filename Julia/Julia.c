#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <stdint.h>

#include "getColor.h"


/*
unsigned char setColor(){
  66  30  15 // brown 3
  25   7  26 // dark violett
   9   1  47 // darkest blue
   4   4  73 // blue 5
   0   7 100 // blue 4
  12  44 138 // blue 3
  24  82 177 // blue 2
  57 125 209 // blue 1
  134 181 229 // blue 0
  211 236 248 // lightest blue
  241 233 191 // lightest yellow
  248 201  95 // light yellow
  255 170   0 // dirty yellow
  204 128   0 // brown 0
  153  87   0 // brown 1
  106  52   3 // brown 2
}
*/


int main(int argc, char* argv[]){

  /* The window in the plane. */
  const double xmin = -2;
  const double xmax = 2;
  const double ymin = -2;
  const double ymax = 2;

  /* Maximum number of iterations, at most 65535. */
  const uint16_t maxiter = 500;

  /* Image size, width is given, height is computed. */
  const int xres = 2000;
  const int yres = (xres*(ymax-ymin))/(xmax-xmin);

  double Cf;
  char name[16];

  /* Precompute pixel width and height. */
  double dx=(xmax-xmin)/xres;
  double dy=(ymax-ymin)/yres;

  double x, y; /* Coordinates of the current point in the complex plane. */
  double u, v; /* Coordinates of the iterated point. */
  int i,j; /* Pixel counters */
  int k; /* Iteration counter */

  for(int bil = 1; bil <= 100; bil++){

    Cf = -2 + 0.04*bil;

    printf("skpar Bild: %f\n",Cf);

    /* The output file name */
    snprintf(name, 15*sizeof(char), "Julia_%i.ppm",bil);

    //const char* filename = "Julia.ppm";

    /* Open the file and write the header. */
    FILE * fp = fopen(name,"wb");
    char *comment="# Julia Set";/* comment should start with # */

    /*write ASCII header to the file*/
    fprintf(fp,
            "P6\n# Julia, xmin=%lf, xmax=%lf, ymin=%lf, ymax=%lf, maxiter=%d\n%d\n%d\n%d\n",
            xmin, xmax, ymin, ymax, maxiter, xres, yres, (maxiter < 256 ? 256 : maxiter));

    for (j = 0; j < yres; j++) {
      y = ymax - j * dy;
      for(i = 0; i < xres; i++) {
        x = xmin + i * dx;
        //double u = 0.0;
        //double v= 0.0;
        double u = x;
        double v= y;
        double u2 = u * u;
        double v2 = v*v;

        /* iterate the point */
        for (k = 1; k < maxiter && (u2 + v2 < 4.0); k++) {
              v = 2 * u * v + Cf;
              u = u2 - v2;
              u2 = u * u;
              v2 = v * v;
        };
        /* compute  pixel color and write it to file */
        if (k >= maxiter) {
          /* interior */
          const unsigned char black[] = {0, 0, 0, 0, 0, 0};
          fwrite (black, 6, 1, fp);
        }
        else {
          /* exterior */
          //RGB
          int * color = getColor(k);

          fwrite(color, 6, 1, fp);
        };
      }
    }
    fclose(fp);
  }

  return 0;
}
