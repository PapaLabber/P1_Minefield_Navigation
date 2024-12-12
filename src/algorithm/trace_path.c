#include <stdio.h>
#include <stdlib.h>
#include "../general-library.h"

node **trace_path(node *dest_node) {
    if (dest_node == NULL) {
        printf("Destination node is NULL.\n");
        return NULL;
    }
    node **path_list = malloc(sizeof(node *));
    if (path_list == NULL) {
        printf("path_list allocation failed");
        exit(EXIT_FAILURE);
    }

    node *temp_node = dest_node;
    int i = 0;

    // Traverse the path
    while (temp_node != NULL) {
        path_list[i] = temp_node;

        // Prepare for the next node
        temp_node = temp_node->parent;
        i++;

        // Reallocate memory for the next node
        node **new_path_list = realloc(path_list, (i + 1) * sizeof(node *));
        if (new_path_list == NULL) {
            free(path_list);
            printf("Reallocation failed\n");
            exit(EXIT_FAILURE);
        }
        path_list = new_path_list;
    }

    printf("DEBUG: show me da way\n");
    for (int j = i - 1; j >= 0; j--) {
        printf("-> (%d, %d) ", path_list[j]->col, path_list[j]->row);
    }
    printf("\n");

    return path_list;
}
