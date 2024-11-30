#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <stdbool.h>


#define dummygrid_width 10
#define dummygrid_height 10


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

node* hash_table[dummygrid_width][dummygrid_height];

// Statisk
bool init_hash_table() {

    for (int x = 0; x < dummygrid_width; x++) {
        for (int y = 0; y < dummygrid_height; y++) {
            hash_table[x][y] = NULL;
        }
    }
    // table is empty
}

unsigned int hash_function(int x, int y) {
    return (x % dummygrid_width + y % dummygrid_height) % dummygrid_width;
}

void insert_node(int x, int y, int cost) {
    node* new_node = malloc(sizeof(node));
    new_node->x = x;
    new_node->y = y;
    new_node->g_cost = cost;
    new_node->next = NULL;

    // Beregn hashværdi
    int hash_x = x % dummygrid_width;
    int hash_y = y % dummygrid_height;

    if (hash_table[hash_x][hash_y] == NULL) {
        hash_table[hash_x][hash_y] = new_node;
    } else {
        node* current = hash_table[hash_x][hash_y];
        while (current->next != NULL) {
            current = current->next;
        }
        current->next = new_node;
    }
}

node* find_node(int x, int y) {
    int hash_x = x % dummygrid_width;
    int hash_y = y % dummygrid_height;

    node* current = hash_table[hash_x][hash_y];
    while (current != NULL) {
        if (current->x == x && current->y == y) {
            return current;
        }
        current = current->next;
    }
    return NULL;
}