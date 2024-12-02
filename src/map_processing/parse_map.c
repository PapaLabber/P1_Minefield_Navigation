#include <stdio.h>
#include <stdlib.h>
#include <time.h>
typedef struct {
    int mine;
    int height;
    int obstacle;
}cell_værdi;

//mangler indlæsning af read_file data og returnering af output

void random_cr(int* rows, int* coloumns); //prototype af funktion til randomize tal
int try_parse_map(void) {
    //Jeg håber at vi får data på rows og columns på sam
    int rows;
    int columns;
    random_cr(&rows, &columns);
    //allokore plads til matrixen
    cell_værdi*** matrix = (cell_værdi***)malloc(rows * sizeof(cell_værdi**)); //allokere plads til rows
    for(int i = 0; i < rows; i++) {
        matrix[i] = (cell_værdi**)malloc(columns * sizeof(cell_værdi**)); //allokere plads til coloumns
        for(int j = 0; j < columns; j++) {
            matrix[i][j] = (cell_værdi*)malloc(sizeof(cell_værdi));
        }
    }
    //fylder matrixen med værdier
    for(int i = 0; i < rows; i++) {
        for(int j = 0; j < columns; j++) {
            matrix[i][j]->mine = i * columns + j;
            matrix[i][j]->height = i * columns + j * 2;
            matrix[i][j]->obstacle = i * columns + j * 3;
        }
    }

    //Test print for sjov skyld
    for(int i = 0; i < rows; i++) {
        for(int j = 0; j < columns; j++) {
            printf("(%4d, %4d, %4d)",matrix[i][j]->mine,matrix[i][j]->height, matrix[i][j]->obstacle);
        }
        printf("\n");
    }


    for(int i = 0; i < rows; i++) {
        for(int j = 0; j < columns; j++) {
            free(matrix[i][j]);
        }
        free(matrix[i]);
    }
    free(matrix);
    return matrix; // ikke færdigt
}
//test
void random_cr(int* rows, int* coloumns) {

    srand(time(NULL));
    *rows = rand() % 16 + 5 ;
    *coloumns = rand() % 16 + 5;
}