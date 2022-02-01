#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <stdint.h>

#include "../getColor.h"
#include "../argumentParser.h"

/* Maximum number of iterations */

void GetBinomialSum(double *complexNum, int power){
  /* Takes complexNum to power */
  /* Binomial Sum */
  double u = complexNum[0];
  double v = complexNum[1];
  double uPow = 0;
  double vPow = 0;
  for (int iKoef = 0; iKoef <= power; iKoef++) {
      /* Calculate Binomial Coefitent */
      int factorialKoefToPower = 1;
      for (int iFactorial = (power-iKoef + 1); iFactorial <= power; iFactorial++) {
        factorialKoefToPower = factorialKoefToPower * iFactorial;
      }

      int factorialKoef = 1;
      for (int iFactorial = 1; iFactorial <= iKoef; iFactorial++) {
        factorialKoef = factorialKoef * iFactorial;
      }
      if (iKoef == 0){
        factorialKoef = 1;
      }

      int binomialKoef = factorialKoefToPower/factorialKoef;

      /* Komplex Factor */
      if ( iKoef % 4 == 0 ) {
          uPow = uPow + binomialKoef * pow(u,power-iKoef) * pow(v,iKoef);
      }
      else if ( iKoef % 4 == 1 ) {
          vPow = vPow + binomialKoef * pow(u,power-iKoef) * pow(v,iKoef);
      }
      else if ( iKoef % 4 == 2 ) {
          uPow = uPow - binomialKoef * pow(u,power-iKoef) * pow(v,iKoef);
      }
      else  {
          vPow = vPow - binomialKoef * pow(u,power-iKoef) * pow(v,iKoef);
      }

  };

  complexNum[0] = uPow;
  complexNum[1] = vPow;
}

int main(int argc, char* argv[]){

  double arguments[4];
  parseArguments(argc, argv, arguments);

  double xmin = arguments[0];
  double xmax = arguments[1];
  double ymin = arguments[2];
  double ymax = arguments[3];

  /* Image size, width is given, height is computed. */
  const int xres = 2000;
  const int yres = (xres*(ymax-ymin))/(xmax-xmin);

  /* Level of Mandelbrot. */
  const int power = 6;

  /* The output file name */
  const char* filename = "Multibrot.ppm";

  /* Open the file and write the header. */
  FILE * fp = fopen(filename,"wb+");
  char *comment="# Mandelbrot set";/* comment should start with # */

  /*write ASCII head# Mandelbrot, xmin=%lf, xmax=%lf, ymin=%lf, ymax=%lf, maxiter=%der to the file*/
  fprintf(fp,"P3\n%d %d\n255\n",xres, yres);

  /* Precompute pixel width and height. */
  double dx=(xmax-xmin)/xres;
  double dy=(ymax-ymin)/yres;

  double x, y; /* Coordinates of the current point in the complex plane. */
  double u, v; /* Coordinates of the iterated point. u is reel and v is coplex. */
  
  int i,j; /* Pixel counters */
  int k; /* Iteration counter */

  double *complexNumTest = malloc(2*sizeof(double));
  
  int *color = malloc(3*sizeof(int));
  
  for (j = 0; j < yres; j++) {

    y = ymax - j * dy;
    
    for(i = 0; i < xres; i++) {
      double u = 0.0;
      double v = 0.0;
      double u2 = 0.0;
      double v2 = 0.0;
      double uPow = 0.0;
      double vPow = 0.0;
      complexNumTest[0] = 0.0;
      complexNumTest[1] = 0.0;

      x = xmin + i * dx;
      /* iterate the point */
      for (k = 0; k < maxiter && (u2 + v2 < 4.0); k++) {
        /* Binomial Sum */
        for (int iKoef = 0; iKoef <= power; iKoef++) {
            /* Calculate Binomial Coefitent */
            int factorialKoefToPower = 1;
            for (int iFactorial = (power-iKoef + 1); iFactorial <= power; iFactorial++) {
              factorialKoefToPower = factorialKoefToPower * iFactorial;
            }

            int factorialKoef = 1;
            for (int iFactorial = 1; iFactorial <= iKoef; iFactorial++) {
              factorialKoef = factorialKoef * iFactorial;
            }
            if (iKoef == 0){
              factorialKoef = 1;
            }

            int binomialKoef = factorialKoefToPower/factorialKoef;

            /* Komplex Factor */
            if ( iKoef % 4 == 0 ) {
                uPow = uPow + binomialKoef * pow(u,power-iKoef) * pow(v,iKoef);
            }
            else if ( iKoef % 4 == 1 ) {
                vPow = vPow + binomialKoef * pow(u,power-iKoef) * pow(v,iKoef);
            }
            else if ( iKoef % 4 == 2 ) {
                uPow = uPow - binomialKoef * pow(u,power-iKoef) * pow(v,iKoef);
            }
            else  {
                vPow = vPow - binomialKoef * pow(u,power-iKoef) * pow(v,iKoef);
            }

        };

        GetBinomialSum(complexNumTest, power);

        uPow = complexNumTest[0];
        vPow = complexNumTest[1];

        /* f_n+1 */
        uPow = uPow + x;
        vPow = vPow + y;

        /* For absolute Value */
        u2 = uPow*uPow;
        v2 = vPow*vPow;

        /* Load next Iter */
        u = uPow;
        v = vPow;
        complexNumTest[0] = u;
        complexNumTest[1] = v;
        uPow = 0;
        vPow = 0;

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
