#ifndef A_STAR_LIBRARY_H
#define A_STAR_LIBRARY_H
#include "../general-library.h"

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


//Function prototype (Trace path)
node** trace_path(node* dest_node);


#endif //A_STAR_LIBRARY_H
