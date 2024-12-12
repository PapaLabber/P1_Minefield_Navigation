#include "../general-library.h"
#include "../algorithm/a_star_library.h"
#include <stdlib.h>
#include <stdio.h>

int hash_function(int col, int row, int map_size_col) {
    return (row * map_size_col + col);
}

hash_node* init_hash_table(int map_size_col, int map_size_row) {
    int hash_size = map_size_col * map_size_row;
    hash_node* closed_list = calloc(hash_size, sizeof(hash_node));
    if(closed_list == NULL) {
        printf("ERROR: Could not allocate memory for hash table\n");
        exit(EXIT_FAILURE);
    }
    return closed_list;
}

void insert_hash_table(hash_node* hash_table, int map_size_col, node* new_entry) {
    int index = hash_function(new_entry->col, new_entry->row, map_size_col);

    hash_node* new_hash = malloc(sizeof(hash_node));
    if (new_hash == NULL) {
        printf("ERROR: Could not allocate memory for hash node\n");
        exit(EXIT_FAILURE);
    }

    new_hash->entry = new_entry;
    new_hash->next = NULL;

    // No collision, insert directly
    if (hash_table[index].entry == NULL && hash_table[index].next == NULL) {
        hash_table[index].entry = new_entry;
        hash_table[index].next = NULL;
        free(new_hash);
    } else {
        // Handle collision with chaining
        new_hash->next = hash_table[index].next;
        hash_table[index].next = new_hash;
    }

    printf("\n");
    for (int i = 0; i < map_size_col * map_size_col; i++) {
    if (hash_table[i].entry != NULL) {
            printf("Closed_list holds at index[%d]: (%d, %d)\n",
                   i, hash_table[i].entry->row, hash_table[i].entry->col);
        }
    }
}

int is_node_in_closed_set(hash_node* hash_table, node* node_to_check, int map_size_col) {
    if(hash_table == NULL || node_to_check == NULL) {
        printf("ERROR: Hash table is full.\n");
        exit(EXIT_FAILURE);
    }
    int index = hash_function(node_to_check->col, node_to_check->row, map_size_col);

    hash_node* current = &hash_table[index];

    while (current != NULL && current->entry != NULL) {
        if (current->entry->col == node_to_check->col && current->entry->row == node_to_check->row) {
            return 1;
        }
        current = current->next;
    }

    return 0;
}