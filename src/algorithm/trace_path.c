#include <stdio.h>
#include "../function-library.h"

void trace_path(node node_details[GRID_ROW][GRID_COL], node destination) {
    int row = destination.row;
    int col = destination.col;

    // Stack to store the path temporarily for printing (no need to store full path)
    node temp_path[GRID_ROW * GRID_COL];
    int temp_path_size = 0;

    // Backtrack from destination to start
    while (!(node_details[row][col].parent.row == row && node_details[row][col].parent.col == col)) {
        // Store current position in temp_path
        temp_path[temp_path_size].row = row;
        temp_path[temp_path_size].col = col;
        temp_path_size++;

        // Move to the parent cell (this is the backtracking step)
        int temp_row = node_details[row][col].parent.row;  // Get parent row
        int temp_col = node_details[row][col].parent.col;  // Get parent column
        row = temp_row;  // Update current row to parent's row
        col = temp_col;  // Update current col to parent's column
    }

    // Add the starting cell to the temporary path
    temp_path[temp_path_size].row = row;
    temp_path[temp_path_size].col = col;
    temp_path_size++;

    // Print the reconstructed path from destination to start (in reverse order)
    printf("\nThe path is: ");
    for (int i = temp_path_size - 1; i >= 0; i--) {
        printf("-> (%d, %d) ", temp_path[i].row, temp_path[i].col);
    }
    printf("\n");
}
