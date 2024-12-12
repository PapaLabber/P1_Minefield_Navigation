// PURPOSE: sorting mines (vertices) to travel to from first to last

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <math.h>
#include "../function-library.h"


// Finding odd degree of vertices

void odd_degree_nodes(node* mst) {
    // Generate the MST using Prim's algorithm

    for (int i = 0; i < NUMBER_OF_MINES; i++) {
        printf("(%d, %d) ", mst[i].col, mst[i].row);
    }

    printf("poop\n");

    prim_algorithm(mst);


    printf("\n\nDette er indenfor Cristo!\n");
    for (int i = 1; i < NUMBER_OF_MINES; i++) {
        printf("(%d %d) ", mst[i].previous_mine->col, mst[i].previous_mine->row);
    }


    printf("\n\nDette er indenfor Cristo anden print\n");
    for (int i = 0; i < NUMBER_OF_MINES; i++) {
        printf("(%d %d) ", mst[i].col, mst[i].row);
    }

    printf("\n\n");

    for (int i = 0; i < NUMBER_OF_MINES; i++) {
        printf("mine [%d] antal børn: %d\n",i, mst[i].mine_child);
    }


    printf("\n\n");


}

void christofides_test() {

    node* mst = malloc(NUMBER_OF_MINES * sizeof(node));

    node mine_1, mine_2, mine_3, mine_4, mine_5, mine_6, mine_7, mine_8, mine_9, mine_10, mine_31;
    mine_1.row = 0,mine_2.row = 2, mine_3.row = 5, mine_4.row = 1, mine_5.row = 2, mine_6.row = 4, mine_7.row = 7, mine_8.row = 1, mine_9.row = 8, mine_10.row = 0,  mine_31.row = 4;
    mine_1.col = 0,mine_2.col = 3, mine_3.col = 6, mine_4.col = 6, mine_5.col = 8, mine_6.col = 5, mine_7.col = 5, mine_8.col = 11, mine_9.col = 2, mine_10.col = 1, mine_31.col = 0;

    node mines[NUMBER_OF_MINES] = {
        mine_1, mine_2, mine_3, mine_4, mine_5, mine_6, mine_7, mine_8, mine_9, mine_10, mine_31
    };

    for (int i = 0; i < NUMBER_OF_MINES; i++) {
        mst[i] = mines[i];
    }

    odd_degree_nodes(mst);

    printf("\n\nballs deep");
}

