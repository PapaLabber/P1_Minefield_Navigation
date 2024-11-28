#include <stdio.h>
#include <stdio.h>
#include <string.h>
#include <math.h>
#include <stdlib.h>


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
    min_heap* minheap = (min_heap*) calloc (1, sizeof(min_heap));
    minheap->arr = (int*) calloc(capacity, sizeof(int));
    minheap->size = 0;
    minheap->capacity = capacity;
    return minheap;
}

void free_minheap(min_heap* heap) {
    if(heap == NULL) {
        return;
    }
    free(heap->arr);
    free(heap);
}

min_heap* insert_minheap(min_heap* heap, int element) {
    if(heap->size == heap->capacity) {
        fprintf("Heap is already full!\n", element); // mangler fil "fil,"
        return heap;
    }
    heap->size++;
    heap->arr[heap->size - 1] = element;

    //Swap to get root
    int current = heap->size - 1;

    while(current > 0 && heap->arr[parent(current)]) {
        int temp = heap->arr[parent(current)];
        heap->arr[parent(current)] = heap->arr[current];
        heap->arr[current] = temp;
        current = parent(current);
    }
    return heap;
}
