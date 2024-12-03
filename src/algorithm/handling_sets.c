#include <stdio.h>
#include <stdio.h>
#include <string.h>
#include <math.h>
#include <stdlib.h>
#include <stdbool.h>
#include <stdnoreturn.h>


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
    // int elevation;           // Højden for en given celle
    int blast_radius;            // Ekstra felt til at angive risiko-niveau (f.eks. miner: højere værdi)
} node;

typedef struct min_heap {
    node** arr;                  // Array af node pointers
    int size;                    // Current size of heap
    int capacity;                // Max capacity of the heap
} min_heap;

// Adds node to open set using min_heap (Priority que)
void add_to_open_set(min_heap* pq, node* node_to_add) {

    if(pq == NULL || node_to_add == NULL) {
        fprintf(stderr, "Error: Priority queue is full.\n");
        return;
    }

    insert_min_heap(pq, node_to_add);
}

// Finds the lowest f cost
node* find_lowest_f_cost(min_heap* pq) {
    if(pq == NULL || pq->size == 0) {
        fprintf(stderr, "Error: Priority queue is full.\n");
        return NULL;
    }

    // Get the root node, because it is the minimum
    node* lowest_f_cost_node = pq->arr[0];

    pq->arr[0] = pq->arr[pq->size - 1];
    pq->size--;

    heapify(pq, 0);

    return lowest_f_cost_node;
}

// Add note to the closed set (obstacles)
void add_to_closed_set(node* hash_table[][dummygrid_height], node* node_to_add) {
    if(hash_table == NULL || node_to_add == NULL) {
        fprintf(stderr, "Error: Hash table is full.\n");
        return;
    }

    int hash_x = node_to_add->x % dummygrid_width;
    int hash_y = node_to_add->y % dummygrid_height;

    if(hash_table[hash_x][hash_y] == NULL) {
        hash_table[hash_x][hash_y] = node_to_add;
        node_to_add->next = NULL;
    } else {
        node_to_add->next = hash_table[hash_x][hash_y];
        hash_table[hash_x][hash_y] = node_to_add;
    }
}

// Checks if a node is already in the closed set
int is_node_in_closed_set(node* hash_table[][dummygrid_height], node* node_to_check) {
    if(hash_table == NULL || node_to_check == NULL) {
        fprintf(stderr, "Error: Hash table is full.\n");
        return;
    }

    int hash_x = node_to_check->x % dummygrid_width;
    int hash_y = node_to_check->y % dummygrid_height;

    node* current = hash_table[hash_x][hash_y];
    while (current != NULL) {
        if (current->x == node_to_check->x && current->y == node_to_check) {
            return 1;
        }
        current = current->next;
    }

    return 0;
}