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
    int col, row;
    double g_cost;
    double h_cost;
    double f_cost;
    struct node* parent;
    obstacle obstacle_type;
    mine mine_type;
    int terrain;
    int in_blast_zone;
} node;

typedef struct heap {
    node **binary_tree;
    int size;
    int capacity;
} heap;

// Function prototypes
int is_out_of_bounds(int derived_col, int derived_row, int map_size_col, int map_size_row);

void trace_path(node** input_map, node* destination, int map_rows, int map_cols);

// Debug kontrol
#ifndef DEBUG
#define DEBUG 0
#endif

#if DEBUG
#define DEBUG_MSG(fmt, ...) printf(fmt, ##__VA_ARGS__)
#else
#define DEBUG_MSG(fmt, ...)
#endif


// Funktion prototyper
node* read_map_from_file (const char* file, int* rows, int* columns, int* num_nodes);
node** parse_map(const int rows, const int columns, const node* read_map_array, const int num_nodes);

// Extra prototyper
void create_file();

#endif //FUNCTION_LIBRARY_H