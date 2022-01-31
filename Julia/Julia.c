#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <stdint.h>

#include "../getColor.h"


double* parseArguments(int argc, char* argv[]) {

  double* ret = malloc(4*sizeof(double));

  double xmin = -2;
  double xmax = 2;
  double ymin = -2;
  double ymax = 2;

  if(argc<=4) {
    printf("Not enugh Arguments Entered using default area. \n ");
    printf("x: %f to %f and y: %f to %f \n", xmin, xmax, ymin, ymax);
  }
  else {
    if (atof(argv[1]) < atof(argv[2])) {
      xmin = atof(argv[1]);
      xmax = atof(argv[2]);
    }
    else {
      printf("xMin: %f have to be smaler than xMax= %f", atof(argv[1]), atof(argv[2]));
    }

    if (atof(argv[3]) < atof(argv[4])) {
      ymin = atof(argv[3]);
      ymax = atof(argv[4]);
    }
    else {
      printf("yMin: %f have to be smaler than yMax= %f", atof(argv[3]), atof(argv[4]));
    }

    printf("x: %f to %f and y: %f to %f \n", xmin, xmax, ymin, ymax);
    // TODO Check if arguments is valid
    // That is min < max
  }

  ret[0] = xmin;
  ret[1] = xmax;
  ret[2] = ymin;
  ret[3] = ymax;

  return(ret);
}


int main(int argc, char* argv[]){

  /* The window in the plane. */
  double xmin = -2;
  double xmax = 2;
  double ymin = -2;
  double ymax = 2;

  /* The window in the plane. */
  if(argc<=4) {
      printf("Not enugh Arguments Entered using default area. \n ");

      printf("x: %f to %f and y: %f to %f \n", xmin, xmax, ymin, ymax);
  }
  else {
    if (atof(argv[1]) < atof(argv[2])) {
      xmin = atof(argv[1]);
      xmax = atof(argv[2]);
    }
    else {
      printf("xMin: %f have to be smaler than xMax= %f", atof(argv[1]), atof(argv[2]));
    }

    if (atof(argv[3]) < atof(argv[4])) {
      ymin = atof(argv[3]);
      ymax = atof(argv[4]);
    }
    else {
      printf("yMin: %f have to be smaler than yMax= %f", atof(argv[3]), atof(argv[4]));
    }

    printf("x: %f to %f and y: %f to %f \n", xmin, xmax, ymin, ymax);
    // TODO Check if arguments is valid
    // That is min < max
  }

  /* Maximum number of iterations, at most 65535. */
  //Seams to change the color
  const uint16_t maxiter = 500;

  /* Image size, width is given, height is computed. */
  const int xres = 2000;
  const int yres = (xres*(ymax-ymin))/(xmax-xmin);

  double Cf;

  char name[16];
  snprintf(name, 15*sizeof(char), "Julia.ppm");

  FILE * fp = fopen(name,"wb");

  /* The output file name */
  fprintf(fp,"P3\n%d %d\n255\n",xres, yres);

  /* Open the file and write the header. */
  char *comment="# Julia Set";/* comment should start with # */


  /* Precompute pixel width and height. */
  double dx=(xmax-xmin)/xres;
  double dy=(ymax-ymin)/yres;

  double x, y; /* Coordinates of the current point in the complex plane. */
  double u, v; /* Coordinates of the iterated point. */
  int i,j; /* Pixel counters */
  int k; /* Iteration counter */

  int *color = malloc(3*sizeof(int));

  Cf = 0.75;

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
