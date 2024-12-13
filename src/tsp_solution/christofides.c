// PURPOSE: sorting mines (vertices) to travel to from first to last

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <math.h>
#include "../function-library.h"


// Finding odd degree of vertices

void odd_degree_nodes(node* mst) {
    // Generate the MST using Prim's algorithm
    int temp_index = 0;
    int odd_edge_count = 0;

    prim_algorithm(mst);


    // runs a for loop that decides how big our odd_degree_nodes is gonna be.
    for (int i = 0; i < NUMBER_OF_MINES; i++) {
        if (i == 0) {
            mst[i].edge_counter = mst[i].mine_child;
        } else
            mst[i].edge_counter = mst[i].mine_child + 1;

        if (mst[i].edge_counter % 2 == 1) {
            odd_edge_count++;
            printf("odd_edge_count is %d\n", odd_edge_count);
        }
    }

    // Making a node list, that have all of the nodes that have odd edges.
    node odd_degree_nodes[odd_edge_count];

    for (int i = 0; i < NUMBER_OF_MINES; i++) {
        // Only nodes with odd edges go through the if-statement.
        if (mst[i].edge_counter % 2 == 1) {
            printf("temp_index is %d\n", temp_index);
            odd_degree_nodes[temp_index]= mst[i];
            temp_index++;
        }
    }

    // if from mine or to mine is in visited break (gør så at de ikke kan bruges igen lige så snart de har fundet en makker)

    // Den skal vælge imellem dens children med hvilken en er kortest, og derfeter tage den rute.
    // hvis den kun har en child skal den vælge den !HVIS! child ikke er i visited list, ellers skal den finde den mine der er tættest på.
    // Så vi kører fra start punktet putter den i close list, derefter køre vi parametrene fra oven, indtil der ikke er flere noder tilbage.


    printf("\n\n");

    printf("The nodes edges: \n");
    for (int i = 0; i < (NUMBER_OF_MINES); i++) {
        printf("%d ", mst[i].edge_counter);
    }

    printf("\n\n");


    printf("Odd degree nodes: \n");
    for (int i = 0; i < odd_edge_count; i++) {
        printf("(%d %d) ", odd_degree_nodes[i].col, odd_degree_nodes[i].row);
    }


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

    node mine_1, mine_2, mine_3, mine_4, mine_5, mine_6, mine_7, mine_8, mine_9, mine_10;
    mine_1.row = 0,mine_2.row = 2, mine_3.row = 5, mine_4.row = 1, mine_5.row = 2, mine_6.row = 4, mine_7.row = 7, mine_8.row = 1, mine_9.row = 8, mine_10.row = 0;
    mine_1.col = 0,mine_2.col = 3, mine_3.col = 6, mine_4.col = 6, mine_5.col = 8, mine_6.col = 5, mine_7.col = 5, mine_8.col = 11, mine_9.col = 2, mine_10.col = 1;

    node mines[NUMBER_OF_MINES] = {
        mine_1, mine_2, mine_3, mine_4, mine_5, mine_6, mine_7, mine_8, mine_9, mine_10
    };

    for (int i = 0; i < NUMBER_OF_MINES; i++) {
        mst[i] = mines[i];
    }

    odd_degree_nodes(mst);

    printf("\n\nballs deep");
}

