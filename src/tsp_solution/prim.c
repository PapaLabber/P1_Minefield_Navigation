// PURPOSE: calculate minimum-spanning tree (MST) for christofides.c to use

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

/*
int find_cheapest(double two_d_array[NUMBER_OF_MINES][NUMBER_OF_MINES], int runs, int from_mine, int to_mine) {
    int cheapest = INT_MAX;
    int list_of_visited_edges[NUMBER_OF_MINES];

    for (to_mine = 0; to_mine < runs; to_mine++) { // if mine at new index is not 0 and cheaper than previous cheapest mine, reassign
        int is_in_array = 0;

        if (two_d_array[from_mine][to_mine] < cheapest && two_d_array[from_mine][to_mine] != 0)

            for(int j = 0; j < sizeof(list_of_visited_edges[j]); j++) {
                if(list_of_visited_edges[j] == to_mine)
                    is_in_array = 1;
            }

            if (is_in_array == 0)
                cheapest = two_d_array[from_mine][to_mine];
    }

    return cheapest;
}

void prim_algorithm(node grid[NUMBER_OF_MINES], double mine_distances[NUMBER_OF_MINES][NUMBER_OF_MINES]) {
    // calculate edge weights
    calculate_edge_weights(grid);

    // find the cheapest edge
    for (int from_mine = 0; from_mine < NUMBER_OF_MINES; from_mine++) {
        for (int to_mine = 0; to_mine < NUMBER_OF_MINES; to_mine++) {
            int cheapest_edge = find_cheapest(mine_distances, NUMBER_OF_MINES, from_mine, to_mine);
            printf("From mine %d to mine %d: [%d] is the cheapest edge with weight [%d].\n", from_mine, to_mine, cheapest_edge, 4); // 4 = placeholder
        }
    }
}

*/

int find_cheapest(double mine_distances[NUMBER_OF_MINES][NUMBER_OF_MINES], int number_of_visited_mines, node visited_mines[NUMBER_OF_MINES], node mines[NUMBER_OF_MINES]) {

    // brug visited mines og kør den igennem da vi allerede ved at de miner der er i den er visited

    int cheapest = INT_MAX;
    int temp_p = 0;

    for (int from_mine = 0; from_mine < number_of_visited_mines; from_mine++) { // Decides how many times it should run
        for (int p = 0; p < NUMBER_OF_MINES; p++) { // Checks all mines
            int not_visited = 0;

            for (int i = 0; i < number_of_visited_mines; i++) { // Checks if the mines is already visited
                if (mines[p].col != visited_mines[i].col && mines[p].row != visited_mines[i].row) {
                    not_visited = 1;
                }
            }

            if (not_visited == 1) {
                // double temp_dist = calculate_distance(visited_mines[from_mine], mines[p]);
                double temp_dist = mine_distances[from_mine][p];
                if (temp_dist < cheapest && temp_dist != 0) {
                    cheapest = temp_dist;
                    /*
                    if (number_of_visited_mines == NUMBER_OF_MINES - 1) {
                        printf("DEBUG: accessing beyond array bounds");
                        exit(EXIT_FAILURE);
                    }
                    */
                    visited_mines[number_of_visited_mines + 1] = mines[p];
                    temp_p = p;
                }
            }
        }
    }

    return cheapest;
}

void prim_algorithm(node array_of_mines[NUMBER_OF_MINES]) {
    // create visited list
    int number_of_visited_mines = 0;
    node visited_mines[NUMBER_OF_MINES];
    visited_mines[0] = array_of_mines[0];
    int mst[NUMBER_OF_MINES];

    // calculate distance from first mine to every other mine
    calculate_edge_weights(array_of_mines);

    // find the cheapest edge from first mine to another mine

    for (int i = 0; i < NUMBER_OF_MINES-2; i++) {
        number_of_visited_mines++;

        mst[i] = find_cheapest(mine_distances, number_of_visited_mines, visited_mines, array_of_mines);

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