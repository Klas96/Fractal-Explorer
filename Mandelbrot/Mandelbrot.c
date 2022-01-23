#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <stdint.h>

#include "getColor.h"

int main(int argc, char* argv[]){

  /* TODO Take in area to render as argument 
  printf("Arguments:");
  char * endpt;
  int t = strtol(argv[1]+2, &endpt,10) + 2;
  int l = strtol(argv[2]+2, &endpt,10);
  int d = strtol(argv[3], &endpt,10);
  */


  /* The window in the plane. */
  //TODO take out arguments from user
  const double xmin = -2;
  const double xmax = 2;
  const double ymin = -2;
  const double ymax = 2;

  /* Maximum number of iterations, at most 5000. */
  const uint16_t maxiter = 5000;

  /* Image size, width is given, height is computed. */
  const int xres = 2000;
  const int yres = (xres*(ymax-ymin))/(xmax-xmin);

  /* The output file name */
  const char* filename = "Mandelbrot.ppm";

  /* Open the file and write the header. */
  FILE * fp = fopen(filename,"wb");
  char *comment="# Mandelbrot set";/* comment should start with # */

  /*write ASCII header to the file*/
  fprintf(fp,
          "P6\n# Mandelbrot, xmin=%lf, xmax=%lf, ymin=%lf, ymax=%lf, maxiter=%d\n%d\n%d\n%d\n",
          xmin, xmax, ymin, ymax, maxiter, xres, yres, (maxiter < 256 ? 256 : maxiter));

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
      double v= 0.0;
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
      if (k >= maxiter) {
        /* interior */
        const unsigned char black[] = {0, 0, 0, 0, 0, 0};
        fwrite (black, 6, 1, fp);
      }
      else {
        /* exterior */
        //RGB
        //unsigned char color[6];
        //color[0] = k*3 >> 8;
        //color[1] = k*3 & 255;
        //color[2] = k*2 >> 8;
        //color[3] = k*2 & 255;
        //color[4] = k >> 8;
        //color[5] = k & 255;
        int * color = getColor(k);
        fwrite(color, 6, 1, fp);
      };
    }
  }
  fclose(fp);
  return 0;
}
