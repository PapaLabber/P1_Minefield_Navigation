#ifndef FUNCTION_LIBRARY_H
#define FUNCTION_LIBRARY_H

#endif //FUNCTION_LIBRARY_H

#define GRID_ROW 9 // # rows in the grid we'll traverse (effectively the height)
#define GRID_COL 9 // # columns in the grid we'll traverse (effectively the width)

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
    int col, row;
} node_parent;

typedef struct {
    int col, row;                // coordinates ---- x -> col, y -> row
    int g_cost;                  // cost from current node to new node
    int h_cost;                  // estimated distance from current node to destination
    int f_cost;                  // sum of g_cost h_cost
    node_parent parent;          // Pointer til forælder-node for sti-rekonstruktion
    struct node* next;
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

int parent(int index);

int parent(int index);

int lchild(int index);

int rchild(int index);

node* get_min (min_heap* heap);

min_heap* initialise_min_heap(int capacity);

void free_min_heap(min_heap* heap);

min_heap* insert_min_heap(min_heap* heap, node* element);

node* find_minimum(min_heap* heap);

min_heap* heapify(min_heap* heap, int index);

void trace_path(node node_details[GRID_ROW][GRID_COL], node destination);

void a_star_test(void);