#include "../function-library.h"
#include <stdio.h>
#include <stdlib.h>


cell** parse_map(const int rows, const int columns, const cell* read_map_array, const int num_cells) {
    //allokere plads til matrixen
    cell **matrix = (cell **) malloc(rows * sizeof(cell *)); //allokere plads til rows
     if(matrix == NULL) {
        printf("Allocation error in matrix\n");
        exit(EXIT_FAILURE);
    }
    for (int i = 0; i < rows; i++) {
        matrix[i] = (cell *) malloc(columns * sizeof(cell)); //allokere plads til coloumns
        if (matrix[i] == NULL) {
            printf("Allocation error in 2d allocation index:[%d]\n", i);
            exit(EXIT_FAILURE);
        }
    }

    //fylder matrixen med værdier fra read_map array
    int k = 0;
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < columns; j++) {
            if (k < num_cells) {
                matrix[i][j] = read_map_array[k];
                k++;
            } else {
                printf("Warning: read_map_array is smaller than the required matrix size\n");
                break;
            }
        }
    }

    //print for sjov skyld
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < columns; j++) {
            printf("(%4d, %4d, %4d)", matrix[i][j].obstacle, matrix[i][j].terrain, matrix[i][j].mine);
        }
        printf("\n");
    }

    return matrix;
}

