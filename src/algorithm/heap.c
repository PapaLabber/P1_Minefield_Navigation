#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include "../general-library.h"
#include "../algorithm/a_star_library.h"

int get_heap_parent(int index) {
    return (index - 1) / 2;
}

int get_lchild(int index) {
    return 2 * index + 1;
}

int get_rchild(int index) {
    return 2 * index + 2;
}

heap *init_heap(int capacity) {
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

heap *heapify(heap *my_heap, int index) {
    if (my_heap->size <= 1) {
        return my_heap;
    }

    int left = get_lchild(index);
    int right = get_rchild(index);

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
        my_heap = heapify(my_heap, smallest);
    }

    return my_heap;
}

void print_heap_sideways(heap *my_heap, int index, int level) {
    if (index >= my_heap->size) {
        return;
    }

    // Print the right child first (appears at the top visually)
    print_heap_sideways(my_heap, get_rchild(index), level + 1);

    // Print the current node with indentation
    printf("%*s", level * 6, ""); // Indentation based on level
    printf("(%d,%d)-f=%.4lf\n",
           my_heap->binary_tree[index]->col,
           my_heap->binary_tree[index]->row,
           my_heap->binary_tree[index]->f_cost);

    // Print the left child (appears at the bottom visually)
    print_heap_sideways(my_heap, get_lchild(index), level + 1);
}

void print_heap_binary(heap *my_heap) {
    //printf("\n--- DEBUG(print_heap_binary): Current Heap Structure ---\n");

    if (my_heap == NULL || my_heap->size == 0) {
        printf("Heap is empty.\n");
        return;
    }

    //print_heap_sideways(my_heap, 0, 0);

    //printf("-----------------------------------------------\n\n");
}

node *get_min_heap(heap *my_heap) {
    if (my_heap == NULL || my_heap->size == 0) {
        printf("my_heap is NULL or empty\n");
        exit(EXIT_FAILURE);
    }

    return my_heap->binary_tree[0];
}

int search_heap_node(heap *my_heap, int index, node *target_node) {
    if (my_heap->binary_tree[index] == NULL) {
        return 0;
    }

    if (my_heap->binary_tree[index] == target_node) {
        return 1;
    }
    DEBUG_MSG("DEBUG(search_heap_node): Checking left child of (%d,%d)-f_cost(%lf)\n", my_heap->binary_tree[index]->row,
           my_heap->binary_tree[index]->col, my_heap->binary_tree[index]->f_cost);
    int l_result = search_heap_node(my_heap, get_lchild(index), target_node);

    DEBUG_MSG("DEBUG(search_heap_node): Checking right child of (%d,%d)-f_cost(%lf)\n", my_heap->binary_tree[index]->row,
           my_heap->binary_tree[index]->col, my_heap->binary_tree[index]->f_cost);
    int r_result = search_heap_node(my_heap, get_rchild(index), target_node);

    return (l_result || r_result);
}

node *get_and_remove_lowest_heap_node(heap *my_heap) {
    // Retrieving of root node, having the smallest f_cost
    node *lowest_f_cost_node = get_min_heap(my_heap);

    // New root node assigned and heap size adjusted
    my_heap->binary_tree[0] = my_heap->binary_tree[my_heap->size - 1];
    my_heap->size--;

    // Heapify top-down used because root node is deleted and new is assigned
    heapify(my_heap, 0);

    // Return of previous root node
    return lowest_f_cost_node;
}

void insert_heap_node(heap *my_heap, node *neighbor_node) {
    if (my_heap->size >= my_heap->capacity) {
        printf("Heap overflow! Cannot insert value.\n");
        return;
    }

    if (search_heap_node(my_heap, 0, neighbor_node)) {
        return;
    }

    // Add new element at the end
    my_heap->binary_tree[my_heap->size] = neighbor_node;
    DEBUG_MSG("DEBUG(insert_heap_node): (Priority queue)Added new node (%d,%d) with f_cost=%lf at index %d\n", neighbor_node->row,
           neighbor_node->col,
           neighbor_node->f_cost, my_heap->size);

    int current_index = my_heap->size;
    my_heap->size++;

    DEBUG_MSG("DEBUG(insert_heap_node): heap_parent_node (%d,%d), child_node (%d,%d)\n",
           my_heap->binary_tree[get_heap_parent(current_index)]->row,
           my_heap->binary_tree[get_heap_parent(current_index)]->col,
           my_heap->binary_tree[current_index]->row, my_heap->binary_tree[current_index]->col);

    // Heapify up from the newly inserted node
    while (current_index != 0 &&
           my_heap->binary_tree[get_heap_parent(current_index)]->f_cost >
           my_heap->binary_tree[current_index]->f_cost) {
        // Print swap details
        DEBUG_MSG("DEBUG(insert_heap_node): Swapping nodes: index %d (f_cost=%lf) and parent index %d (f_cost=%lf)\n",
               current_index,
               my_heap->binary_tree[current_index]->f_cost,
               get_heap_parent(current_index),
               my_heap->binary_tree[get_heap_parent(current_index)]->f_cost);

        // Swap current node with its parent
        node *temp = my_heap->binary_tree[current_index];
        my_heap->binary_tree[current_index] = my_heap->binary_tree[get_heap_parent(current_index)];
        my_heap->binary_tree[get_heap_parent(current_index)] = temp;

        // Update current index to parent
        current_index = get_heap_parent(current_index);
    }

    // Final status after sorting
    DEBUG_MSG("DEBUG(insert_heap_node): Heapify complete. Current node at index %d with f_cost=%lf\n",
           current_index, my_heap->binary_tree[current_index]->f_cost);
    print_heap_binary(my_heap);
}
