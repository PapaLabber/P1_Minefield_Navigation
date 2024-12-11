// PURPOSE: calculate minimum-spanning tree (MST) for christofides.c to use

#include <float.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "../function-library.h"

double calculate_distance(node current_node, node destination_node) {
    return sqrt(pow((current_node.row - destination_node.row),2) + pow((current_node.col - destination_node.col),2));
} // sqrt((x_1 - x_2)^2 + (y_1 - y_2)^2) // euclidean distance

double mine_distances[NUMBER_OF_MINES][NUMBER_OF_MINES];

void calculate_edge_weights(node mine_array[]) { // calculate edge weights from each mine to each other mine
    for (int from_mine = 0; from_mine < NUMBER_OF_MINES; from_mine++) {
        for (int to_mine = 0; to_mine < NUMBER_OF_MINES; to_mine++) {
            mine_distances[from_mine][to_mine] = calculate_distance(mine_array[from_mine], mine_array[to_mine]);
        }
    }
}

double find_cheapest(double mine_distances[NUMBER_OF_MINES][NUMBER_OF_MINES], int number_of_visited_mines, node visited_mines[NUMBER_OF_MINES], node mines[NUMBER_OF_MINES]) {

    // brug visited mines og kør den igennem da vi allerede ved at de miner der er i den er visited

    double cheapest = FLT_MAX;
    int from_mine_temp = 0;
    int temp_p = 0;

    for (int from_mine = 0; from_mine < number_of_visited_mines; from_mine++) { // Decide how many times it should run
        for (int p = 0; p < NUMBER_OF_MINES; p++) { // Check all mines
            int not_visited = 1;

            for (int i = 0; i < number_of_visited_mines; i++) { // Check if the mines are already visited
                if (mines[p].col == visited_mines[i].col && mines[p].row == visited_mines[i].row) {
                    not_visited = 0;
                }
            }

            if (not_visited == 1) {
                double temp_dist = calculate_distance(visited_mines[from_mine], mines[p]);
                //double temp_dist = mine_distances[from_mine][p];
                if (temp_dist < cheapest && temp_dist != 0) {
                    cheapest = temp_dist;
                    visited_mines[number_of_visited_mines] = mines[p];
                    temp_p = p;
                    from_mine_temp = from_mine;
                }
            }
        }
    }
    printf("distance = %lf, from_mine = (%d,%d), temp_p = (%d,%d).\n", cheapest, visited_mines[from_mine_temp].col, visited_mines[from_mine_temp].row, mines[temp_p].col, mines[temp_p].row);
    return cheapest;
}

void prim_algorithm(node array_of_mines[NUMBER_OF_MINES]) {
    // create visited list
    int number_of_visited_mines = 0;
    node visited_mines[NUMBER_OF_MINES];
    visited_mines[0] = array_of_mines[0]; // add first mine to visited list
    double mst[NUMBER_OF_MINES]; // initialize minimum-spanning tree
    // mst[0] = visited_mines[0];

    // calculate distance from first mine to every other mine
    calculate_edge_weights(array_of_mines);

    // find the cheapest edge from first mine to another mine

    for (int i = 0; i < NUMBER_OF_MINES-1; i++) {
        number_of_visited_mines++;

        mst[i] = find_cheapest(mine_distances, number_of_visited_mines, visited_mines, array_of_mines);
        printf("mst[%d] = %lf\n", i, mst[i]);
    }
}

void prim_test(void) {
    node mine_1, mine_2, mine_3, mine_4, mine_5, mine_6, mine_7, mine_8, mine_9, mine_10;
    mine_1.row = 0, mine_2.row = 2, mine_3.row = 5, mine_4.row = 1, mine_5.row = 2, mine_6.row = 4, mine_7.row = 7, mine_8.row = 1, mine_9.row = 8, mine_10.row = 0;
    mine_1.col = 0, mine_2.col = 3, mine_3.col = 6, mine_4.col = 6, mine_5.col = 8, mine_6.col = 5, mine_7.col = 5, mine_8.col = 11, mine_9.col = 2, mine_10.col = 1;

    node mines[NUMBER_OF_MINES] = {mine_1, mine_2, mine_3, mine_4, mine_5, mine_6, mine_7, mine_8, mine_9, mine_10};

    prim_algorithm(mines);

    printf("prim.c works\n");
}