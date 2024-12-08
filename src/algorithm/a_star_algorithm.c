//
// Created by erik on 06-12-2024.
//

#include "../function-library.h"
#include <stdlib.h>
#include <stdio.h>

// cost of moving around in a grid, and neighbor offsets.
const int col_offsets[] = {0, 0, 1, -1, -1, 1, -1, 1};
const int row_offsets[] = {-1, 1, 0, 0, -1, -1, 1, 1};
const int move_costs[] = {1, 1, 1, 1, 2, 2, 2, 2};

typedef struct heap {
    node **binary_tree;
    int size;
    int capacity;
} heap;

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

void prepare_map_data(node **input_map, int map_size_col, int map_size_row) {
    for (int i = 0; i < map_size_col; i++) {
        for (int j = 0; j < map_size_row; j++) {
            input_map[i][j].f_cost = INT_MAX;
            input_map[i][j].g_cost = INT_MAX;
            input_map[i][j].h_cost = INT_MAX;
            //input_map[i][j].parent->col = -1;
            //input_map[i][j].parent->row = -1;
        }
    }
}

int get_heap_parent_eju(int index) {
    return (index - 1) / 2;
}

int get_lchild_eju(int index) {
    // Index of left child node
    return 2 * index + 1;
}

int get_rchild_eju(int index) {
    // Index of left child node
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

int get_total_g_cost_eju(node *target_node, node *previous_node) {
    if (previous_node == NULL)
        return 0;

    return target_node->g_cost + get_total_g_cost_eju(previous_node, previous_node->parent);
}

void insert_node_eju(heap *my_heap, node *neighbor_node) {
    if (my_heap->size >= my_heap->capacity) {
        printf("Heap overflow! Cannot insert value.\n");
        return;
    }

    // Add new element at the end
    my_heap->binary_tree[my_heap->size] = neighbor_node;
    printf("DEBUG: Added new node (%d,%d) with f_cost=%d at index %d\n", neighbor_node->col, neighbor_node->row,
           neighbor_node->f_cost, my_heap->size);

    int current_index = my_heap->size;
    my_heap->size++;

    printf("DEBUG: parent_node (%d,%d), current_node (%d,%d)\n",
           my_heap->binary_tree[get_heap_parent_eju(current_index)]->col,
           my_heap->binary_tree[get_heap_parent_eju(current_index)]->row,
           my_heap->binary_tree[current_index]->col, my_heap->binary_tree[current_index]->row);

    // Heapify up
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
}

node *get_min_heap(heap *my_heap) {
    if (my_heap == NULL || my_heap->size == 0) {
        printf("my_heap is NULL or empty\n");
        exit(EXIT_FAILURE);
    }

    return my_heap->binary_tree[0];
}

node *get_and_remove_lowest_node_eju(heap *my_heap) {
    // Get the root node, because it is the minimum
    node *lowest_f_cost_node = get_min_heap(my_heap);

    my_heap->binary_tree[0] = my_heap->binary_tree[my_heap->size - 1];
    my_heap->size--;

    heapify_eju(my_heap, 0);

    return lowest_f_cost_node;
}

// HASH TABLE---------------------------------------
#define HASH_SIZE 101 // midlertidig - kan ikke bruges i den færdige kode

typedef struct {
    int x, y;
} Coordinate;

/*The HashNode struct with the next pointer implements separate chaining using a linked list. Here's how it works:

Each bucket in the hash table (hashTable[index]) points to the head of a linked list.
When inserting a new coordinate, if the computed hash index is already occupied, we chain the new HashNode to the front of the list.
When searching, we traverse this linked list until we find the matching coordinates or reach the end (indicating the coordinate hasn’t been visited).*/

typedef struct HashNode {
    Coordinate coord;
    struct HashNode *next;
} HashNode;

// Hash table
HashNode *hashTable[HASH_SIZE];

// Hash function
int hash_function_eju(int x, int y) {
    return (x * 31 + y) % HASH_SIZE;
}

int hash_search(int x, int y) {
    int index = hash_function_eju(x, y);
    HashNode *current = hashTable[index];
    while (current != NULL) {
        if (current->coord.x == x && current->coord.y == y) {
            return 1; // Found
        }
        current = current->next;
    }
    return 0; // Not found
}

void hash_insert_node(int x, int y) {
    int index = hash_function_eju(x, y);

    // Check if already present
    HashNode *current = hashTable[index];
    while (current != NULL) {
        if (current->coord.x == x && current->coord.y == y) {
            return; // Already visited
        }
        current = current->next;
    }

    // Insert at the beginning of the list
    HashNode *newNode = (HashNode *) malloc(sizeof(HashNode));
    newNode->coord.x = x;
    newNode->coord.y = y;
    newNode->next = hashTable[index];
    hashTable[index] = newNode;
}

void hash_cleanup() {
    for (int i = 0; i < HASH_SIZE; i++) {
        HashNode *current = hashTable[i];
        while (current != NULL) {
            HashNode *temp = current;
            current = current->next;
            free(temp);
        }
        hashTable[i] = NULL;
    }
}

//___________________________________________________
void a_star_algorithm(node **input_map, int map_size_col, int map_size_row, node *start_node, node *dest_node) {
    // Initialization of heap
    heap *priority_queue = init_heap_eju(map_size_col * map_size_row);

    // Initialization of hash table.
    // TODO: implement hash table for closed list

    // set input_map costs to max and parents to -1
    prepare_map_data(input_map, map_size_col, map_size_row);

    node *current_node = start_node;
    current_node->parent = NULL;

    while (current_node != dest_node) {
        // check neighbors
        for (int k = 0; k < 8; k++) {
            int derived_col = current_node->col + col_offsets[k];
            int derived_row = current_node->row + row_offsets[k];

            // Out of bounds?:
            if (derived_col < 0 || derived_col >= map_size_col || derived_row < 0 || derived_row >= map_size_row)
                continue;

            node *neighbor_node = &input_map[derived_col][derived_row];
            printf("DEBUG: Neighbor(%d,%d) with obstacle_type(%d)\n", neighbor_node->col, neighbor_node->row,
                   neighbor_node->obstacle_type);

            if (neighbor_node->obstacle_type == 0) {
                // Calculate neighbor costs
                neighbor_node->h_cost = get_heuristic_eju(neighbor_node, dest_node);
                neighbor_node->g_cost = move_costs[k];
                int total_g_cost = get_total_g_cost_eju(neighbor_node, current_node);
                neighbor_node->f_cost = neighbor_node->h_cost + total_g_cost;

                printf("DEBUG: ready to insert new node\n");

                insert_node_eju(priority_queue, neighbor_node);
                printf("DEBUG: New node added\n\n");
            }
        }
        // find the cheapest
        node *cheapest_neighbor = get_and_remove_lowest_node_eju(priority_queue);
        printf("DEBUG: Cheapest neighbor is (%d,%d)\n\n", cheapest_neighbor->col, cheapest_neighbor->row);
        cheapest_neighbor->parent = current_node;

        // TODO: Add current_node to closed_list

        current_node = cheapest_neighbor;
    }
    printf("DEBUG: destination reached. Current_node (%d,%d)\n", current_node->col, current_node->row);

    free(priority_queue);
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
