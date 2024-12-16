#include <stdlib.h>
#include <stdio.h>
#include "general-library.h"
#include "../src/algorithm/a_star_library.h"
#include "../src/map_processing/process_library.h"
#include "../src/tsp/tsp_library.h"

int main(void) {

    int map_rows, map_cols, num_nodes, num_mines = 0;

    node* read_map_array = read_map_from_file("map.txt", &map_rows, &map_cols, &num_nodes);

    node** map_matrix = parse_map(map_rows, map_cols, read_map_array, num_nodes);

    node* list_of_mines = process_map(map_rows, map_cols, map_matrix, &num_mines);

    node* start_node = &map_matrix[0][0];

    tsp_node* planned_route = plan_route(start_node, list_of_mines, num_mines, map_cols, map_rows);

    node** total_traced_path = malloc(sizeof(void));
    if (total_traced_path == NULL) {
        printf("Allocation of total_traced_path failed");
        exit(EXIT_FAILURE);
    }

    // TODO: use A* between every mine in planned_route
    for (int i = 0; i < num_mines; i++) {
        node* dest_node = &map_matrix[planned_route[i].mine->row][planned_route[i].mine->col];

        a_star_algorithm(map_matrix, map_cols, map_rows, start_node, dest_node);
        node** traced_path = trace_path(dest_node);

        node** new_total_traced_path = realloc(total_traced_path, sizeof(total_traced_path) + sizeof(traced_path));
        if (new_total_traced_path == NULL) {
            printf("Allocation of new_total_traced_path failed");
            exit(EXIT_FAILURE);
        }

        for (int j = 0 ; j < sizeof(traced_path) ; j++) {
            new_total_traced_path[sizeof(total_traced_path) + j] = traced_path[j];
            printf("-> (%d,%d) ", new_total_traced_path[j]->col, new_total_traced_path[j]->row);

        }
        printf("\n");

        total_traced_path = new_total_traced_path;
        start_node = dest_node;
        free(traced_path);
    }

    // TODO: Lav en visualisering


    for (int i = 0; i < map_rows; i++) {
        free(map_matrix[i]);
    }
    free(map_matrix);
    free(list_of_mines);
    free(total_traced_path);

    return 0;
}