#include <stdlib.h>
#include <stdio.h>
#include "general-library.h"
#include "../src/algorithm/a_star_library.h"
#include "../src/map_processing/process_library.h"
#include "../src/tsp/tsp_library.h"

int main(void) {

    int map_rows, map_cols, num_nodes, num_mines = 0, num_nodes_traveled = 0;

    node* read_map_array = read_map_from_file("map.txt", &map_rows, &map_cols, &num_nodes);

    node** map_matrix = parse_map(map_rows, map_cols, read_map_array, num_nodes);

    node* list_of_mines = process_map(map_rows, map_cols, map_matrix, &num_mines);

    // Tests
    for(int i = 0 ; i < map_rows ; i++) {
        for(int j = 0 ; j < map_cols ; j++)
            printf("[%c,%c,%c]", map_matrix[i][j].obstacle_type > 0 ? 'o':'_', map_matrix[i][j].mine_type > 0 ? 'm':'_',
                map_matrix[i][j].in_blast_zone > 0 ? 'b':'_');
        printf("\n");
    }

    node* start_node = &map_matrix[0][0];

    tsp_node* planned_route = plan_route(start_node, list_of_mines, num_mines, map_cols, map_rows);

    // Tests
    printf("Planned route:\n");
    for (int i = 0; i < num_mines+2 ; i++) {
        printf("(%d,%d) mine status: %s\n", planned_route[i].mine->col, planned_route[i].mine->row, planned_route[i].mine->mine_type ? "TRUE" : "FALSE");
    }

    node* total_traced_path = malloc(sizeof(node));
    if (total_traced_path == NULL) {
        printf("Allocation of total_traced_path failed");
        exit(EXIT_FAILURE);
    }

    int k = 0;
    for (int i = 1; i < num_mines+1; i++) {
        node* dest_node = &map_matrix[planned_route[i].mine->row][planned_route[i].mine->col];

        prepare_map(map_matrix, map_cols, map_rows);

        // Tests
        printf("\n");

        a_star_algorithm(map_matrix, map_cols, map_rows, start_node, dest_node);
        node* traced_path = trace_path(start_node, dest_node, &num_nodes_traveled);

        node* new_total_traced_path = realloc(total_traced_path, (num_nodes_traveled) * sizeof(node));
        if (new_total_traced_path == NULL) {
            printf("Allocation of new_total_traced_path failed");
            exit(EXIT_FAILURE);
        }

        // Tests
        for (int j = 0 ; j < num_nodes_traveled; j++) {
            new_total_traced_path[k++] = traced_path[j];
        }

        // Tests
        for (int l = 0 ; l < num_nodes_traveled ; l++) {
            printf("total_traced_path: (%d, %d)\n", new_total_traced_path[l].col, new_total_traced_path[l].row);
        }

        total_traced_path = new_total_traced_path;

        start_node = dest_node;
        free(traced_path);
    }

    // TODO: 1. Find ud af hvorfor den sidste mine ikke bliver tilføjet til planned route.
                // Klaret!
    // TODO: 2. Find ud af hvorfor a* springer ud fra en tidligere tilføjet parent for få fat i nogle andre miner.
                // Der var noget galt med f_cost, så nu får den bare en omgang prepare_map mere...
    // TODO: 3. Find ud hvorfor den ikke vil printe ruten i main.
    // TODO: 4. Lav en visualisering.


    for (int i = 0; i < map_rows; i++) {
        free(map_matrix[i]);
    }
    free(map_matrix);
    free(list_of_mines);
    free(total_traced_path);

    return 0;
}