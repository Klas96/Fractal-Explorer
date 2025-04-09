#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#define MAX_SIZE 40 // Adjusted for better visibility

void generateDragonCurve(char *current, int iterations) {
    char *next = (char *)malloc(strlen(current) * 2 + 1); // Allocate memory for the next generation
    strcpy(next, ""); // Initialize next as an empty string

    for (int i = 0; i < iterations; i++) {
        for (int j = 0; j < strlen(current); j++) {
            if (current[j] == 'X') {
                strcat(next, "XRYF"); // Replace X with XRYF
            } else if (current[j] == 'Y') {
                strcat(next, "LFXL"); // Replace Y with LFXL
            } else {
                strncat(next, &current[j], 1); // Copy the character as is
            }
        }
        free(current); // Free the old string
        current = next; // Move to the next generation
        next = (char *)malloc(strlen(current) * 2 + 1); // Allocate memory for the next generation
        strcpy(next, ""); // Initialize next as an empty string
    }

    free(next); // Free the last allocated memory
    printf("Dragon Curve Instructions: %s\n", current); // Print the final instructions
    free(current); // Free the final string
}

void drawDragonCurve(char *instructions) {
    char grid[MAX_SIZE][MAX_SIZE];
    memset(grid, ' ', sizeof(grid)); // Initialize grid with spaces

    int x = MAX_SIZE / 2; // Start in the middle of the grid
    int y = MAX_SIZE / 2;
    int angle = 0; // 0 degrees is to the right

    // Directions: right, up, left, down
    int dx[] = {1, 0, -1, 0};
    int dy[] = {0, -1, 0, 1};

    for (int i = 0; instructions[i] != '\0'; i++) {
        char command = instructions[i];
        if (command == 'F') {
            // Move forward in the current direction
            int newX = x + dx[angle];
            int newY = y + dy[angle];
            if (newX >= 0 && newX < MAX_SIZE && newY >= 0 && newY < MAX_SIZE) {
                grid[newY][newX] = '*'; // Mark the position
                x = newX; // Update current position
                y = newY;
            }
        } else if (command == 'L') {
            angle = (angle + 1) % 4; // Turn left
        } else if (command == 'R') {
            angle = (angle + 3) % 4; // Turn right
        }
    }

    // Print the grid
    for (int i = 0; i < MAX_SIZE; i++) {
        for (int j = 0; j < MAX_SIZE; j++) {
            putchar(grid[i][j]);
        }
        putchar('\n');
    }
}

int main() {
    char *initial = (char *)malloc(3); // Allocate 3 bytes for "FX" + null terminator
    strcpy(initial, "FX"); // Start with "FX"

    int iterations = 10; // Number of iterations
    generateDragonCurve(initial, iterations); // Generate the Dragon Curve

    // Draw the Dragon Curve based on the instructions
    drawDragonCurve(initial);

    free(initial); // Free the initial string
    return 0;
}
