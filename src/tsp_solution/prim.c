// PURPOSE: calculate minimum-spanning tree (MST) for christofides.c to use

#include <float.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "../function-library.h"

double calculate_distance(node current_node, node destination_node) {
    return sqrt(pow((current_node.row - destination_node.row),2) + pow((current_node.col - destination_node.col),2));
} // sqrt((x_1 - x_2)^2 + (y_1 - y_2)^2) // euclidean distance


void find_cheapest(int number_of_visited_mines, node visited_mines[NUMBER_OF_MINES], node mines[NUMBER_OF_MINES]) {

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
                    break;
                }
            }

            if (not_visited == 1) {
                double temp_dist = calculate_distance(visited_mines[from_mine], mines[p]);
                if (temp_dist < cheapest && temp_dist != 0) {
                    cheapest = temp_dist;
                    visited_mines[number_of_visited_mines] = mines[p];
                    temp_p = p;
                    from_mine_temp = from_mine;
                }
            }
        }
    }



    visited_mines[from_mine_temp].mine_child ++;

    printf("Number: %d mine found\n", number_of_visited_mines);

    printf("mine = (%d,%d) has: %d child(ren)\n", visited_mines[from_mine_temp].col, visited_mines[from_mine_temp].row, visited_mines[from_mine_temp].mine_child);

    printf("distance = %lf, from_mine = (%d,%d), temp_p = (%d,%d).\n", cheapest, visited_mines[from_mine_temp].col, visited_mines[from_mine_temp].row, mines[temp_p].col, mines[temp_p].row);

    mines[temp_p].previous_mine = &visited_mines[from_mine_temp];
    visited_mines[number_of_visited_mines].previous_mine = &visited_mines[from_mine_temp];


    printf("parent to mine (%d, %d) is (%d, %d)\n",mines[temp_p].col, mines[temp_p].row, mines[temp_p].previous_mine->col, mines[temp_p].previous_mine->row);
}

node* prim_algorithm(node* array_of_mines) {
    // create visited list
    int number_of_visited_mines = 0;
    node visited_mines[NUMBER_OF_MINES];
    // sets all children to be 0
    for (int i = 0; i < NUMBER_OF_MINES; i++) {
        array_of_mines[i].mine_child = 0;
        array_of_mines[i].previous_mine = NULL;
    }


    visited_mines[0] = array_of_mines[0]; // add first mine to visited list

    for (int i = 0; i < NUMBER_OF_MINES - 1; i++) {
        number_of_visited_mines++;
        find_cheapest(number_of_visited_mines, visited_mines, array_of_mines);
    }

    for (int i = 0; i < NUMBER_OF_MINES; i++) {
        array_of_mines[i] = visited_mines[i];
    }


    printf("\n\n");

    for (int i = 1; i < NUMBER_OF_MINES; i++) {
        printf("(%d, %d) ", array_of_mines[i].previous_mine->col, array_of_mines[i].previous_mine->row);
    }
    /*

    printf("\n");
    printf("\n");
    for (int i = 0; i < NUMBER_OF_MINES; i++) {
        printf("mine = (%d,%d) has: %d child(ren)\n", visited_mines[i].col, visited_mines[i].row, visited_mines[i].mine_child);
    }

    for (int i = 1; i < NUMBER_OF_MINES; i++) {
        printf("parent to mine (%d, %d) is (%d, %d)\n",visited_mines[i].col, visited_mines[i].row, visited_mines[i].previous_mine->col, visited_mines[i].previous_mine->row);
    }
    */

    return array_of_mines;
}
