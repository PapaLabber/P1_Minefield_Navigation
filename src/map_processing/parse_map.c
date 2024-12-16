#include "../general-library.h"
#include <stdio.h>
#include <stdlib.h>


node** parse_map(const int map_rows, const int map_cols, const node* read_map_array, const int num_nodes) {
    node** matrix = malloc(map_rows * sizeof(node*)); //allokerer plads til map_rows
    if(matrix == NULL) {
        printf("Allocation error in matrix\n");
        exit(EXIT_FAILURE);
    }
    for (int i = 0; i < map_rows; i++) {
        matrix[i] = (node* ) calloc(map_cols, sizeof(node)); //allokerer plads til map_cols
        if (matrix[i] == NULL) {
            printf("Allocation error in 2d allocation index:[%d]\n", i);
            exit(EXIT_FAILURE);
        }
    }

    //fylder matrixen med værdier fra read_map array
    int k = 0;
    for (int row = 0; row < map_rows; row++) {
        for (int col = 0; col < map_cols; col++) {
            if (k < num_nodes) {
                matrix[row][col] = read_map_array[k];
                matrix[row][col].row = row;
                matrix[row][col].col = col;
                k++;
            } else {
                printf("Warning: read_map_array is smaller than the required matrix size\n");
                break;
            }
        }
    }

    return matrix;
}

