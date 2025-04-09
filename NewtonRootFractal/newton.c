#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<pthread.h>
#include<complex.h>
#include<math.h>

//Global Variables

int d = 5; // Define d with a specific value
//TODO fix this
float complex* Roots; // Change to a pointer for dynamic allocation

// Initialize file pointers inside a function, e.g., main()
FILE * fproots;
FILE * fpIter;

void calculate_roots() {
    for (int k = 0; k < d; k++) {
        Roots[k] = cexp(2 * M_PI * I * k / d); // Calculate the k-th root of unity
    }
}

void initialize_files() {
    fproots = fopen("Roots_tQ_lQ_dQ.ppm", "wb+");
    if (fproots == NULL) {
        fprintf(stderr, "Error opening file for writing: Roots_tQ_lQ_dQ.ppm\n");
        return;
    }
    fpIter = fopen("Iter_tQ_lQ_dQ.ppm", "wb+");
}

typedef struct Newton_arg {
  float complex x;
  int d;
  int* it;
  int l;
} Newton_arg;

typedef struct Bild_arg {
  float x;
  int it;
} Bild_arg;

float complex f(float complex x, int d){
  float complex x_orginal = x;
  
  for(size_t i = 1; i<d; i++){
    //x^d
    x  *= x_orginal; 
  }
  //printf("f(x) %f+%fi  ",creal(x-1), cimag(x-1));
  return  x-1;
}

float complex df(float complex x, int d){
  float complex x_orginal = x;
  for(size_t i = 1; i<(d-1); i++){
    //x^(d-1)
    x *= x_orginal;
  }
  //printf("df(x) %f+%fi  ",creal(x*d),cimag(x*d));
  return d*x;
}

// Ensure the newton function is declared before use
void newton(void *arg); // Declare the function prototype

// Ensure the newton function is defined
void newton(void *arg) {
    // Ensure it_new is declared correctly
    int it_new; // Declare it_new as an integer
    it_new = 100000000; // Assign the value correctly

    //Slutar när steglängd mindre änn tol (ändra till ratio av f)
    struct Newton_arg* args = (struct Newton_arg*)arg;
    float complex x_new = args->x;
    int d_new = args->d;
    int* it_new_ptr = args->it;
    int l_new = args->l;
    //free(arg);
    
    float tol = 0.01;
    
    //Steg
    float complex p = 1 + 1*I;
    
    //Iteration
    *it_new_ptr = 0;
    int n = 0;
    
    while(cabsf(p) > tol){
      p = f(x_new,d_new)/df(x_new,d_new);
      x_new = x_new - p;//kan det hända något här???
      *it_new_ptr += 1;
      
      n = isnormal(creal(x_new));
      
      if(n == 0 ||cabsf(x_new)<0.01){
        x_new = 0+0I;
        *it_new_ptr = it_new;
        break;
      }
      //printf("x %f+%fi  p %f+%fi  it %i\n",creal(x),cimag(x),creal(p),cimag(p),it);
    }
    //printf("x %f+%fi  p %f+%fi  it %i\n",creal(x),cimag(x),creal(p),cimag(p),it);
    //return it;
}

// Example of file operations
void someFunction() {
    // Ensure fproots and Iter are properly declared and opened before using them
    if (fproots != NULL) {
        fprintf(fproots, "\n"); // Correct usage of fprintf
        fclose(fproots); // Close the file after writing
    }

    if (fpIter != NULL) {
        fprintf(fpIter, "\n"); // Correct usage of fprintf
        fclose(fpIter); // Close the file after writing
    }
}

// Example of generating a Newton fractal
void generateFractalIter(FILE *fproots, int width, int height) {
    fprintf(fproots, "P3\n%d %d\n255\n", width, height); // PPM header

    int max_iterations = 100; // Define the maximum number of iterations
    double x_min = -2.0, x_max = 2.0; // Define the range for the real part
    double y_min = -2.0, y_max = 2.0; // Define the range for the imaginary part
    int d = 5; // Define the degree of the polynomial

    for (int y = 0; y < height; y++) {
        for (int x = 0; x < width; x++) {
            // Map pixel coordinates to the complex plane
            double real = x_min + (x / (double)width) * (x_max - x_min);
            double imag = y_min + (y / (double)height) * (y_max - y_min);
            double complex z = real + imag * I; // Start with the complex number

            int iterations = 0;

            // Perform Newton's method iterations
            while (iterations < max_iterations) {
                double complex f_z = f(z, d); // Pass both arguments
                double complex df_z = df(z, d); // Pass both arguments

                if (cabs(df_z) == 0) break; // Avoid division by zero

                // Update z using Newton's method
                z = z - f_z / df_z;

                // Check for convergence
                if (cabs(f_z) < 1e-6) {
                    break; // Converged
                }
                iterations++;
            }

            // Determine color based on iterations
            int r = (iterations == max_iterations) ? 0 : (iterations * 255 / max_iterations);
            int g = (iterations == max_iterations) ? 0 : (iterations * 255 / max_iterations);
            int b = (iterations == max_iterations) ? 0 : (iterations * 255 / max_iterations);
            fprintf(fproots, "%d %d %d ", r, g, b); // Write pixel color
        }
        fprintf(fproots, "\n"); // New line for each row
    }
}

int find_root_index(double complex z, float complex *Roots, int d) {
    // Example implementation: find the closest root
    int closest_index = 0;
    double min_distance = cabs(z - Roots[0]);

    for (int i = 1; i < d; i++) {
        double distance = cabs(z - Roots[i]);
        if (distance < min_distance) {
            min_distance = distance;
            closest_index = i;
        }
    }
    return closest_index;
}

void generateFractalRoots(FILE *fproots, int width, int height) {
    fprintf(fproots, "P3\n%d %d\n255\n", width, height); // PPM header

    int max_iterations = 100; // Define the maximum number of iterations
    double x_min = -2.0, x_max = 2.0; // Define the range for the real part
    double y_min = -2.0, y_max = 2.0; // Define the range for the imaginary part
    int d = 5; // Define the degree of the polynomial

    for (int y = 0; y < height; y++) {
        for (int x = 0; x < width; x++) {
            // Map pixel coordinates to the complex plane
            double real = x_min + (x / (double)width) * (x_max - x_min);
            double imag = y_min + (y / (double)height) * (y_max - y_min);
            double complex z = real + imag * I; // Start with the complex number

            int iterations = 0;

            // Perform Newton's method iterations
            while (iterations < max_iterations) {
                double complex f_z = f(z, d); // Pass both arguments
                double complex df_z = df(z, d); // Pass both arguments

                if (cabs(df_z) == 0) break; // Avoid division by zero

                // Update z using Newton's method
                z = z - f_z / df_z;

                // Check for convergence
                if (cabs(f_z) < 1e-6) {
                    break; // Converged
                }
                iterations++;
            }

            // Determine color based on iterations and root convergence
            int r, g, b;
            if (iterations == max_iterations) {
                r = 0; g = 0; b = 0; // No convergence
            } else {
                // Color determined by the root_index
                int root_index = find_root_index(z, Roots, d);
                r = (root_index % 3 == 0) ? 255 : 0; // Red
                g = (root_index % 3 == 1) ? 255 : 0; // Green
                b = (root_index % 3 == 2) ? 255 : 0; // Blue
            }
            fprintf(fproots, "%d %d %d ", r, g, b); // Write pixel color
        }
        fprintf(fproots, "\n"); // New line for each row
    }
}

void initialize_roots() {
    Roots = malloc(d * sizeof(float complex)); // Allocate memory for Roots
    if (Roots == NULL) {
        fprintf(stderr, "Memory allocation failed for Roots\n");
        exit(EXIT_FAILURE); // Exit if allocation fails
    }
}

// Define the main function
int main() {
    // Initialize necessary variables
    initialize_files(); // Call the function to initialize file pointers
    initialize_roots(); // Call the function to initialize Roots
    calculate_roots();

    // Define the width and height for the fractal image
    int width = 800; // Example width
    int height = 800; // Example height

    // Generate the fractal and write it to the file
    generateFractalIter(fpIter, width, height);
    generateFractalRoots(fproots,width,height);

    // Close the files after writing
    if (fproots != NULL) {
        fclose(fproots);
    }
    if (fpIter != NULL) {
        fclose(fpIter);
    }

    free(Roots); // Free the allocated memory before exiting
    return 0; // Return success
}
