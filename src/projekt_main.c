#include "general-library.h"
#include "../src/algorithm/a_star_library.h"
#include <stdlib.h>
#include "../src/map_processing/process_library.h"

int main(void) {

    int row, col, num_nodes;

    node* read_map_array = read_map_from_file("map.txt", &row, &col, &num_nodes);

    node** matrix = parse_map(row, col, read_map_array, num_nodes);

    process_map(row, col, matrix);

    node *start_node = &matrix[9][9];
    node *dest_node = &matrix[0][0];

    a_star_algorithm(matrix, col, row, start_node, dest_node);

    trace_path(matrix, dest_node, row, col);
    // a_star_test_eju();

    //This is needed at somepoint
    for (int i = 0; i < row; i++) {
        free(matrix[i]);
    }
    free(matrix);
    return 0;
}