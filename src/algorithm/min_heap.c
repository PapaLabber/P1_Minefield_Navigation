#include <stdio.h>
#include <stdio.h>
#include <string.h>
#include <math.h>
#include <stdlib.h>
#include <stdbool.h>


typedef enum is_mine {
    no_mine,
    MRUD,
    PMA2,
    PMA3,
    PROM1
} is_mine;

typedef enum is_obstacle {
    no_obstacle,
    tree,
    stone,
    bush,
    tripwire,
    deep_water
} is_obstacle;


typedef struct node {
    int x, y;                    // Koordinater
    int g_cost;                  // Omkostning fra startnoden til denne node
    int h_cost;                  // Omkostningen fra denne node til mål
    int f_cost;                  // Summen af g_cost og h_cost (f_cost = g_cost + h_cost)
    struct node* parent;         // Pointer til forælder-node for sti-rekonstruktion
    is_obstacle obstacle_type;   // Obstacle type / Ingen obstacle == 0
    is_mine mine_type;           // Minetype / Ingen mine == 0
     // int elevation;           // Højden for en given celle
    int blast_radius;            // Ekstra felt til at angive risiko-niveau (f.eks. miner: højere værdi)
} node;

typedef struct min_heap {
    node** arr;                  // Array af node pointers
    int size;                    // Current size of heap
    int capacity;                // Max capacity of the heap
} min_heap;

// Prototyper
min_heap* heapify(min_heap* heap, int index);


/* min_heap til open list */

// Hjælpe funktioner til at lave min_heap
int parent(int index) {
    //index of parent node
    return (index - 1) / 2;
}

int lchild(int index) {
    // Index of left child node
    return 2 * index + 1;
}

int rchild(int index) {
    // Index of left child node
    return 2 * index + 2;
}

int get_min (min_heap* heap) {
    // Return root node, since it is min
    return heap->arr[0];
}

min_heap* initialise_min_heap(int capacity) {
    min_heap* heap = (min_heap*) calloc (1, sizeof(min_heap));
    heap->arr = (node**) calloc(capacity, sizeof(node*));
    heap->size = 0;
    heap->capacity = capacity;
    return heap;
}

void free_minheap(min_heap* heap) {
    if(heap == NULL) {
        return;
    }
    free(heap->arr);
    free(heap);
}

min_heap* insert_min_heap(min_heap* heap, node* element) {
    if(heap->size == heap->capacity) {
        fprintf("Heap is already full!\n", element); // mangler fil "fil,"
        return heap;
    }
    heap->size++;
    heap->arr[heap->size - 1] = element;

    //Swap to get root
    int current = heap->size - 1;

    while(current > 0 && heap->arr[parent(current)]->f_cost > heap->arr[current]->f_cost) {
        node* temp = heap->arr[parent(current)];
        heap->arr[parent(current)] = heap->arr[current];
        heap->arr[current] = temp;
        current = parent(current);
    }
    return heap;
}


min_heap* find_minimum(min_heap* heap) {

    // Find minimum element, at the root
    if (!heap || heap->size == 0) {
        return heap;
    }
    // Min is always at the root and move last element to the root
    node* min_node = heap->arr[0];
    heap->arr[0] = heap->arr[heap->size - 1];
    heap->size--;

    // Call heapify function, to maintain the min-heap property
    heap = heapify(heap, 0);
    return find_minimum;
}

// Priority que
min_heap* heapify(min_heap* heap, int index) {
    // Rearrage heap to maintain minheap properties

    if(heap->size <= 1) {
        return heap;
    }

    int left = lchild(index);
    int right = rchild(index);

    // Variable to get smallest element in substree of an element in index
    int smallest = index;

    // If the left child is smaller than this element, it is the smallest
    if (left < heap->size && heap->arr[left]->f_cost < heap->arr[smallest]->f_cost) {
        smallest = left;
    }

    // If the child child is smaller than this element, it is the smallest
    if (right < heap->size && heap->arr[right]->f_cost < heap->arr[smallest]->f_cost) {
        smallest = right;
    }


    // If root is not the smallest, swap and heapify recursively until we reach the smallest rode node
    if(smallest != index) {
    node* temp = heap->arr[index];
    heap->arr[index] = heap->arr[smallest];
    heap->arr[smallest] = temp;
    heap = heapify(heap, smallest);
    }

    return heap;
}