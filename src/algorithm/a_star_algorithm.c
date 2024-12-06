//
// Created by erik on 06-12-2024.
//

#include "../function-library.h"
#include <stdlib.h>
#include <stdio.h>

// cost of moving around in a grid, and neighbor offsets.
const int row_offsets[] = {-1, 1, 0, 0, -1, -1, 1, 1};
const int col_offsets[] = {0, 0, 1, -1, -1, 1, -1, 1};
const int move_costs[] = {1, 1, 1, 1, 2, 2, 2, 2};

typedef struct heap {
    node** heap_array;
    int size;
    int capacity;
} heap;

heap* init_heap_eju(const int capacity) {
    heap* my_heap = (heap*)malloc(sizeof(heap));
    if (my_heap == NULL) {
        printf("Error: Could not allocate memory for heap.\n");
        exit(EXIT_FAILURE);
    }

    my_heap->heap_array = (node**)calloc(capacity,sizeof(node*));
    if (my_heap->heap_array == NULL) {
        printf("Error: Could not allocate memory for heap array.\n");
        free(my_heap);
        exit(EXIT_FAILURE);
    }

    my_heap->size = 0;
    my_heap->capacity = capacity;

    return my_heap;
}

void prepare_map_data(node** input_map, int map_size_col, int map_size_row) {
    for (int i = 0; i < map_size_col; i++) {
        for (int j = 0; j < map_size_row; j++) {
            input_map[i][j].f_cost = INT_MAX;
            input_map[i][j].g_cost = INT_MAX;
            input_map[i][j].h_cost = INT_MAX;
            input_map[i][j].parent.col = -1;
            input_map[i][j].parent.row = -1;
        }
    }
}

int get_parent_eju(int index) {
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

heap* heapify_eju(heap* my_heap, int index) {
    if(my_heap->size <= 1) {
        return my_heap;
    }

    int left = get_lchild_eju(index);
    int right = get_rchild_eju(index);

    int smallest = index;

    if (left < my_heap->size && my_heap->heap_array[left]->f_cost < my_heap->heap_array[smallest]->f_cost) {
        smallest = left;
    }
    if (right < my_heap->size && my_heap->heap_array[right]->f_cost < my_heap->heap_array[smallest]->f_cost) {
        smallest = right;
    }
    if(smallest != index) {
        node* temp = my_heap->heap_array[index];
        my_heap->heap_array[index] = my_heap->heap_array[smallest];
        my_heap->heap_array[smallest] = temp;
        my_heap = heapify_eju(my_heap, smallest);
    }

    return my_heap;
}

void insert_node_eju(heap* my_heap, node* new_node) {
    if (my_heap->size == my_heap->capacity) {
        printf("Heap overflow! Cannot insert value.\n");
        return;
    }

    my_heap->heap_array[my_heap->size] = new_node;
    int current_index = my_heap->size;
    my_heap->size++;

    //heapify_new(my_heap, current_index);
    while (current_index != 0 && my_heap->heap_array[get_parent_eju(current_index)]->f_cost > my_heap->heap_array[current_index]->f_cost) {
        // Swap current node with its parent
        node* temp = my_heap->heap_array[current_index];
        my_heap->heap_array[current_index] = my_heap->heap_array[get_parent_eju(current_index)];
        my_heap->heap_array[get_parent_eju(current_index)] = temp;

        // Move up to the parent index
        current_index = get_parent_eju(current_index);
    }
}

node* get_min_heap(heap* my_heap) {
    if (my_heap == NULL || my_heap->size == 0) {
        printf("my_heap is NULL or empty\n");
        exit(EXIT_FAILURE);
    }

    return my_heap->heap_array[0];
}

//___________________________________________________
void a_star_algorithm(node** input_map, int map_size_col, int map_size_row, node* start_node, node* destination_node) {
    // Validate input data

    // Initialization of heap
    heap* priority_queue = init_heap_eju(sizeof(input_map));

    // Initialization of hash table and add start node to it
        // just use for-loop for now...

    // set input_map costs to max and parents to -1
    prepare_map_data(input_map, map_size_col, map_size_row);
    node* current_node = start_node;

    // loop for going through every node adding to the heap and finding the "cheapest" node for every step.
    //while(1) {
        // check neighbors
        for (int d = 0; d < 8; d++) {
            node neighbor_node;
            neighbor_node.col = current_node->col + col_offsets[d];
            neighbor_node.row = current_node->row + row_offsets[d];
            neighbor_node.obstacle_type = current_node->obstacle_type;


            if(!neighbor_node.obstacle_type == 0)
                break;

            insert_node_eju(priority_queue, &neighbor_node);
        }

        // find the cheapest
        node* cheapest_neighbor = get_min_heap(priority_queue);
    //}

    //Test
    printf("(%d, %d)", cheapest_neighbor->col, cheapest_neighbor->row);



}
//___________________________________________________

void a_star_test_eju(void) {
    int map_size = 9; // representing our future variable size (not constant...)
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
    node** grid_with_obstacles = (node**)malloc(map_size * sizeof(node*));
    for (int i = 0; i < map_size; i++) {
        grid_with_obstacles[i] = (node*)malloc(map_size * sizeof(node));
    }
    // Fill
    for (int i = 0; i < map_size; i++) {
        for (int j = 0; j < map_size; j++) {
            grid_with_obstacles[i][j].obstacle_type = grid[i][j];
        }
    }
    // Print
    printf("grid_with_obstacles:\n");
    for (int i = 0; i < map_size; i++) {
        for (int j = 0; j < map_size; j++) {
            printf("%d ", grid_with_obstacles[i][j].obstacle_type);
        }
        printf("\n");
    }


    node start = {0, 0};
    node destination = {8, 8};

    a_star_algorithm(grid_with_obstacles, map_size, map_size, &start, &destination);

    free(grid_with_obstacles);
}