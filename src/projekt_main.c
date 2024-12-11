#include "general-library.h"
#include "../src/algorithm/a_star_library.h"
#include <stdlib.h>


int main(void) {

    int row, col, num_cells;

    node* read_map_array = read_map_from_file("map.txt", &row, &col, &num_cells);

    node **matrix = parse_map(row, col, read_map_array, num_cells);

    a_star_test_eju();

    //This is needed at somepoint
    for (int i = 0; i < row; i++) {
        free(matrix[i]);
    }
    free(matrix);
    return 0;
}