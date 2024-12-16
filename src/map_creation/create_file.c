#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "../general-library.h"


void create_file() {
    // Seed random number generator
    srand((unsigned int)time(NULL));

    // Prompt for dimensions of the map
    int rows, columns;
    printf("What dimensions would you like the map to be?: \n");
    scanf("%d %d", &rows, &columns);

    // File pointer
    FILE *file = fopen("map.txt", "w");
    if (!file) {
        perror("Failed to open file");
        exit(EXIT_FAILURE);
    }
    DEBUG_MSG("Debug - map_creation: map opened \n");

    // Number of data points dependent on dimensions of map
    int num_data_points = rows * columns;
    DEBUG_MSG("Debug - map_creation: num_data_points = %d \n", num_data_points);

    // Printing of dimensions as first 2 numbers in map.txt
    fprintf(file, "%d %d ", rows, columns);
    DEBUG_MSG("Debug - map_creation: dimensions successfully written to map file\n");

    // Initialize the first value for x2
    int x2 = rand() % 31 - 15; // Random value between -15 and 15

    for (int i = 0; i < num_data_points; i++) {
        // Generate the first and third integers
        int x3 = (rand() % 10 < 1) ? 1 : 0;  // 10% chance of being 1
        int x1 = (rand() % 5 == 0 && (x3 == 0)) ? (rand() % 8 + 1) : 0;   // 0 to 8



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
    DEBUG_MSG("Debug - map_creation: File closed successfully\n");

    printf("Data points successfully written to data.txt.\n");
}
