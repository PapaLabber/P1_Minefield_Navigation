#include <stdio.h>
#include <math.h>
#include <limits.h>

#define ROW 10
#define COL 10

typedef struct {
    int rows, colls;
} Point;

// Funktion til at beregne den Euklidiske afstand mellem to punkter
double calculateDistance(Point p1, Point p2) {
    return sqrt((p1.rows - p2.rows) * (p1.rows - p2.rows) + (p1.colls - p2.colls) * (p1.colls - p2.colls));
}

// Funktion til at finde nærmeste mine, som ikke er besøgt
int findNearestMine(Point current, Point mines[], int numMines, int visited[]) {
    double minDistance = INT_MAX;
    int nearestMineIndex = -1;

    for (int i = 0; i < numMines; i++) {
        if (!visited[i]) { // Hvis minen ikke er besøgt
            double dist = calculateDistance(current, mines[i]);
            if (dist < minDistance) {
                minDistance = dist;
                nearestMineIndex = i;
            }
        }
    }

    return nearestMineIndex; // Returnerer indekset på nærmeste mine
}

// Dummy funktion til at simulere en pathfinding-algoritme
void findPath(Point start, Point end) {
    printf("Finding path from (%d, %d) to (%d, %d)\n", start.rows, start.colls, end.rows, end.colls);
    // Her vil du implementere en faktisk pathfinding-algoritme som A* eller Dijkstra
}

// Hovedfunktionen til at finde og gemme ruterne mellem start og minerne
void planRoutes(Point start, Point mines[], int numMines) {
    int visited[numMines]; // Holder styr på, om en mine er besøgt
    for (int i = 0; i < numMines; i++) {
        visited[i] = 0; // Initialiser til alle miner som ikke-besøgte
    }

    Point current = start; // Startpunktet
    for (int i = 0; i < numMines; i++) {
        int nearestMineIndex = findNearestMine(current, mines, numMines, visited);
        if (nearestMineIndex == -1) {
            break; // Ingen flere miner tilbage
        }

        // Find ruten til nærmeste mine
        findPath(current, mines[nearestMineIndex]);

        // Marker minen som besøgt
        visited[nearestMineIndex] = 1;

        // Opdater det nuværende punkt
        current = mines[nearestMineIndex];
    }

    // Til sidst, find ruten tilbage til start
    findPath(current, start);
}

void nearest_neighbor_test(void) {
    // Eksempeldata
    Point start = {0, 0}; // Startkoordinater
    Point mines[] = {{2, 3}, {5, 4}, {8, 1}}; // Minerkoordinater
    int numMines = sizeof(mines) / sizeof(mines[0]);

    // Kør programmet
    planRoutes(start, mines, numMines);
}
