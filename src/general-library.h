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

typedef struct hash_node {
    node *entry;
    struct hash_node *next;
} hash_node;

typedef struct tsp_node {
    node* mine;
    double dist_to_next;
} tsp_node;

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

// Function prototypes
int is_out_of_bounds(int derived_col, int derived_row, int map_size_col, int map_size_row);

// Function prototypes (Hash table)
int hash_function(int col, int row, int map_size_col);

hash_node *init_hash_table(int map_size_col, int map_size_row);

void insert_hash_table(hash_node *hash_table, int map_size_col, node *new_entry);

int is_node_in_closed_set(hash_node *hash_table, node *node_to_check, int map_size_col);


// Extra prototyper
void create_file();

#endif //FUNCTION_LIBRARY_H