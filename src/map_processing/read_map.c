#include "../general-library.h"
#include <stdio.h>
#include <stdlib.h>

/* Implementering af funktion som læser kort data fra fil og gemmer det i et array af structs */
node* read_map_from_file (const char* file, int* rows, int* columns, int* num_nodes) {
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

    /* Udregning af total antal nodes */
    *num_nodes = *rows * *columns;
    DEBUG_MSG("Debug - read_map: Number of nodes calculated = %d\n", *num_nodes);

    /* Allokering af hukommelse til node array, som indeholder data fra kort */
    node* node_array = calloc((*num_nodes), sizeof(node));

    /* Kontrol om hukommelse til node array kunne allokeres */
    if (node_array == NULL) {
        printf("Error - read_map: Memory allocation for node array failed...\n<");
        exit (EXIT_FAILURE);
    }

    /* Indlæsning af hver node */
    for (int i = 0; i < *num_nodes; i++) {
            if (fscanf(local_file, "%d %d %d",
                    &node_array[i].obstacle_type,
                    &node_array[i].terrain,
                    &node_array[i].mine_type) != 3) {
                printf("Error - read_map: Failed to read node %d\n", i);
                free(node_array);
                fclose(local_file);
                exit (EXIT_FAILURE);
            }
            DEBUG_MSG("Debug - read_map: node_array[%d] = (%d, %d, %d)\n",
                i, node_array[i].obstacle_type, node_array[i].terrain, node_array[i].mine_type);
    }

    /* Til slut lukkes filen, og den tomme matrix returneres fra funktionen */
    fclose(local_file);
    DEBUG_MSG("Debug - read_map: File closed successfully\n");
    return node_array;
}

void read_map_test() {
    int rows, columns, num_nodes;

    /* Kald af read_map_from_file funktionen */
    node* node_array = read_map_from_file("map.txt", &rows, &columns, &num_nodes);

    /* Tjek af dimensioner og antal nodes */
    printf("Test/read_map - Dimensions: rows = %d, columns = %d, num_nodes = %d\n",
        rows, columns, num_nodes);

    /* Verificering af data i hver node */
    for (int i = 0; i < num_nodes; i++) {
        printf("Test/read_map - node array[%d] = (%d, %d, %d)\n",
            i, node_array[i].obstacle_type, node_array[i].terrain, node_array[i].mine_type);
    }

    /* Frigørelse af allokeret hukommelse */
    free(node_array);
    printf("Test/read_map - Memory of node array freed successfully\n");
}

