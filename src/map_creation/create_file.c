#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "../function-library.h"


void create_file() {
    // Seed random number generator
    srand((unsigned int)time(NULL));

    // File pointer
    FILE *file = fopen("map.txt", "w");
    if (!file) {
        perror("Failed to open file");
        exit(EXIT_FAILURE);
    }
    DEBUG_MSG("Debug - map_creation: map opened \n");

    // Random number of data points (e.g., between 10 and 100)
    int num_data_points = rand() % 51 + 10; // 10 to 100
    DEBUG_MSG("Debug - map_creation: num_data_points = %d \n", num_data_points);

    // Initialize the first value for x2
    int x2 = rand() % 31 - 15; // Random value between -15 and 15

    for (int i = 0; i < num_data_points; i++) {
        // Generate the first and third integers
        int x1 = rand() % 9;                  // 0 to 8
        int x3 = (rand() % 10 < 1) ? 1 : 0;  // 10% chance of being 1

        // Generate the new value for x2, constrained by the previous value
        int new_x2;
        do {
            new_x2 = x2 + (rand() % 5 - 2); // ±2 change
        } while (new_x2 < -15 || new_x2 > 15); // Clamp to valid range [-15, 15]

        x2 = new_x2; // Update x2

        // Write to file
        fprintf(file, "%d %d %d ", x1, x2, x3);
    }
    // Close the file
    fclose(file);

    printf("Data points successfully written to data.txt.\n");
}
