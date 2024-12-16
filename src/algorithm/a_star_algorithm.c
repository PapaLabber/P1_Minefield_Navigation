#include "../general-library.h"
#include "../algorithm/a_star_library.h"
#include <stdlib.h>
#include <stdio.h>
#include <math.h>

// TEMPORARY DEFINITIONS
#define GRID_ROW 9
#define GRID_COL 9


// cost of moving around in a grid, and neighbor offsets.
const int col_offsets[] = {0, 0, 1, -1, -1, 1, -1, 1};
const int row_offsets[] = {-1, 1, 0, 0, -1, -1, 1, 1};
const double move_costs[] = {1, 1, 1, 1, sqrt(2), sqrt(2), sqrt(2), sqrt(2)};


int is_out_of_bounds(int derived_col, int derived_row, int map_size_col, int map_size_row) {
    return derived_col < 0 || derived_col >= map_size_col || derived_row < 0 || derived_row >= map_size_row;
}

double get_heuristic_euclidian(node *current_node, node *destination) {
    return sqrt(pow(current_node->row - destination->row, 2) + pow(current_node->col - destination->col, 2));
}

double get_total_g_cost(double target_g_cost, node *previous_node) {
    if (previous_node == NULL)
        return 0;

    return target_g_cost + get_total_g_cost(previous_node->g_cost, previous_node->parent);
}

//___________________________________________________
void a_star_algorithm(node **input_map, int map_size_col, int map_size_row, node *start_node, node *dest_node) {
    start_node->f_cost = get_heuristic_euclidian(start_node, dest_node);

    // Initialization of heap
    heap *priority_queue = init_heap(map_size_col * map_size_row);

    // Initialization of hash table.
    hash_node *closed_list = init_hash_table(map_size_col, map_size_row);

    node *current_node = start_node;
    current_node->parent = NULL;

    while (current_node != dest_node) {
        // check neighbors
        for (int k = 0; k < 8; k++) {
            int derived_col = current_node->col + col_offsets[k];
            int derived_row = current_node->row + row_offsets[k];

            if (is_out_of_bounds(derived_col, derived_row, map_size_col, map_size_row))
                continue;

            node *neighbor_node = &input_map[derived_row][derived_col];
            if (is_node_in_closed_set(closed_list, neighbor_node, map_size_col))
                continue;

            DEBUG_MSG("DEBUG(a_star_algorithm): Neighbor(%d,%d) with obstacle_type(%d)\n", neighbor_node->row, neighbor_node->col,
                   neighbor_node->obstacle_type);

            if (neighbor_node->obstacle_type == 0) {
                // Calculate neighbor costs
                double temp_h_cost = get_heuristic_euclidian(neighbor_node, dest_node);
                double temp_g_cost = move_costs[k] + neighbor_node->in_blast_zone;
                double temp_total_g_cost = get_total_g_cost(temp_g_cost, current_node);
                double temp_f_cost = temp_h_cost + temp_total_g_cost;
                if (temp_f_cost <= neighbor_node->f_cost) {
                    neighbor_node->h_cost = temp_h_cost;
                    neighbor_node->g_cost = temp_g_cost;
                    neighbor_node->f_cost = temp_f_cost;
                    neighbor_node->parent = current_node;
                }

                DEBUG_MSG("DEBUG(a_star_algorithm): ready to insert new node\n");

                insert_heap_node(priority_queue, neighbor_node);
                DEBUG_MSG("DEBUG(a_star_algorithm): New node added\n\n");
            }
        }
        node *cheapest_neighbor = get_and_remove_lowest_heap_node(priority_queue);
        DEBUG_MSG("DEBUG(a_star_algorithm): Cheapest neighbor is (%d,%d)\n", cheapest_neighbor->row, cheapest_neighbor->col);

        insert_hash_table(closed_list, map_size_col, current_node);

        current_node = cheapest_neighbor;
        DEBUG_MSG("DEBUG(a_star_algorithm): new current node = (%d,%d)\n\n", current_node->row, current_node->col);
    }
    DEBUG_MSG("DEBUG(a_star_algorithm): Destination reached. Current_node (%d,%d)\n", current_node->row, current_node->col);

    free(priority_queue);
    free(closed_list);
}

//___________________________________________________

void a_star_test_eju(void) {
    int map_size_col = 9; // representing our future variable size (not constant...)
    int map_size_row = 9; // representing our future variable size (not constant...)

    int grid[GRID_ROW][GRID_COL] = {
        {1, 0, 1, 1, 1, 1, 0, 1, 1},
        {1, 1, 1, 0, 1, 1, 1, 0, 1},
        {1, 1, 1, 0, 1, 1, 0, 1, 0},
        {0, 0, 1, 0, 1, 0, 0, 0, 0},
        {1, 1, 1, 0, 1, 1, 1, 0, 1},
        {1, 1, 1, 0, 1, 1, 0, 1, 0},
        {1, 1, 1, 1, 1, 1, 1, 1, 1},
        {1, 0, 0, 0, 0, 1, 0, 0, 1},
        {1, 1, 1, 1, 1, 1, 1, 0, 1}
    };

    // Allocate
    node **grid_with_obstacles = (node **) malloc(map_size_row * sizeof(node *));
    if (grid_with_obstacles == NULL) {
        printf("Allocation error cols\n");
        exit(EXIT_FAILURE);
    }
    for (int row = 0; row < map_size_row; row++) {
        grid_with_obstacles[row] = (node *) malloc(map_size_col * sizeof(node));
        if (grid_with_obstacles[row] == NULL) {
            printf("Allocation error rows\n");
            free(grid_with_obstacles);
            exit(EXIT_FAILURE);
        }
    }
    // Fill
    for (int row = 0; row < map_size_row; row++) {
        for (int col = 0; col < map_size_col; col++) {
            grid_with_obstacles[row][col].row = row;
            grid_with_obstacles[row][col].col = col;
            grid_with_obstacles[row][col].obstacle_type = !grid[row][col];
        }
    }
    // Print
    printf("grid_with_obstacles:\n");
    for (int row = 0; row < map_size_row; row++) {
        for (int col = 0; col < map_size_col; col++) {
            printf("%d ", grid_with_obstacles[row][col].obstacle_type);
        }
        printf("\n");
    }

    node *start_node = &grid_with_obstacles[0][0];
    node *dest_node = &grid_with_obstacles[8][8];

    a_star_algorithm(grid_with_obstacles, map_size_col, map_size_row, start_node, dest_node);

    free(grid_with_obstacles);
}
