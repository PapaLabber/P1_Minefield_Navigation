#ifndef FUNCTION_LIBRARY_H
#define FUNCTION_LIBRARY_H

// Struct definitions
typedef enum mine {
    no_mine,
    MRUD,
    PMA2,
    PMA3,
    PROM1
} mine;

typedef enum obstacle {
    no_obstacle = 0,
    tree,
    stone,
    bush,
    tripwire,
    deep_water
} obstacle;

typedef struct node {
    int col, row;                // coordinates ---- x -> col, y -> row
    int g_cost;                  // cost from start node to new node
    int h_cost;                  // estimated distance from current node to destination
    int f_cost;                  // sum of g_cost h_cost
    struct node* parent;          // Pointer til forælder-node for sti-rekonstruktion
    struct node* next;
    obstacle obstacle_type;   // obstacle type ---- no obstacle == 0
    mine mine_type;           // mine type ---- no mine == 0
    // int elevation;            // height of node ---- nice to have
    int blast_radius;            // Ekstra felt til at angive risiko-niveau (f.eks. miner: højere værdi)
} node;

typedef struct heap {
    node **binary_tree;
    int size;
    int capacity;
} heap;

// Function prototypes
int is_out_of_bounds(int derived_col, int derived_row, int map_size_col, int map_size_row);

// Debug kontrol
#ifndef DEBUG
#define DEBUG 1
#endif

#if DEBUG
#define DEBUG_MSG(fmt, ...) printf(fmt, ##__VA_ARGS__)
#else
#define DEBUG_MSG(fmt, ...)
#endif


// Funktion prototyper
node* read_map_from_file (const char* file, int* rows, int* columns, int* num_cells);
node** parse_map(const int rows, const int columns, const node* read_map_array, const int num_cells);

// Extra prototyper
void create_file();

#endif //FUNCTION_LIBRARY_H