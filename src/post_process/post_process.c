#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// Enums for mine and obstacle types
typedef enum {
    no_mine = 0,  // No mine
    MRUD = 1,     // Type 1 mine
    PMA2 = 2,     // Type 2 mine
    PMA3 = 3,     // Type 3 mine
    PROM1 = 4,    // Type 4 mine
    blast_radius = 5 // Blast radius marker
} is_mine;

typedef enum {
    no_obstacle = 0,
    tree = 1,
    Large_stone = 2,
    Water = 3
} is_obstacle;

// Struct representing each cell
typedef struct {
    is_mine mine;
    is_obstacle obstacle;
    int height;
} cell_værdi;

typedef struct {
    int x_rows;
    int y_columns;
}mine_cords;

void array_for_mines(int *rows, int *columns, cell_værdi** matrix) {
    int k = 0;

    printf("We are in the function!\n");
    mine_cords mine_array[20];
    for (int i = 0; i < *rows; i++) {
        for (int j = 0; j < *columns; j++) {
            if (matrix[i][j].mine != no_mine) {
                mine_array[k].x_rows = i;
                mine_array[k].y_columns = j;
                k++;
            }
        }
    }
    //
    for (int i = 0; i < k; i++) {  // Print only up to `k`
        printf("(%d,%d) ", mine_array[i].x_rows, mine_array[i].y_columns);
    }
    printf("\n");
}

// Funktion til at tilføje blastradius
void add_danger_zone(int rows, int columns, cell_værdi** matrix) {
    //koordinator til lille blast radius
    int naboer[8][2] = {
        {0,  1}, {1,  0}, {1,  1}, {0, -1},
        {-1, 0}, {-1, -1}, {1, -1}, {-1, 1}
    };
    //koordinator til stor blast radius
    int naboer2[16][2] = {
        {-2,-2}, {-2,-1}, {-2, 0}, {-2, 1},
        {-2, 2}, {-1, 2}, {-1,-2}, {0,  2},
        {0, -2}, {1,  2}, {1, -2}, {2, -2},
        {2, -1}, {2,  0}, {2,  1}, {2,  2}
    };

// Her finder vi minerne

    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < columns; j++) {
            //Hvis cellen har en mine, kigges der på nabocellerne
            if (matrix[i][j].mine == PMA2 || matrix[i][j].mine == PMA3) {
                for (int k = 0; k < 8; k++) {
                    int mine_i = i + naboer[k][0];
                    int mine_j = j + naboer[k][1];
                    // Hvis der ikke er en mine på nabocellerne tilføjes blast radius
                    if (mine_i >= 0 && mine_i < rows && mine_j >= 0 && mine_j < columns &&
                        matrix[mine_i][mine_j].mine == no_mine) {
                        matrix[mine_i][mine_j].mine = blast_radius;
                    }
                }
            }
            // Der tilføjes blast radius 2. Hvis cellen har en mine kigges der på nabocellerne via naboer2
            if(matrix[i][j].mine == PMA3) {
                for (int h = 0; h < 16; h++) {
                    int mine_i = i + naboer2[h][0];
                    int mine_j = j + naboer2[h][1];
                    //Hvis ikke der er en mine på nabocellerne tilføjes blast radius
                    if (mine_i >= 0 && mine_i < rows && mine_j >= 0 && mine_j < columns &&
                        matrix[mine_i][mine_j].mine == no_mine) {
                        matrix[mine_i][mine_j].mine = blast_radius;

                    }
                }
            }
        }
    }
}

// Function to allocate random rows and columns
void random_cr(int* rows, int* columns) {
    srand(time(NULL));
    *rows = 5; //rand() % 10 + 5;  // Random between 5 and 20
    *columns = 5;  //rand() % 10 + 5;  // Random between 5 and 20
}

int main(void) {
    int rows, columns;

    // Generate random dimensions for the matrix
    random_cr(&rows, &columns);

    // Allocate memory for the matrix
    cell_værdi** matrix = (cell_værdi**)malloc(rows * sizeof(cell_værdi*));
    if (matrix == NULL) {
        fprintf(stderr, "Memory allocation failed!\n");
        return EXIT_FAILURE;
    }

    for (int i = 0; i < rows; i++) {
        matrix[i] = (cell_værdi*)malloc(columns * sizeof(cell_værdi));
        if (matrix[i] == NULL) {
            fprintf(stderr, "Memory allocation failed!\n");
            return EXIT_FAILURE;
        }
    }

    // Initialize the matrix with some default values
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < columns; j++) {
            matrix[i][j].mine = (rand() % 10 == 0) ? PMA3 : no_mine;  // Randomly place PMA2 mines
            matrix[i][j].obstacle = no_obstacle;
            matrix[i][j].height = rand() % 10 + 1;  // Random height between 1 and 10
        }
    }

    // Print the initial matrix
    printf("Initial matrix:\n");
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < columns; j++) {
            printf("(%d,%d,%d) ", matrix[i][j].mine, matrix[i][j].height, matrix[i][j].obstacle);
        }
        printf("\n");
    }
    array_for_mines(&rows, &columns, matrix);
    // Add blast radius for all mines
    add_danger_zone(rows, columns, matrix);

    // Print the modified matrix
    printf("\nMatrix after adding blast radius:\n");
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < columns; j++) {
            printf("(%d,%d,%d) ", matrix[i][j].mine, matrix[i][j].height, matrix[i][j].obstacle);
        }
        printf("\n");
    }


    // Free allocated memory
    for (int i = 0; i < rows; i++) {
        free(matrix[i]);
    }
    free(matrix);

    return 0;


}

