//
// Created by erik on 06-12-2024.
//

#include "../function-library.h"
#include <stdlib.h>
#include <stdio.h>
#include <math.h>


// cost of moving around in a grid, and neighbor offsets.
const int col_offsets[] = {0, 0, 1, -1, -1, 1, -1, 1};
const int row_offsets[] = {-1, 1, 0, 0, -1, -1, 1, 1};
const int move_costs[] = {1, 1, 1, 1, 2, 2, 2, 2};

typedef struct heap {
    node **binary_tree;
    int size;
    int capacity;
} heap;

// TODO: Move to post process
// Temporary function that can be used in post_process after merge
void prepare_map(node **input_map, int map_size_col, int map_size_row) {
    for (int row = 0; row < map_size_row; row++) {
        for (int col = 0; col < map_size_col; col++) {
            input_map[row][col].f_cost = INT_MAX;
        }
    }
}

int is_out_of_bounds_eju(int derived_col, int derived_row, int map_size_col, int map_size_row) {
    return derived_col < 0 || derived_col >= map_size_col || derived_row < 0 || derived_row >= map_size_row;
}

heap *init_heap_eju(const int capacity) {
    heap *my_heap = malloc(sizeof(heap));
    if (my_heap == NULL) {
        printf("Error: Could not allocate memory for heap.\n");
        exit(EXIT_FAILURE);
    }

    my_heap->binary_tree = (node **) calloc(capacity, sizeof(node *));
    if (my_heap->binary_tree == NULL) {
        printf("Error: Could not allocate memory for heap array.\n");
        free(my_heap);
        exit(EXIT_FAILURE);
    }

    my_heap->size = 0;
    my_heap->capacity = capacity;

    return my_heap;
}

int get_heap_parent_eju(int index) {
    return (index - 1) / 2;
}

int get_lchild_eju(int index) {
    return 2 * index + 1;
}

int get_rchild_eju(int index) {
    return 2 * index + 2;
}

heap *heapify_eju(heap *my_heap, int index) {
    if (my_heap->size <= 1) {
        return my_heap;
    }

    int left = get_lchild_eju(index);
    int right = get_rchild_eju(index);

    int smallest = index;

    if (left < my_heap->size && my_heap->binary_tree[left]->f_cost < my_heap->binary_tree[smallest]->f_cost) {
        smallest = left;
    }
    if (right < my_heap->size && my_heap->binary_tree[right]->f_cost < my_heap->binary_tree[smallest]->f_cost) {
        smallest = right;
    }
    if (smallest != index) {
        node *temp = my_heap->binary_tree[index];
        my_heap->binary_tree[index] = my_heap->binary_tree[smallest];
        my_heap->binary_tree[smallest] = temp;
        my_heap = heapify_eju(my_heap, smallest);
    }

    return my_heap;
}

int get_heuristic_eju(node *current_node, node *destination) {
    return abs(current_node->row - destination->row) + abs(current_node->col - destination->col);
}

int get_total_g_cost_eju(int target_g_cost, node *previous_node) {
    if (previous_node == NULL)
        return 0;

    return target_g_cost + get_total_g_cost_eju(previous_node->g_cost, previous_node->parent);
}

void print_heap_sideways_eju(heap *my_heap, int index, int level) {
    if (index >= my_heap->size) {
        return;
    }

    // Print the right child first (appears at the top visually)
    print_heap_sideways_eju(my_heap, get_rchild_eju(index), level + 1);

    // Print the current node with indentation
    printf("%*s", level * 6, "");  // Indentation based on level
    printf("(%d,%d)-f=%d\n",
           my_heap->binary_tree[index]->col,
           my_heap->binary_tree[index]->row,
           my_heap->binary_tree[index]->f_cost);

    // Print the left child (appears at the bottom visually)
    print_heap_sideways_eju(my_heap, get_lchild_eju(index), level + 1);
}

void print_heap_binary_eju(heap *my_heap) {
    printf("\n----- Current Heap Structure (Sideways) -----\n");

    if (my_heap == NULL || my_heap->size == 0) {
        printf("Heap is empty.\n");
        return;
    }

    print_heap_sideways_eju(my_heap, 0, 0);

    printf("-----------------------------------------------\n\n");
}

int search_heap_node(heap* my_heap, int index, node* target_node) {
    if (my_heap->binary_tree[index] == NULL){
        return 0;
    }

    if (my_heap->binary_tree[index] == target_node) {
        return 1;
    }
    printf("DEBUG: Checking left child of (%d,%d)-f_cost(%d)\n", my_heap->binary_tree[index]->col,
        my_heap->binary_tree[index]->row, my_heap->binary_tree[index]->f_cost);
    int l_result = search_heap_node(my_heap, get_lchild_eju(index), target_node);

    printf("DEBUG: Checking right child of (%d,%d)-f_cost(%d)\n", my_heap->binary_tree[index]->col,
        my_heap->binary_tree[index]->row, my_heap->binary_tree[index]->f_cost);
    int r_result = search_heap_node(my_heap, get_rchild_eju(index), target_node);

    return (l_result || r_result);
}

void insert_heap_node_eju(heap *my_heap, node *neighbor_node) {
    if (my_heap->size >= my_heap->capacity) {
        printf("Heap overflow! Cannot insert value.\n");
        return;
    }

    if (search_heap_node(my_heap, 0, neighbor_node)) {
        return;
    }

    // Add new element at the end
    my_heap->binary_tree[my_heap->size] = neighbor_node;
    printf("DEBUG: (Priority queue)Added new node (%d,%d) with f_cost=%d at index %d\n", neighbor_node->col, neighbor_node->row,
           neighbor_node->f_cost, my_heap->size);

    int current_index = my_heap->size;
    my_heap->size++;

    printf("DEBUG: heap_parent_node (%d,%d), child_node (%d,%d)\n",
           my_heap->binary_tree[get_heap_parent_eju(current_index)]->col,
           my_heap->binary_tree[get_heap_parent_eju(current_index)]->row,
           my_heap->binary_tree[current_index]->col, my_heap->binary_tree[current_index]->row);

    // Heapify up
    //heapify_eju(my_heap, current_index);

    while (current_index != 0 &&
           my_heap->binary_tree[get_heap_parent_eju(current_index)]->f_cost >
           my_heap->binary_tree[current_index]->f_cost) {
        // Print swap details
        printf("DEBUG: Swapping nodes: index %d (f_cost=%d) and parent index %d (f_cost=%d)\n",
               current_index,
               my_heap->binary_tree[current_index]->f_cost,
               get_heap_parent_eju(current_index),
               my_heap->binary_tree[get_heap_parent_eju(current_index)]->f_cost);

        // Swap current node with its parent
        node *temp = my_heap->binary_tree[current_index];
        my_heap->binary_tree[current_index] = my_heap->binary_tree[get_heap_parent_eju(current_index)];
        my_heap->binary_tree[get_heap_parent_eju(current_index)] = temp;

        // Update current index to parent
        current_index = get_heap_parent_eju(current_index);
    }

    // Final status after sorting

    printf("DEBUG: Heapify complete. Current node at index %d with f_cost=%d\n",
           current_index, my_heap->binary_tree[current_index]->f_cost);
    print_heap_binary_eju(my_heap);
}

node *get_min_heap(heap *my_heap) {
    if (my_heap == NULL || my_heap->size == 0) {
        printf("my_heap is NULL or empty\n");
        exit(EXIT_FAILURE);
    }

    return my_heap->binary_tree[0];
}

node *get_and_remove_lowest_heap_node_eju(heap *my_heap) {
    // Get the root node, because it is the minimum
    node *lowest_f_cost_node = get_min_heap(my_heap);

    my_heap->binary_tree[0] = my_heap->binary_tree[my_heap->size - 1];
    my_heap->size--;

    // TODO: change the heapify algorithm.
    heapify_eju(my_heap, 0);

    return lowest_f_cost_node;
}

// HASH TABLE---------------------------------------
typedef struct {
    int x, y;
} Coordinate;

typedef struct hash_node {
    node* entry;
    struct hash_node *next;
} hash_node;

int hash_function_eju(int col, int row, int map_size_col) {
    return (row * map_size_col + col);
}

hash_node* init_hash_table_eju(int map_size_col, int map_size_row) {
    int hash_size = map_size_col * map_size_row;
    hash_node* closed_list = calloc(hash_size, sizeof(hash_node));
    if(closed_list == NULL) {
        printf("ERROR: Could not allocate memory for hash table\n");
        exit(EXIT_FAILURE);
    }
    return closed_list;
}

void insert_hash_table_eju(hash_node* hash_table, int map_size_col, node* new_entry) {
    int index = hash_function_eju(new_entry->col, new_entry->row, map_size_col);

    hash_node* new_hash = malloc(sizeof(hash_node));
    if (new_hash == NULL) {
        printf("ERROR: Could not allocate memory for hash node\n");
        exit(EXIT_FAILURE);
    }

    new_hash->entry = new_entry;
    new_hash->next = NULL;

    // No collision, insert directly
    if (hash_table[index].entry == NULL && hash_table[index].next == NULL) {
        hash_table[index].entry = new_entry;
        hash_table[index].next = NULL;
        free(new_hash);
    } else {
        // Handle collision with chaining
        new_hash->next = hash_table[index].next;
        hash_table[index].next = new_hash;
    }

    printf("\n");
    for (int i = 0; i < map_size_col * map_size_col; i++) {
    if (hash_table[i].entry != NULL) {
            printf("Closed_list holds at index[%d]: (%d, %d)\n",
                   i, hash_table[i].entry->col, hash_table[i].entry->row);
        }
    }
}

int is_node_in_closed_set_eju(hash_node* hash_table, node* node_to_check, int map_size_col) {
    if(hash_table == NULL || node_to_check == NULL) {
        printf("ERROR: Hash table is full.\n");
        exit(EXIT_FAILURE);
    }
    int index = hash_function_eju(node_to_check->col, node_to_check->row, map_size_col);

    hash_node* current = &hash_table[index];

    while (current != NULL && current->entry != NULL) {
        if (current->entry->col == node_to_check->col && current->entry->row == node_to_check->row) {
            return 1;
        }
        current = current->next;
    }

    return 0;
}

//___________________________________________________
void a_star_algorithm(node **input_map, int map_size_col, int map_size_row, node *start_node, node *dest_node) {
    prepare_map(input_map, map_size_col, map_size_row);
    start_node->f_cost = get_heuristic_eju(start_node, dest_node);

    // Initialization of heap
    heap* priority_queue = init_heap_eju(map_size_col * map_size_row);

    // Initialization of hash table.
    hash_node* closed_list = init_hash_table_eju(map_size_col, map_size_row);

    node *current_node = start_node;
    current_node->parent = NULL;

    while (current_node != dest_node) {
        // check neighbors
        for (int k = 0; k < 8; k++) {
            int derived_col = current_node->col + col_offsets[k];
            int derived_row = current_node->row + row_offsets[k];

            if (is_out_of_bounds_eju(derived_col, derived_row, map_size_col, map_size_row))
                continue;

            node *neighbor_node = &input_map[derived_row][derived_col];
            if (is_node_in_closed_set_eju(closed_list, neighbor_node, map_size_col))
                continue;

            printf("DEBUG: Neighbor(%d,%d) with obstacle_type(%d)\n", neighbor_node->col, neighbor_node->row,
                   neighbor_node->obstacle_type);

            if (neighbor_node->obstacle_type == 0) {
                // Calculate neighbor costs
                int temp_h_cost = get_heuristic_eju(neighbor_node, dest_node);
                int temp_g_cost = move_costs[k];
                int temp_total_g_cost = get_total_g_cost_eju(temp_g_cost, current_node);
                int temp_f_cost = temp_h_cost + temp_total_g_cost;
                if (temp_f_cost <= neighbor_node->f_cost) {
                    neighbor_node->h_cost = temp_h_cost;
                    neighbor_node->g_cost = temp_g_cost;
                    neighbor_node->f_cost = temp_f_cost;
                    neighbor_node->parent = current_node;
                }

                printf("DEBUG: ready to insert new node\n");

                insert_heap_node_eju(priority_queue, neighbor_node);
                printf("DEBUG: New node added\n\n");
            }
        }
        node *cheapest_neighbor = get_and_remove_lowest_heap_node_eju(priority_queue);
        printf("DEBUG: Cheapest neighbor is (%d,%d)\n", cheapest_neighbor->col, cheapest_neighbor->row);

        insert_hash_table_eju(closed_list, map_size_col, current_node);

        current_node = cheapest_neighbor;
        printf("DEBUG: new current node = (%d,%d)\n\n", current_node->col, current_node->row);
    }
    printf("DEBUG: destination reached. Current_node (%d,%d)\n", current_node->col, current_node->row);

    free(priority_queue);
    free(closed_list);
}

//___________________________________________________

void a_star_test_eju(void) {
    int map_size_col = 9; // representing our future variable size (not constant...)
    int map_size_row = 9; // representing our future variable size (not constant...)

    int grid[GRID_COL][GRID_ROW] = {
        {1, 0, 1, 1, 1, 1, 0, 1, 1},
        {1, 1, 1, 0, 1, 1, 1, 0, 1},
        {1, 1, 1, 0, 1, 1, 0, 1, 0},
        {0, 0, 1, 0, 1, 0, 0, 0, 0},
        {1, 1, 1, 0, 1, 1, 1, 0, 1},
        {1, 1, 1, 0, 1, 1, 0, 1, 0},
        {1, 1, 1, 1, 1, 1, 1, 1, 1},
        {1, 0, 0, 0, 0, 1, 0, 0, 1},
        {1, 1, 1, 1, 1, 1, 1, 0, 1}
    };

    // Allocate
    node **grid_with_obstacles = (node **) malloc(map_size_row * sizeof(node *));
    if (grid_with_obstacles == NULL) {
        printf("Allocation error cols\n");
        exit(EXIT_FAILURE);
    }
    for (int row = 0; row < map_size_row; row++) {
        grid_with_obstacles[row] = (node *) malloc(map_size_col * sizeof(node));
        if (grid_with_obstacles[row] == NULL) {
            printf("Allocation error rows\n");
            free(grid_with_obstacles);
            exit(EXIT_FAILURE);
        }
    }
    // Fill
    for (int row = 0; row < map_size_row; row++) {
        for (int col = 0; col < map_size_col; col++) {
            grid_with_obstacles[row][col].row = row;
            grid_with_obstacles[row][col].col = col;
            grid_with_obstacles[row][col].obstacle_type = !grid[row][col];
        }
    }
    // Print
    printf("grid_with_obstacles:\n");
    for (int row = 0; row < map_size_row; row++) {
        for (int col = 0; col < map_size_col; col++) {
            printf("%d ", grid_with_obstacles[row][col].obstacle_type);
        }
        printf("\n");
    }

    node *start_node = &grid_with_obstacles[0][0];
    node *dest_node = &grid_with_obstacles[8][8];

    a_star_algorithm(grid_with_obstacles, map_size_col, map_size_row, start_node, dest_node);

    free(grid_with_obstacles);
}
