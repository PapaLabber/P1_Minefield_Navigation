#include <stdio.h>
#include <string.h>
#include <math.h>
#include <stdlib.h>
#include <stdbool.h>
#include <float.h>
//#include "min_heap.c"
#include "../function-library.h"

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

/*
 * these are out-commented for now, mostly to test the node struct
typedef struct { // a struct Pair with ints representing rows (formerly first) and columns (formerly second)
    int row;
    int col;
} Pair;

typedef struct { // previously "first" and "second", manages cost of node
    double cost; // might be able to be an int
    Pair pair;
} pPair;

typedef struct { // previously "Cell", manges parents of node
    int parent_i, parent_j; // parents of node
    double f, g, h; // cost of node
} Node;
*/

bool isValid(node valid_node) { // is node within grid boundaries? (compares node coords with grid dimensions) ---- Pair -> node
    return (valid_node.row >= 0) && (valid_node.row < GRID_ROW) && (valid_node.col >= 0) && (valid_node.col < GRID_COL);
}

bool isUnBlocked(int grid[GRID_ROW][GRID_COL], node unblocked_node) { // is node unblocked? (checks node value) ---- Pair -> node
    return (grid[unblocked_node.row][unblocked_node.col] == 1);
}

bool isDestination(node is_dest_node, node destination) { // has destination been reached? (compare coords) ---- Pair -> node
    return (is_dest_node.row == destination.row && is_dest_node.col == destination.col);
}

int calculateHeuristic(node current_node, node destination) { // heuristic function estimating distance to destination ---- Pair -> node
    return abs(current_node.row - destination.row) + abs(current_node.col - destination.col); // using Manhattan distance
}

void aStarSearch(int grid[GRID_ROW][GRID_COL], node start, node destination) { // Pair -> node
    // are both start and destination valid?
    if (!isValid(start) == 1) {
        printf("ERROR: Start node is invalid.");
        exit(EXIT_FAILURE);
    } else if (!isValid(destination)) {
        printf("ERROR: Destination node is invalid.");
        exit(EXIT_FAILURE);
    }

    // are both start and destination unblocked?
    if (!isUnBlocked(grid, start)) {
        printf("ERROR: Start node is blocked.");
        exit(EXIT_FAILURE);
    } else if (!isUnBlocked(grid, destination)) {
        printf("ERROR: Destination node is blocked.");
        exit(EXIT_FAILURE);
    }

    // are start and destination different?
    if (!isDestination(start, destination)) {
        printf("ERROR: The start and destinationination are the same.");
        exit(EXIT_FAILURE);
    }

    bool closedList[GRID_ROW][GRID_COL]; // a list of closed nodes, none are closed yet
    memset(closedList, false, sizeof(closedList));

    node nodeDetails[GRID_ROW][GRID_COL]; // details regarding a node ---- Node -> node
    for (int i = 0; i < GRID_ROW; i++) {
        for (int j = 0; j < GRID_COL; j++) {
            nodeDetails[i][j].f_cost = FLT_MAX; // initial cost infinite, not looked at yet
            nodeDetails[i][j].g_cost = FLT_MAX;
            nodeDetails[i][j].h_cost = FLT_MAX;
            nodeDetails[i][j].parent_i = -1; // no parent assigned yet
            nodeDetails[i][j].parent_j = -1;
        }
    }

    int i = start.row, j = start.col; // initialize start node
    nodeDetails[i][j].f_cost = 0.0;
    nodeDetails[i][j].g_cost = 0.0;
    nodeDetails[i][j].h_cost = 0.0;
    nodeDetails[i][j].parent_i = i;
    nodeDetails[i][j].parent_j = j;

    min_heap openList; // MinHeap -> min_heap
    openList.arr = (node *)malloc(sizeof(node) * GRID_ROW * GRID_COL); // pPair -> node
    openList.size = 0;
    openList.capacity = GRID_ROW * GRID_COL;



    insert_min_heap(&openList, start); // insertHeap -> insert_min_heap

    bool foundDest = false;

    while (openList.size > 0) {
        node current = find_minimum(&openList); // extractMin -> find_minimum ---- pPair -> node
        i = current.pair.row;
        j = current.pair.col;
        closedList[i][j] = true;

        double gNew, hNew, fNew;

        int rowOffsets[] = {-1, 1, 0, 0, -1, -1, 1, 1};
        int colOffsets[] = {0, 0, 1, -1, -1, 1, -1, 1};
        int moveCosts[] = {1, 1, 1, 1, 2, 2, 2, 2};

        for (int d = 0; d < 8; d++) {
            node adjacent; // Pair -> node

            adjacent.row = i + rowOffsets[d];
            adjacent.col = j + colOffsets[d];

            if (isValid(adjacent)) {
                if (isDestination(adjacent, destination)) {
                    nodeDetails[adjacent.row][adjacent.col].parent_i = i;
                    nodeDetails[adjacent.row][adjacent.col].parent_j = j;
                    printf("The destination node has been found!\n");
                    tracePath(nodeDetails, destination); // awaiting tracePath program
                    foundDest = true;
                    free(openList.arr);
                    return;
                } else if (!closedList[adjacent.row][adjacent.col] && isUnBlocked(grid, adjacent)) {
                    gNew = nodeDetails[i][j].g_cost + moveCosts[d];
                    hNew = calculateHeuristic(adjacent, destination);
                    fNew = gNew + hNew;

                    if (nodeDetails[adjacent.row][adjacent.col].f_cost == FLT_MAX || nodeDetails[adjacent.row][adjacent.col].f_cost > fNew) {
                        insert_min_heap(&openList, (node){fNew, adjacent});  // pPair -> node
                        nodeDetails[adjacent.row][adjacent.col].f_cost = fNew;
                        nodeDetails[adjacent.row][adjacent.col].g_cost = gNew;
                        nodeDetails[adjacent.row][adjacent.col].h_cost = hNew;
                        nodeDetails[adjacent.row][adjacent.col].parent_i = i;
                        nodeDetails[adjacent.row][adjacent.col].parent_j = j;
                    }
                }
            }
        }
    }


    if (!foundDest) {
        printf("Failed to find a path to the Destination node.\n");
    }

    free_min_heap(openList.arr); //
}

int test_aStar(void) {
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

    node start = {0, 0}; // Pair -> node
    node destination = {8, 8}; // Pair -> node

    aStarSearch(grid, start, destination);

    return 0;
}