#include <stdio.h>
#include <stdlib.h>
#include "../general-library.h"


node *list_mines(int map_rows, int map_cols, node **matrix, int *mine_arr_index) {
    *mine_arr_index = 0;
    node *mine_array = malloc(((*mine_arr_index) + 1) * sizeof(node));

    for (int row = 0; row < map_rows; row++) {
        for (int col = 0; col < map_cols; col++) {
            if (matrix[row][col].mine_type != no_mine) {
                mine_array[(*mine_arr_index)] = matrix[row][col];
                (*mine_arr_index)++;
                mine_array = (node*)realloc(mine_array, ((*mine_arr_index) + 1) * sizeof(node));
                if(mine_array == NULL) {
                    printf("Reallocation failed\n");
                    exit(EXIT_FAILURE);
                }
            }
        }
    }

    DEBUG_MSG("DEBUG(list_mines):\n");
    for (int i = 0; i < *mine_arr_index; i++) {
        DEBUG_MSG("(%d,%d) ", mine_array[i].row, mine_array[i].col);
    }
    DEBUG_MSG("\n");

    return mine_array;
}

void add_danger_zone(int map_rows, int map_cols, node **matrix, node *list_of_mines, int *mine_arr_index) {
    for (int i = 0; i < *mine_arr_index; i++) {
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

        for (int row = list_of_mines[i].row - blast_radius; row <= list_of_mines[i].row + blast_radius; row++) {
            for (int col = list_of_mines[i].col - blast_radius; col <= list_of_mines[i].col + blast_radius; col++) {
                // Check if within bounds and within Manhattan distance
                if (row >= 0 && row < map_rows && col >= 0 && col < map_cols) {
                    int distance = abs(row - list_of_mines[i].row) + abs(col - list_of_mines[i].col);
                    if (distance <= blast_radius) {
                        matrix[row][col].in_blast_zone = 1;
                    }
                }
            }
        }
    }
}

void prepare_map(node **input_map, int map_cols, int map_rows) {
    for (int row = 0; row < map_rows; row++) {
        for (int col = 0; col < map_cols; col++) {
            input_map[row][col].f_cost = INT_MAX;
        }
    }
}

node* process_map(int map_rows, int map_cols, node **matrix, int* mine_arr_index) {
    // set all f_cost to INT_MAX
    prepare_map(matrix, map_cols, map_rows);

    DEBUG_MSG("DEBUG(process_map): Initial matrix:\n");
    for (int rows = 0; rows < map_rows; rows++) {
        for (int cols = 0; cols < map_cols; cols++) {
            DEBUG_MSG("(%d,%d,%d) ", matrix[rows][cols].mine_type, matrix[rows][cols].terrain,
                   matrix[rows][cols].obstacle_type);
        }
        DEBUG_MSG("\n");
    }

    node *list_of_mines = list_mines(map_rows, map_cols, matrix, mine_arr_index);

    // Add blast radius for all mines
    add_danger_zone(map_rows, map_cols, matrix, list_of_mines, mine_arr_index);


    return list_of_mines;
}
