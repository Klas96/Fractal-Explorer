#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <stdint.h>

#include "getColor.h"


int main(int argc, char* argv[]){

  /* The window in the plane. */
  const double xmin = -2;
  const double xmax = 2;
  const double ymin = -2;
  const double ymax = 2;

  /* Maximum number of iterations, at most 65535. */
  //Seams to change the color
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

  int *color = malloc(3*sizeof(int));

  Cf = -2+1+1+0.5+0.25;


  /* The output file name */
  snprintf(name, 15*sizeof(char), "Julia.ppm");

  //const char* filename = "Julia.ppm";

  /* Open the file and write the header. */
    FILE * fp = fopen(name,"wb");
    char *comment="# Julia Set";/* comment should start with # */

  /*write ASCII header to the file*/
  fprintf(fp,"P3\n%d %d\n255\n",xres, yres);

  /*
  fprintf(fp,
          "P3\n# Julia, xmin=%lf, xmax=%lf, ymin=%lf, ymax=%lf, maxiter=%d\n%d\n%d\n%d\n",
          xmin, xmax, ymin, ymax, maxiter, xres, yres, (maxiter < 256 ? 256 : maxiter));
  */
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

      color = getColor(k);
      fprintf(fp, "%d %d %d  ",color[0],color[1],color[2]);

    }
    fprintf(fp,"\n");
  }
  fclose(fp);
  return 0;
}
