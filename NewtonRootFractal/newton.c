#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<pthread.h>
#include<complex.h>
#include<math.h>

//Global Variables

int d = 10; // Define d with a specific value
float complex Roots[10]; // Use a constant size for the array

// Initialize file pointers inside a function, e.g., main()
FILE * fproots;
FILE * Iter;

void initialize_files() {
    fproots = fopen("Roots_tQ_lQ_dQ.ppm", "wb+");
    if (fproots == NULL) {
        fprintf(stderr, "Error opening file for writing: Roots_tQ_lQ_dQ.ppm\n");
        return;
    }
    Iter = fopen("Iter_tQ_lQ_dQ.ppm", "wb+");
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

// Declare Color as an array of integers
int Color[3]; // Define Color as an array of integers

void skapaBilder(void* arg) {
    struct Bild_arg* args = (struct Bild_arg*)arg; // Cast arg to the correct type
    size_t k; // Declare k appropriately
    size_t l; // Ensure l is declared and initialized properly
    float **xp; // Ensure xp is declared and initialized properly

    // Ensure mutex is defined
    pthread_mutex_t mutex; // Declare a mutex variable

    pthread_mutex_lock(&mutex); // Lock the mutex correctly

    for (size_t j = 0; j < l; j++) {
        args->x = xp[j][k]; // Use args instead of args
        // ... existing code ...
    }

    // Correct the assignment to Color
    Color[0] = args->it; // Assign the value directly, not the address
    Color[1] = args->it; // Assign the value directly, not the address
    Color[2] = args->it; // Assign the value directly, not the address

    // No return statement needed for a void function
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

    if (Iter != NULL) {
        fprintf(Iter, "\n"); // Correct usage of fprintf
        fclose(Iter); // Close the file after writing
    }
}

// Example of generating a Newton fractal
void generateFractal(FILE *fproots, int width, int height) {
    fprintf(fproots, "P3\n%d %d\n255\n", width, height); // PPM header

    int max_iterations = 100; // Define the maximum number of iterations
    double x_min = -2.0, x_max = 2.0; // Define the range for the real part
    double y_min = -2.0, y_max = 2.0; // Define the range for the imaginary part
    int d = 3; // Define the degree of the polynomial (adjust as needed)

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

                // Check for convergence (you can define a threshold)
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

// Define the main function
int main() {
    // Initialize necessary variables
    initialize_files(); // Call the function to initialize file pointers

    // Define the width and height for the fractal image
    int width = 800; // Example width
    int height = 800; // Example height

    // Generate the fractal and write it to the file
    generateFractal(fproots, width, height);

    // Close the files after writing
    if (fproots != NULL) {
        fclose(fproots);
    }
    if (Iter != NULL) {
        fclose(Iter);
    }

    return 0; // Return success
}
