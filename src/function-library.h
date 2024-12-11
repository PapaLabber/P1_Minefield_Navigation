#ifndef FUNCTION_LIBRARY_H
#define FUNCTION_LIBRARY_H

#endif //FUNCTION_LIBRARY_H

#define GRID_ROW 9 // # rows in the grid we'll traverse (effectively the height)
#define GRID_COL 9 // # columns in the grid we'll traverse (effectively the width)

#define NUMBER_OF_MINES 11

void read_map_test();
void parse_map_test();
void process_map_test();

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

typedef struct {
    int col, row;
    int g_cost;
} node_parent;




typedef struct node {
    int col, row;                // coordinates ---- x -> col, y -> row
    int g_cost;                  // cost from start node to new node
    int h_cost;                  // estimated distance from current node to destination
    int f_cost;                  // sum of g_cost h_cost
    struct node* parent;    // Pointer til forælder-node for sti-rekonstruktion
    struct node* previous_mine;  // pointer til forældre minen
    struct node* next;
    int mine_child;              // Hvor mange childs minen har
    obstacle obstacle_type;   // obstacle type ---- no obstacle == 0
    mine mine_type;           // mine type ---- no mine == 0
    // int elevation;            // height of node ---- nice to have
    int blast_radius;            // Ekstra felt til at angive risiko-niveau (f.eks. miner: højere værdi)
} node;

typedef struct min_heap {
    node** arr;                  // Array af node pointers
    int size;                    // Current size of heap
    int capacity;                // Max capacity of the heap
} min_heap;

typedef struct hash_table_entry {
    node* head;
} hash_table_entry;

typedef struct hash_table {
    hash_table_entry* entries;
    int size;
} hash_table;

typedef struct edge {
    node source, destination;
    double weight;
} edge;

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

hash_table* init_hash_table(int size);

void add_to_open_set(min_heap* pq, node* node_to_add);

node* get_and_remove_lowest_node(min_heap* pq);

void add_to_closed_set(hash_table* closed_list, node* node_to_add);

int is_node_in_closed_set(node* hash_table[][GRID_ROW], node* node_to_check);

unsigned int hash_function(int x, int y, int width);


void a_star_test_eju(void);


double calculate_distance(node current_node, node destination_node);

//void calculate_edge_weights(node mine_array[]);

void find_cheapest(/*double mine_distances[NUMBER_OF_MINES][NUMBER_OF_MINES], */int number_of_visited_mines, node visited_mines[NUMBER_OF_MINES], node mines[NUMBER_OF_MINES]);

void prim_algorithm(node array_of_mines[NUMBER_OF_MINES]);

void prim_test(void);