#include "../general-library.h"
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define NUMBER_OF_MINES 10 //test med 10

double calculate_euclid_distance(node* start_node, node* end_node) {
    return sqrt((start_node->row - end_node->row) * (start_node->row - end_node->row) +
        (start_node->col - end_node->col) * (start_node->col - end_node->col));
}

// Funktion til at finde nærmeste mine, som ikke er besøgt
int find_nearest_mine(node* current, node* list_of_mines, int num_of_mines, hash_node* visited_mines, int map_size_col) {
    double min_distance = INT_MAX;
    int nearest_mine_index = 0;

    for (int i = 0; i < num_of_mines; i++) {
        if (is_node_in_closed_set(visited_mines, &list_of_mines[i], map_size_col)) {
            continue;
        } else {
            double dist = calculate_euclid_distance(current, &list_of_mines[i]);
            if (dist < min_distance) {
                min_distance = dist;
                nearest_mine_index = i;
            }
        }
    }

    return nearest_mine_index;
}

// Hovedfunktionen til at finde og gemme ruterne mellem start og minerne
tsp_node* plan_route(node* start_node, node* list_of_mines, int num_of_mines, int map_size_col, int map_size_row) {

    hash_node* visited_mines = init_hash_table(map_size_col, map_size_row);
    tsp_node* path_array = calloc(num_of_mines, sizeof(tsp_node));
    if (path_array == NULL) {
        printf("Allocation of path_array failed\n");
        exit(EXIT_FAILURE);
    }

    insert_hash_table(visited_mines, map_size_col, start_node);

    node* current = start_node;
    for (int i = 0; i < num_of_mines; i++) {
        // Marker minen som besøgt
        insert_hash_table(visited_mines, map_size_col, current);

        int nearest_mine_index = find_nearest_mine(current, list_of_mines, num_of_mines, visited_mines, map_size_col);

        path_array[i].mine = current;
        path_array[i].dist_to_next = calculate_euclid_distance(current, &list_of_mines[nearest_mine_index]);

        // Opdater det nuværende punkt
        current = &list_of_mines[nearest_mine_index];
    }

    free(visited_mines);

    return path_array;
}


void nearest_neighbor_test() {
    node* list_of_mines = malloc(NUMBER_OF_MINES * sizeof(node));

    node mine_1, mine_2, mine_3, mine_4, mine_5, mine_6, mine_7, mine_8, mine_9, mine_10;
    mine_1.row = 0,mine_2.row = 2, mine_3.row = 5, mine_4.row = 1, mine_5.row = 2, mine_6.row = 4, mine_7.row = 7,
    mine_8.row = 1, mine_9.row = 8, mine_10.row = 0;
    mine_1.col = 0,mine_2.col = 3, mine_3.col = 6, mine_4.col = 6, mine_5.col = 8, mine_6.col = 5, mine_7.col = 5,
    mine_8.col = 11, mine_9.col = 2, mine_10.col = 1;

    node mines[NUMBER_OF_MINES] = {
        mine_1, mine_2, mine_3, mine_4, mine_5, mine_6, mine_7, mine_8, mine_9, mine_10
    };

    for (int i = 0; i < NUMBER_OF_MINES; i++) {
        list_of_mines[i] = mines[i];
    }

    node* start = &list_of_mines[0];
    int map_size_col = 20;
    int map_size_row = 20;

    tsp_node* planned_route = plan_route(start, list_of_mines, NUMBER_OF_MINES, map_size_col, map_size_row);

    printf("\nDEBUG:\n");
    for (int i = 0 ; i < NUMBER_OF_MINES ; i++) {
        printf("Waypoint (mine): (%d, %d) with distance to next [%lf]\n", planned_route[i].mine->col, planned_route[i].mine->row,
            planned_route[i].dist_to_next);
    }


    free(list_of_mines);
    free(planned_route);
}