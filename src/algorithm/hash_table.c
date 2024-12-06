#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include "../function-library.h"

// Initialising hash_table
hash_table* init_hash_table(int size) {

    hash_table* ht = malloc(sizeof(hash_table)); // Dynamic allocating memory for room for the table
    if(ht == NULL) {
        printf("ERROR: Out of memory.\n");
        exit(EXIT_FAILURE);
    }
    ht->entries = calloc(size, sizeof(hash_table_entry)); // Allocating memory with calloc for entries and sets to NULL
    ht->size = size;
    return ht;
}

// Size of the grid and hash_function
unsigned int hash_function(int x, int y, int width) {
    return y * width + x;
}

// Inserting a new node in the hashtable and calculating hashvalue to place node in hash_table_entry
void insert_node(int x, int y, int width, int cost, hash_table* ht) {
    node* new_node = malloc(sizeof(node)); // Dynamic allocating memory for new_node
    if (new_node == NULL) {
        printf("ERROR: Out of memory.\n");
        exit(EXIT_FAILURE);
    }

    new_node->col = x;
    new_node->row = y;
    new_node->g_cost = cost;
    new_node->next = NULL;

    // Calculating hash value
    int hash = hash_function(x, y, width) % ht->size;

    // Find correct bucket
    node* current = ht->entries[hash].head;

    // Separate chaining
    if (current == NULL) {
        ht->entries[hash].head = new_node;
    } else {
        while (current->next != NULL) {
            current = current->next;
        }
        current->next = new_node;
    }
}
// Searching for node in the hash_table from (x,y) coordinates
node* find_node(int x, int y, int width, hash_table* ht) {

    int hash = hash_function(x, y, width) % ht->size;

    node* current = ht->entries[hash].head;
    while (current != NULL) {
        if (current->col == x && current->row == y) {
            return current;
        }
        current = current->next;
    }
    return NULL;
}