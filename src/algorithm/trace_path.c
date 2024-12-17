#include <stdio.h>
#include <stdlib.h>
#include "../general-library.h"

node* trace_path(node* start_node, node *dest_node, int* total_path_index, int* local_traced_path_index) {
    if (dest_node == NULL) {
        printf("Destination node is NULL.\n");
        return NULL;
    }
    node* path_list = malloc(sizeof(node));
    if (path_list == NULL) {
        printf("path_list allocation failed");
        exit(EXIT_FAILURE);
    }

    node temp_node = *dest_node;
    int capacity = 1;  // Initial capacity

    // Traverse the path
    while (temp_node.parent != NULL &&
           !(temp_node.col == start_node->col && temp_node.row == start_node->row)) {

        path_list[*local_traced_path_index] = temp_node;
        (*local_traced_path_index)++;
        (*total_path_index)++;

        // Expand the list if necessary
        if ((*local_traced_path_index) >= capacity) {
            capacity = *local_traced_path_index+1;
            node *new_path_list = realloc(path_list, capacity * sizeof(node));
            if (new_path_list == NULL) {
                free(path_list);
                printf("Reallocation failed\n");
                exit(EXIT_FAILURE);
            }
            path_list = new_path_list;
        }

        temp_node = *temp_node.parent;
    }


    // Print result
    for (int j = 0; j < (*local_traced_path_index); j++) {
        printf("(%d, %d) -> ", path_list[j].col, path_list[j].row);
    }
    printf("\n");

    // Invert list
    for (int j = 0; j < (*local_traced_path_index) / 2; j++) {
        node temp = path_list[j];
        path_list[j] = path_list[(*local_traced_path_index) - 1 - j];
        path_list[(*local_traced_path_index) - 1 - j] = temp;
    }

    // Print result
    for (int j = 0; j < (*local_traced_path_index); j++) {
        printf("(%d, %d) -> ", path_list[j].col, path_list[j].row);
    }
    printf("\n");


    return path_list;
}

node* total_path(node* local_traced_path, node* total_traced_path, int* total_path_index, int local_traced_path_size) {
    node* new_total_traced_path = realloc(total_traced_path, (*total_path_index) * sizeof(node));
    if (new_total_traced_path == NULL) {
        printf("Allocation of new_total_traced_path failed");
        exit(EXIT_FAILURE);
    }
    total_traced_path = new_total_traced_path;

    for (int i = 0 ; i < local_traced_path_size; i++) {
        total_traced_path[*total_path_index - local_traced_path_size + i] = local_traced_path[i];
    }

    // Tests
    for (int i = 0 ; i < *total_path_index ; i++) {
        printf("total_traced_path: (%d, %d)\n", total_traced_path[i].col, total_traced_path[i].row);
    }

    return total_traced_path;
}
