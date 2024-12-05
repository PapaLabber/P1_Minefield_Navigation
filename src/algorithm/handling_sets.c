#include <stdio.h>
#include "../function-library.h"

// Adds node to open set using min_heap (Priority que)
void add_to_open_set(min_heap* pq, node* node_to_add) {

    if(pq == NULL || node_to_add == NULL) {
        printf("ERROR: Priority queue is full.\n");
        return;
    }

    insert_min_heap(pq, node_to_add);
}

// Finds the lowest f cost
node* get_and_remove_lowest_node(min_heap* pq) {
    if(pq == NULL || pq->size == 0) {
        printf("ERROR: Priority queue is full.\n");
        return NULL;
    }

    // Get the root node, because it is the minimum
    node* lowest_f_cost_node = pq->arr[0];

    pq->arr[0] = pq->arr[pq->size - 1];
    pq->size--;

    heapify(pq, 0);

    return get_and_remove_lowest_node;
}

// Add note to the closed set (obstacles)
void add_to_closed_set(node* hash_table[][GRID_ROW], node* node_to_add) {
    if(hash_table == NULL || node_to_add == NULL) {
        printf("ERROR: Hash table is full or node is invalid.\n");
        return;
    }

    int hash_col = node_to_add->col % GRID_COL;
    int hash_row = node_to_add->row % GRID_ROW;

    if(hash_table[hash_col][hash_row] == NULL) {
        hash_table[hash_col][hash_row] = node_to_add;
        node_to_add->next = NULL;
    } else {
        node_to_add->next = hash_table[hash_col][hash_row];
        hash_table[hash_col][hash_row] = node_to_add;
    }
}

// Checks if a node is already in the closed set
int is_node_in_closed_set(node* hash_table[][GRID_ROW], node* node_to_check) {
    if(hash_table == NULL || node_to_check == NULL) {
        printf("ERROR: Hash table is full.\n");
        return;
    }

    int hash_col = node_to_check->col % GRID_COL;
    int hash_row = node_to_check->row % GRID_ROW;

    node* current = hash_table[hash_col][hash_row];
    while (current != NULL) {
        if (current->col == node_to_check->col && current->row == node_to_check->row) {
            return 1;
        }
        current = current->next;
    }

    return 0;
}