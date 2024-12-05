#include <stdio.h>
#include <string.h>
#include <math.h>
#include <stdlib.h>
#include <stdbool.h>
#include <float.h>
#include "../function-library.h"

// is node within grid boundaries? (compares node coords with grid dimensions)
bool is_valid(node current_node) {
    return (current_node.row >= 0) && (current_node.row < GRID_ROW) && (current_node.col >= 0) && (current_node.col < GRID_COL);
}

// is node unblocked? (checks node value)
bool is_unblocked(int grid[GRID_ROW][GRID_COL], node current_node) {
    return (grid[current_node.row][current_node.col] == 1);
}

// has destination been reached? (compare coordinates)
bool is_destination(node is_dest_node, node destination) {
    return (is_dest_node.row == destination.row && is_dest_node.col == destination.col);
}

// heuristic function estimating distance to destination using Manhattan distance
int calculate_heuristic(node current_node, node destination) {
    return abs(current_node.row - destination.row) + abs(current_node.col - destination.col);
}

// the actual A* algorithm (mine A to mine B traversal)
void a_star_search(int grid[GRID_ROW][GRID_COL], node start, node destination) { // Pair -> node
    // validating start and destination nodes
    // are both start and destination valid?
    if (!is_valid(start) == 1) {
        printf("ERROR: Start node is invalid.");
        exit(EXIT_FAILURE);
    } else if (!is_valid(destination)) {
        printf("ERROR: Destination node is invalid.");
        exit(EXIT_FAILURE);
    }

    // are both start and destination unblocked?
    if (!is_unblocked(grid, start)) {
        printf("ERROR: Start node is blocked.");
        exit(EXIT_FAILURE);
    } else if (!is_unblocked(grid, destination)) {
        printf("ERROR: Destination node is blocked.");
        exit(EXIT_FAILURE);
    }

    // are start and destination different?
    if (is_destination(start, destination)) {
        printf("ERROR: The start and destination are the same.");
        exit(EXIT_FAILURE);
    }

    // closed list, all elements initially unvisited (closed)
    bool closed_list[GRID_ROW][GRID_COL];
    memset(closed_list, false, sizeof(closed_list));

    // Initialization of grid and setting cost to max. Parents initialized
    node node_details[GRID_ROW][GRID_COL];
    for (int i = 0; i < GRID_ROW; i++) {
        for (int j = 0; j < GRID_COL; j++) {
            node_details[i][j].f_cost = INT_MAX; // initial cost infinite, not looked at yet
            node_details[i][j].g_cost = INT_MAX;
            node_details[i][j].h_cost = INT_MAX;
            node_details[i][j].parent.col = -1; // no parent assigned yet
            node_details[i][j].parent.row = -1;
        }
    }

    // initialize start node
    int i = start.row, j = start.col;
    node_details[i][j].f_cost = 0.0;
    node_details[i][j].g_cost = 0.0;
    node_details[i][j].h_cost = 0.0;
    node_details[i][j].parent.col = i; // no parent assigned yet
    node_details[i][j].parent.row = j;

    min_heap open_list;
    open_list.arr = (node *)malloc(sizeof(node) * GRID_ROW * GRID_COL);
    open_list.size = 0;
    open_list.capacity = GRID_ROW * GRID_COL;

    insert_min_heap(&open_list, &start);

    bool found_dest = false;

    while (open_list.size > 0) {
        node* node_cheapest = find_minimum(&open_list);

        i = node_cheapest->row;
        j = node_cheapest->col;

        closed_list[i][j] = true;

        double g_cost_new, h_cost_new, f_cost_new;

        int row_offsets[] = {-1, 1, 0, 0, -1, -1, 1, 1};
        int col_offsets[] = {0, 0, 1, -1, -1, 1, -1, 1};
        int move_costs[] = {1, 1, 1, 1, 2, 2, 2, 2};

        for (int d = 0; d < 8; d++) {
            node child;

            child.row = i + row_offsets[d];
            child.col = j + col_offsets[d];

            if (is_valid(child)) {
                if (is_destination(child, destination)) {
                    node_details[child.row][child.col].parent.row = i; // node_details -> cellDetails -> grid
                    node_details[child.row][child.col].parent.col = j;
                    printf("The destination node has been found!\n");
                    trace_path(node_details, destination);
                    found_dest = true;
                    free(open_list.arr);
                    return;
                } else if (!closed_list[child.row][child.col] && is_unblocked(grid, child)) {
                    g_cost_new = node_details[i][j].g_cost + move_costs[d];
                    h_cost_new = calculate_heuristic(child, destination);
                    f_cost_new = g_cost_new + h_cost_new;

                    if (node_details[child.row][child.col].f_cost == FLT_MAX || node_details[child.row][child.col].f_cost > f_cost_new) {
                        insert_min_heap(&open_list, &child);
                        node_details[child.row][child.col].f_cost = f_cost_new;
                        node_details[child.row][child.col].g_cost = g_cost_new;
                        node_details[child.row][child.col].h_cost = h_cost_new;
                        node_details[child.row][child.col].parent.row = i;
                        node_details[child.row][child.col].parent.col = j;
                    }
                }
            }
        }
    }


    if (!found_dest) {
        printf("Failed to find a path to the Destination node.\n");
    }

    free_min_heap(open_list.arr);
}

void a_star_test(void) {
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

    node start = {0, 0};
    node destination = {8, 8};

    a_star_search(grid, start, destination);

    printf("run_algorithm.c works");
}