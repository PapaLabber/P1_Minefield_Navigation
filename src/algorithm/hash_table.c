#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <stdbool.h>


typedef enum is_mine {
    no_mine,
    MRUD,
    PMA2,
    PMA3,
    PROM1
} is_mine;

typedef enum is_obstacle {
    no_obstacle,
    tree,
    stone,
    bush,
    tripwire,
    deep_water
} is_obstacle;

typedef struct node {
    int x, y;                    // Koordinater
    int g_cost;                  // Omkostning fra startnoden til denne node
    int h_cost;                  // Omkostningen fra denne node til mål
    int f_cost;                  // Summen af g_cost og h_cost (f_cost = g_cost + h_cost)
    struct node* parent;         // Pointer til forælder-node for sti-rekonstruktion
    is_obstacle obstacle_type;   // Obstacle type / Ingen obstacle == 0
    is_mine mine_type;           // Minetype / Ingen mine == 0
    struct node* next;           // Til håndtering af kollisioner (chaining)
    // int elevation;            // Højden for en given celle
    int blast_radius;            // Ekstra felt til at angive risiko-niveau (f.eks. miner: højere værdi)
} node;

typedef struct hash_table_entry {
    node* head;
} hash_table_entry;

typedef struct hash_table {
    hash_table_entry* entries;
    int size;
} hash_table;

// Initialising hash_table
hash_table* init_hash_table(int size) {

    hash_table* ht = malloc(sizeof(hash_table)); // Dynamic allocating memory for room for the table
    if(ht == 0) {
        printf("Out of memory.\n");
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
        printf("Out of memory.\n");
        exit(EXIT_FAILURE);
    }

    new_node->x = x;
    new_node->y = y;
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
        if (current->x == x && current->y == y) {
            return current;
        }
        current = current->next;
    }
    return NULL;
}