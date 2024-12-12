#ifndef A_STAR_LIBRARY_H
#define A_STAR_LIBRARY_H
#include "../general-library.h"

// Struct definitions
typedef struct {
    int x, y;
} Coordinate;

typedef struct hash_node {
    node *entry;
    struct hash_node *next;
} hash_node;

// Function prototypes (A* Algorithm)
double get_heuristic_euclidian(node *current_node, node *destination);

double get_total_g_cost(double target_g_cost, node *previous_node);

void a_star_algorithm(node **input_map, int map_size_col, int map_size_row, node *start_node, node *dest_node);

void a_star_test_eju(void); // temporary test function

// Function prototypes (Heap/Priority queue)
heap *init_heap(const int capacity);

int get_heap_parent(int index);

int get_lchild(int index);

int get_rchild(int index);

heap *heapify(heap *my_heap, int index);

void print_heap_sideways(heap *my_heap, int index, int level);

void print_heap_binary(heap *my_heap);

int search_heap_node(heap *my_heap, int index, node *target_node);

void insert_heap_node(heap *my_heap, node *neighbor_node);

node *get_min_heap(heap *my_heap);

node *get_and_remove_lowest_heap_node(heap *my_heap);

// Function prototypes (Hash table)
int hash_function(int col, int row, int map_size_col);

hash_node *init_hash_table(int map_size_col, int map_size_row);

void insert_hash_table(hash_node *hash_table, int map_size_col, node *new_entry);

int is_node_in_closed_set(hash_node *hash_table, node *node_to_check, int map_size_col);


#endif //A_STAR_LIBRARY_H
