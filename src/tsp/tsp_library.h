
#ifndef TSP_LIBRARY_H
#define TSP_LIBRARY_H

#include "../general-library.h"

// Function prototypes (TSP)
tsp_node* plan_route(node* start_node, node* list_of_mines, int num_of_mines, int map_size_col, int map_size_row);

int find_nearest_mine(node* current, node* list_of_mines, int num_of_mines, const int visited_mines[]);

double calculate_euclid_distance(node* p1, node* p2);

void nearest_neighbor_test();



#endif //TSP_LIBRARY_H
