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

    // Print map with obstacles, mines and blast_radius
    for(int i = 0 ; i < map_rows ; i++) {
        for(int j = 0 ; j < map_cols ; j++)
            printf("[%c,%c,%c]", map_matrix[i][j].obstacle_type > 0 ? 'o':'_', map_matrix[i][j].mine_type > 0 ? 'm':'_',
                map_matrix[i][j].in_blast_zone > 0 ? 'b':'_');
        printf("\n");
    }

    node* start_node = &map_matrix[0][0];

    tsp_node* planned_route = plan_route(start_node, list_of_mines, num_mines, map_cols, map_rows);

    // Test
    printf("Planned route:\n");
    for (int i = 0; i < num_mines+2 ; i++) {
        printf("(%d,%d) mine status: %s\n", planned_route[i].mine->col, planned_route[i].mine->row,
            planned_route[i].mine->mine_type ? "TRUE" : "FALSE");
    }

    node* total_traced_path = malloc(sizeof(node));
    if (total_traced_path == NULL) {
        printf("Allocation of total_traced_path failed");
        exit(EXIT_FAILURE);
    }

    int total_path_index = 0;
    for (int i = 1; i < num_mines+2; i++) {
        node* dest_node = &map_matrix[planned_route[i].mine->row][planned_route[i].mine->col];

        prepare_map(map_matrix, map_cols, map_rows);

        a_star_algorithm(map_matrix, map_cols, map_rows, start_node, dest_node);

        int local_traced_path_index = 0;
        node* traced_path = trace_path(start_node, dest_node, &total_path_index, &local_traced_path_index);
        total_traced_path = total_path(traced_path, total_traced_path, &total_path_index, local_traced_path_index);

        start_node = dest_node;
    }


    for (int i = 0; i < map_rows; i++) {
        free(map_matrix[i]);
    }
    free(map_matrix);
    free(list_of_mines);
    free(total_traced_path);

    return 0;
}