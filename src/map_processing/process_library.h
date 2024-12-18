
#ifndef PROCESS_LIBRARY_H
#define PROCESS_LIBRARY_H
#include "../general-library.h"

// read_map function prototype
node* read_map_from_file (const char* file, int* map_rows, int* map_cols, int* num_cells);

// parse_map function prototype
node** parse_map(const int map_rows, const int map_cols, const node* read_map_array, const int num_cells);

// post_process function prototype
node* list_mines(int map_rows, int map_cols, node **matrix, int *mine_arr_index);

void add_danger_zone(int map_rows, int map_cols, node **matrix, node *list_of_mines, int *mine_arr_index);

node* process_map(int map_rows, int map_cols, node **matrix, int* mine_arr_index);

void prepare_map(node **input_map, int map_cols, int map_rows);

#endif //PROCESS_LIBRARY_H
