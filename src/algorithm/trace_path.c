#include <stdio.h>
#include <stdlib.h>
#include "../general-library.h"

node* trace_path(node* start_node, node *dest_node, int* num_nodes_traveled) {
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
    //path_list[0] = temp_node;
    int i = 0;

    // Traverse the path
    while (temp_node.parent != NULL &&
         !(temp_node.col == start_node->col && temp_node.row == start_node->row)) {

        path_list[i] = temp_node;
        i++;

        // Reallocate memory for the next node
        node *new_path_list = realloc(path_list, (i+1) * sizeof(node));
        if (new_path_list == NULL) {
            free(path_list);
            printf("Reallocation failed\n");
            exit(EXIT_FAILURE);
        }
        path_list = new_path_list;

        temp_node = *temp_node.parent;
    }
    *num_nodes_traveled += i;

    // Print result
    for (int j = 0; j < i; j++) {
        printf("(%d, %d) -> ", path_list[j].col, path_list[j].row);
    }
    printf("\n");

    // Invert list
    for (int j = 0; j < i / 2; j++) {
        node temp = path_list[j];
        path_list[j] = path_list[i - 1 - j];
        path_list[i - 1 - j] = temp;
    }

    // Print result
    for (int j = 0; j < i; j++) {
        printf("(%d, %d) -> ", path_list[j].col, path_list[j].row);
    }
    printf("\n");


    return path_list;
}
