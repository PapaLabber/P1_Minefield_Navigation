#include <stdio.h>
#include <stdlib.h>
#include "../general-library.h"


node* list_mines(int map_rows, int map_columns, node **matrix, int *mine_arr_size) {
    node *mine_array = malloc(sizeof(node));
    *mine_arr_size = 0;

    for (int row = 0; row < map_rows; row++) {
        for (int column = 0; column < map_columns; column++) {
            if (matrix[row][column].mine_type != no_mine) {
                mine_array[*mine_arr_size] = matrix[row][column];
                mine_arr_size++;
                realloc(mine_array, *mine_arr_size * sizeof(node));
            }
        }
    }

    printf("DEBUG:\n");
    for (int i = 0; i < *mine_arr_size; i++) {
        printf("(%d,%d) ", mine_array[i].row, mine_array[i].col);
    }
    printf("\n");

    return mine_array;
}

void add_danger_zone(int map_rows, int map_columns, node **matrix, node *list_of_mines, int *mine_arr_size) {
    for (int i = 0; i < *mine_arr_size; i++) {
        int blast_radius = 0;
        switch (list_of_mines[i].mine_type) {
            case no_mine:
                blast_radius = 0;
                break;
            case MRUD:
                blast_radius = 1;
                break;
            case PMA2:
                blast_radius = 2;
                break;
            case PMA3:
                blast_radius = 3;
                break;
            case PROM1:
                blast_radius = 4;
                break;
            default:
                break;
        }

        for (int row = list_of_mines[i].row - blast_radius; row <= list_of_mines[i].row + blast_radius * 2; row++) {
            for (int col = list_of_mines[i].col - blast_radius; col <= list_of_mines[i].col + blast_radius * 2; col++) {
                // Check if within bounds and within Manhattan distance
                if (row >= 0 && row < map_rows && col >= 0 && col < map_columns) {
                    int distance = abs(row - list_of_mines[i].row) + abs(col - list_of_mines[i].col);
                    if (distance <= blast_radius) {
                        matrix[row][col].in_blast_zone = 1;
                    }
                }
            }
        }
    }
}

node **process_map(node **matrix, int map_rows, int map_columns) {
    int mine_arr_size; // TSP gruppen skal bruge dette

    printf("DEBUG: Initial matrix:\n");
    for (int rows = 0; rows < map_rows; rows++) {
        for (int columns = 0; columns < map_columns; columns++) {
            printf("(%d,%d,%d) ", matrix[rows][columns].mine_type, matrix[rows][columns].terrain,
                   matrix[rows][columns].obstacle_type);
        }
        printf("\n");
    }

    node* list_of_mines = list_mines(map_rows, map_columns, matrix, &mine_arr_size);

    // Add blast radius for all mines
    add_danger_zone(map_rows, map_columns, matrix, list_of_mines, &mine_arr_size);

    // Print the modified matrix
    printf("\nMatrix after adding blast radius:\n");
    for (int i = 0; i < map_rows; i++) {
        for (int j = 0; j < map_columns; j++) {
            printf("(%d,%d,%d) ", matrix[i][j].mine_type, matrix[i][j].terrain, matrix[i][j].obstacle_type);
        }
        printf("\n");
    }

    free(list_of_mines); // Skal nok slettes

    return 0;
}
