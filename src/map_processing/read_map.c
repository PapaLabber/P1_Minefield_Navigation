#include "../general-library.h"
#include <stdio.h>
#include <stdlib.h>

node* read_map_from_file (const char* file, int* map_rows, int* map_cols, int* num_nodes) {
    /* Først åbnes filen i read mode */
    FILE* local_file = fopen(file, "r");
    if (local_file == NULL) {
        printf("Error - read_map: File could not be opened...\n");
        exit (EXIT_FAILURE);
    }
    DEBUG_MSG("DEBUG - read_map: File opened successfully: %s\n", file);

    fscanf(local_file, "%d %d", map_rows, map_cols);
    DEBUG_MSG("DEBUG - read_map: Read map_rows = %d, map_cols = %d\n", *map_rows, *map_cols);

    *num_nodes = *map_rows * *map_cols;
    DEBUG_MSG("DEBUG - read_map: Number of nodes calculated = %d\n", *num_nodes);

    node* node_array = calloc((*num_nodes), sizeof(node));
    if (node_array == NULL) {
        printf("Error - read_map: Memory allocation for node array failed...\n<");
        exit (EXIT_FAILURE);
    }

    /* Udfyld array med node data */
    for (int i = 0; i < *num_nodes; i++) {
            if (fscanf(local_file, "%d %d %d",
                    &node_array[i].obstacle_type,
                    &node_array[i].terrain,
                    &node_array[i].mine_type) != 3) {
                printf("Error - read_map: Failed to read node %d\n", i);
                free(node_array);
                fclose(local_file);
                exit (EXIT_FAILURE);
            }
            DEBUG_MSG("DEBUG - read_map: node_array[%d] = (%d, %d, %d)\n",
                i, node_array[i].obstacle_type, node_array[i].terrain, node_array[i].mine_type);
    }

    fclose(local_file);
    DEBUG_MSG("DEBUG - read_map: File closed successfully\n");
    return node_array;
}

void read_map_test() {
    int map_rows, map_cols, num_nodes;

    node* node_array = read_map_from_file("map.txt", &map_rows, &map_cols, &num_nodes);

    printf("Test/read_map - Dimensions: map_rows = %d, map_cols = %d, num_nodes = %d\n",
        map_rows, map_cols, num_nodes);

    /* Verificering af data i hver node */
    for (int i = 0; i < num_nodes; i++) {
        printf("Test/read_map - node array[%d] = (%d, %d, %d)\n",
            i, node_array[i].obstacle_type, node_array[i].terrain, node_array[i].mine_type);
    }

    /* Frigørelse af allokeret hukommelse */
    free(node_array);
    printf("Test/read_map - Memory of node array freed successfully\n");
}

