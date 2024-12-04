#include <stdio.h>
#include <stdio.h>
#include <string.h>
#include <math.h>
#include <stdlib.h>
#include <stdbool.h>
#include <float.h>
#include "min_heap.c"

#define GRID_ROW 9 // # rows in the grid we'll traverse (effectively the height)
#define GRID_COL 9 // # columns in the grid we'll traverse (effectively the width)

/*
 * these are out-commented for now
 * I don't know how to incorporate them in the algorithm yet
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
*/

typedef struct { // a struct Pair with ints representing rows (formerly first) and columns (formerly second)
    int row;
    int col;
} Pair;

typedef struct { // previously "first" and "second", manages cost of node
    double cost;
    Pair pair ;
} pPair;

typedef struct { // previously "Cell", manges parents of node
    int parent_i, parent_j;
    double f, g, h;
} Node;

typedef struct { //
    pPair *array;
    int size;
    int capacity;
} MinHeap;

bool isValid(Pair node) { // is node within grid boundaries? (compares node coords with grid dimensions)
    return (node.row >= 0) && (node.row < GRID_ROW) && (node.col >= 0) && (node.col < GRID_COL);
}

bool isUnBlocked(int grid[GRID_ROW][GRID_COL], Pair node) { // is node unblocked? (checks node value)
    return (grid[node.row][node.col] == 1);
}

bool isDestination(Pair node, Pair dest) { // has dest been reached? (compare coords)
    return (node.row == dest.row && node.col == dest.col);
}

int calculateHeuristic(Pair node, Pair dest) { // heuristic function estimating distance to destination
    return abs(node.row - dest.row) + abs(node.col - dest.col); // using Manhattan distance
}

void aStarSearch(int grid[GRID_ROW][GRID_COL], Pair start, Pair dest) {
    // are both start and dest valid?
    if (!isValid(start) == 1) {
        printf("ERROR: Start node is invalid.");
        exit(EXIT_FAILURE);
    } else if (!isValid(dest)) {
        printf("ERROR: Destination node is invalid.");
        exit(EXIT_FAILURE);
    }

    // are both start and dest unblocked?
    if (!isUnBlocked(grid, start)) {
        printf("ERROR: Start node is blocked.");
        exit(EXIT_FAILURE);
    } else if (!isUnBlocked(grid, dest)) {
        printf("ERROR: Destination node is blocked.");
        exit(EXIT_FAILURE);
    }

    // are start and dest different?
    if (!isDestination(start, dest)) {
        printf("ERROR: The start and destination are the same.");
        exit(EXIT_FAILURE);
    }

    bool closedList[GRID_ROW][GRID_COL]; // a list of closed nodes, none are closed yet
    memset(closedList, false, sizeof(closedList));

    Node nodeDetails[GRID_ROW][GRID_COL]; // details regarding a node
    for (int i = 0; i < GRID_ROW; i++) {
        for (int j = 0; j < GRID_COL; j++) {
            nodeDetails[i][j].f = FLT_MAX;
            nodeDetails[i][j].g = FLT_MAX;
            nodeDetails[i][j].h = FLT_MAX;
            nodeDetails[i][j].parent_i = -1;
            nodeDetails[i][j].parent_j = -1;
        }
    }

    int i = start.row, j = start.col;
    nodeDetails[i][j].f = 0.0;
    nodeDetails[i][j].g = 0.0;
    nodeDetails[i][j].h = 0.0;
    nodeDetails[i][j].parent_i = i;
    nodeDetails[i][j].parent_j = j;

    MinHeap openList;
    openList.array = (pPair *)malloc(sizeof(pPair) * GRID_ROW * GRID_COL);
    openList.size = 0;
    openList.capacity = GRID_ROW * GRID_COL;

    insertHeap(&openList, (pPair){0.0, start}); // insertHeap ->

    bool foundDest = false;

    while (openList.size > 0) {

    }


    if (!foundDest) {
        printf("Failed to find a path to the Destination node.\n");
    }

    free(openList.array);
}

int main() {
    int grid[GRID_ROW][GRID_COL] = {
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

    Pair start = {0, 0};
    Pair dest = {8, 8};

    aStarSearch(grid, start, dest);

    return 0;
}