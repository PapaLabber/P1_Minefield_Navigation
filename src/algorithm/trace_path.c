#include <stdio.h>

void tracePath(Cell cellDetails[ROW][COL], Pair dest) {
    int row = dest.first;
    int col = dest.second;

    // Stack to store the path temporarily for printing (no need to store full path)
    Pair tempPath[ROW * COL];
    int tempPathSize = 0;

    // Backtrack from destination to start
    while (!(cellDetails[row][col].parent_i == row && cellDetails[row][col].parent_j == col)) {
        // Store current position in tempPath
        tempPath[tempPathSize].first = row;
        tempPath[tempPathSize].second = col;
        tempPathSize++;

        // Move to the parent cell (this is the backtracking step)
        int temp_row = cellDetails[row][col].parent_i;  // Get parent row
        int temp_col = cellDetails[row][col].parent_j;  // Get parent column
        row = temp_row;  // Update current row to parent's row
        col = temp_col;  // Update current col to parent's column
    }

    // Add the starting cell to the temporary path
    tempPath[tempPathSize].first = row;
    tempPath[tempPathSize].second = col;
    tempPathSize++;

    // Print the reconstructed path from destination to start (in reverse order)
    printf("\nThe path is: ");
    for (int i = tempPathSize - 1; i >= 0; i--) {
        printf("-> (%d, %d) ", tempPath[i].first, tempPath[i].second);
    }
    printf("\n");
}
