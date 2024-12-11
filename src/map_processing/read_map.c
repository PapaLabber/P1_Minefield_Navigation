#include "../function-library.h"
#include <stdio.h>
#include <stdlib.h>

/* Implementering af funktion som læser kort data fra fil og gemmer det i et array af structs */
cell* read_map_from_file (const char* file, int* rows, int* columns, int* num_cells) {
    /* Først åbnes filen i læse mode */
    FILE* local_file = fopen(file, "r");

    /* Kontrol om filen kan åbnes */
    if (local_file == NULL) {
        printf("Error - read_map: File could not be opened...\n");
        exit (EXIT_FAILURE);
    }
    DEBUG_MSG("Debug - read_map: File opened successfully: %s\n", file);

    /* Læsning af dimensioner */
    fscanf(local_file, "%d %d", rows, columns);
    DEBUG_MSG("Debug - read_map: Read rows = %d, columns = %d\n", *rows, *columns);

    /* Udregning af total antal celler */
    *num_cells = *rows * *columns;
    DEBUG_MSG("Debug - read_map: Number of cells calculated = %d\n", *num_cells);

    /* Allokering af hukommelse til cell array, som indeholder data fra kort */
    cell* cell_array = malloc(*num_cells * sizeof(cell));

    /* Kontrol om hukommelse til cell array kunne allokeres */
    if (cell_array == NULL) {
        printf("Error - read_map: Memory allocation for cell array failed...\n<");
        exit (EXIT_FAILURE);
    }

    /* Indlæsning af hver celle */
    for (int i = 0; i < *num_cells; i++) {
            if (fscanf(local_file, "%d %d %d",
                    &cell_array[i].obstacle,
                    &cell_array[i].terrain,
                    &cell_array[i].mine) != 3) {
                printf("Error - read_map: Failed to read cell %d\n", i);
                free(cell_array);
                fclose(local_file);
                exit (EXIT_FAILURE);
            }
            DEBUG_MSG("Debug - read_map: cell_array[%d] = (%d, %d, %d)\n",
                i, cell_array[i].obstacle, cell_array[i].terrain, cell_array[i].mine);
    }

    /* Til slut lukkes filen, og den tomme matrix returneres fra funktionen */
    fclose(local_file);
    DEBUG_MSG("Debug - read_map: File closed successfully\n");
    return cell_array;
}

void read_map_test() {
    int rows, columns, num_cells;

    /* Kald af read_map_from_file funktionen */
    cell* cell_array = read_map_from_file("map.txt", &rows, &columns, &num_cells);

    /* Tjek af dimensioner og antal celler */
    printf("Test/read_map - Dimensions: rows = %d, columns = %d, num_cells = %d\n",
        rows, columns, num_cells);

    /* Verificering af data i hver celle */
    for (int i = 0; i < num_cells; i++) {
        printf("Test/read_map - Cell array[%d] = (%d, %d, %d)\n",
            i, cell_array[i].obstacle, cell_array[i].terrain, cell_array[i].mine);
    }

    /* Frigørelse af allokeret hukommelse */
    free(cell_array);
    printf("Test/read_map - Memory of cell array freed successfully\n");
}

