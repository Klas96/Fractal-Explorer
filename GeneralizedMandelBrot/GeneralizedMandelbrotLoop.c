#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <stdint.h>

/* Global Variables */
/* Maximum number of iterations */
const uint16_t maxiter = 500;

int * GetColor(int k){

  int * color = malloc(3*sizeof(int));

  if (k >= maxiter) {
    /* interior */
    color[0] = 0;
    color[1] = 0;
    color[2] = 0;
  }
  else{
    /* Exterior */
    int colorNum = k % 16;

    switch(colorNum){
        case 0:
            /* brown */
            color[0] = 66;
            color[1] = 30;
            color[2] = 15;
            break;
        case 1:
            /* Dark blue */
            color[0] = 25;
            color[1] = 7;
            color[2] = 26;
            break;
        case 2:
            /* Blue */
            color[0] = 9;
            color[1] = 1;
            color[2] = 47;
            break;
        case 3:
            /* Blue */
            color[0] = 4;
            color[1] = 4;
            color[2] = 73;
            break;
        case 4:
            /* Blue */
            color[0] = 0;
            color[1] = 7;
            color[2] = 100;
            break;
        case 5:
            /* Blue */
            color[0] = 12;
            color[1] = 44;
            color[2] = 138;
            break;
        case 6:
            /* Light Blue */
            color[0] = 24;
            color[1] = 82;
            color[2] = 177;
            break;
        case 7:
            /* Light Blue */
            color[0] = 57;
            color[1] = 125;
            color[2] = 209;
            break;
        case 8:
            /* Light Blue */
            color[0] = 134;
            color[1] = 181;
            color[2] = 229;
            break;
        case 9:
            /* Light Blue */
            color[0] = 211;
            color[1] = 236;
            color[2] = 248;
            break;
        case 10:
            /* Light Red */
            color[0] = 241;
            color[1] = 233;
            color[2] = 191;
            break;
        case 11:
            /* Orange */
            color[0] = 248;
            color[1] = 201;
            color[2] = 95;
            break;
        case 12:
            /* Orange */
            color[0] = 255;
            color[1] = 170;
            color[2] = 0;
            break;
        case 13:
            /* Orange */
            color[0] = 204;
            color[1] = 128;
            color[2] = 0;
            break;
        case 14:
            /* Orange Brown */
            color[0] = 153;
            color[1] = 87;
            color[2] = 0;
            break;
        case 15:
            /* Brown */
            color[0] = 106;
            color[1] = 52;
            color[2] = 3;
            break;
    }
  }
  return color;
}

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

  /* The window in the plane. */
  const double xmin = -2;
  const double xmax = 2;
  const double ymin = -2;
  const double ymax = 2;

  /* Image size, width is given, height is computed. */
  const int xres = 2000;
  const int yres = (xres*(ymax-ymin))/(xmax-xmin);

  /* Level of Mandelbrot. */
  const int power = 6;

  /* The output file name */
  const char* filename = "Mandelbrot.ppm";

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

      color = GetColor(k);
      fprintf(fp, "%d %d %d  ",color[0],color[1],color[2]);

    }
    fprintf(fp,"\n");
  }
  fclose(fp);
  return 0;
}
