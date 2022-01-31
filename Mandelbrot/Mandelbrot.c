#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <stdint.h>

#include "../getColor.h"
#include "../argumentParser.h"


int main(int argc, char *argv[]){

  double arguments[4];
  parseArguments(argc, argv, arguments);

  double xmin = arguments[0];
  double xmax = arguments[1];
  double ymin = arguments[2];
  double ymax = arguments[3];

  /* The output file name */
  const char* filename = "Mandelbrot.ppm";

  /* Maximum number of iterations, at most 5000. */
  const uint16_t maxiter = 500;

  /* Image size, width is given, height is computed. */
  const int xres = 2000;
  //How to handel if negative
  const int yres = (xres*(ymax-ymin))/(xmax-xmin);

  int *color = malloc(3*sizeof(int));

  /* Open the file and write the header. */
  FILE * fp = fopen(filename,"wb");
  char *comment="# Mandelbrot set";/* comment should start with # */

  /*write ASCII header to the file*/
  fprintf(fp,"P3\n%d %d\n255\n",xres, yres);

  /*
  fprintf(fp,
          "P3\n# Mandelbrot, xmin=%lf, xmax=%lf, ymin=%lf, ymax=%lf, maxiter=%d\n%d\n%d\n%d\n",
          xmin, xmax, ymin, ymax, maxiter, xres, yres, (maxiter < 256 ? 256 : maxiter));
  */
  /* Precompute pixel width and height. */
  double dx=(xmax-xmin)/xres;
  double dy=(ymax-ymin)/yres;

  double x, y; /* Coordinates of the current point in the complex plane. */
  double u, v; /* Coordinates of the iterated point. */
  int i,j; /* Pixel counters */
  int k; /* Iteration counter */
  for (j = 0; j < yres; j++) {
    y = ymax - j * dy;
    for(i = 0; i < xres; i++) {
      double u = 0.0;
      double v = 0.0;
      double u2 = u * u;
      double v2 = v*v;
      x = xmin + i * dx;
      /* iterate the point */
      for (k = 1; k < maxiter && (u2 + v2 < 4.0); k++) {
            v = 2 * u * v + y;
            u = u2 - v2 + x;
            u2 = u * u;
            v2 = v * v;
      };
      /* compute  pixel color and write it to file */
      color = getColor(k);
      fprintf(fp, "%d %d %d  ",color[0],color[1],color[2]);
      //fwrite(color, 6, 1, fp);
    }
    fprintf(fp,"\n");
  }
  fclose(fp);
  return 0;
}
