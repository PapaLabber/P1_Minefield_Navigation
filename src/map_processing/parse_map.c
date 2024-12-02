#include <stdio.h>
#include <stdlib.h>


int parse_map(int* rows, int* columns, int array) {
    //allokere plads til matrixen
    cell_værdi **matrix = (cell_værdi **) malloc(*rows * sizeof(cell_værdi *)); //allokere plads til rows
     if(matrix == NULL) {
        printf("Allokeringsfejl ved Matrix");
        exit(EXIT_FAILURE);
    }
    for (int i = 0; i < *rows; i++) {
        matrix[i] = (cell_værdi *) malloc(*columns * sizeof(cell_værdi)); //allokere plads til coloumns
        if (matrix == NULL) {
            printf("allokeringsfejl");
            exit(EXIT_FAILURE);
        }
    }
    //fylder matrixen med værdier fra read_map array
    cell_værdi array[]; // den får jeg vel fra Thor right?
    int k = 0;
    int array_size = sizeof(array[10]) / sizeof(array[0]);
    for (int i = 0; i < *rows && k < array_size; i++) {
        for (int j = 0; j < *columns; j++) {
            matrix[i][j] = array[k];
            k++;
        }
    }
    //print for sjov skyld
    /*for (int i = 0; i < *rows; i++) {
        for (int j = 0; j < *columns; j++) {
            printf("(%4d, %4d, %4d)", matrix[i][j].mine, matrix[i][j].height, matrix[i][j].obstacle);
        }
        printf("\n");
    }*/
    //This is needed at somepoint
    for (int i = 0; i < *rows; i++) {
        free(matrix[i]);
    }
    free(matrix);
    return 0;
}

