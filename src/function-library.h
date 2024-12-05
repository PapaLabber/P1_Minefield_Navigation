#ifndef FUNCTION_LIBRARY_H
#define FUNCTION_LIBRARY_H

#endif //FUNCTION_LIBRARY_H

void read_map_test();
void parse_map_test();
void process_map_test();

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

typedef struct {
    int col, row;                // coordinates ---- x -> col, y -> row
    int g_cost;                  // cost from current node to new node
    int h_cost;                  // estimated distance from current node to destination
    int f_cost;                  // sum of g_cost h_cost
    struct node* parent;         // Pointer til forælder-node for sti-rekonstruktion
    is_obstacle obstacle_type;   // obstacle type ---- no obstacle == 0
    is_mine mine_type;           // mine type ---- no mine == 0
    // int elevation;            // height of node ---- nice to have
    int blast_radius;            // Ekstra felt til at angive risiko-niveau (f.eks. miner: højere værdi)
} node;

typedef struct min_heap {
    node** arr;                  // Array af node pointers
    int size;                    // Current size of heap
    int capacity;                // Max capacity of the heap
} min_heap;

min_heap* insert_min_heap(min_heap* heap, node* element);

min_heap* find_minimum(min_heap* heap);

void free_min_heap(min_heap* heap);

int parent(int index);

min_heap* heapify(min_heap* heap, int index);
