#include "function-library.h"
#include <stdlib.h>


int main(void) {

    int rows, columns, num_cells;

    cell* read_map_array = read_map_from_file("map.txt", &rows, &columns, &num_cells);

    cell **matrix = parse_map(rows, columns, read_map_array, num_cells);



    //This is needed at somepoint
    for (int i = 0; i < rows; i++) {
        free(matrix[i]);
    }
    free(matrix);
    return 0;
}
