#ifndef FUNCTION_LIBRARY_H
#define FUNCTION_LIBRARY_H

// Debug kontrol
#ifndef DEBUG
#define DEBUG 0
#endif

#if DEBUG
    #define DEBUG_MSG(fmt, ...) printf(fmt, ##__VA_ARGS__)
#else
    #define DEBUG_MSG(fmt, ...)
#endif

// Struct definition
typedef struct {
    int obstacle;
    int terrain;
    int mine;
} cell;

// Funktion prototyper
cell* read_map_from_file (const char* file, int* rows, int* columns, int* num_cells);
cell** parse_map(const int rows, const int columns, const cell* read_map_array, const int num_cells);


// Extra prototyper
void create_file();


#endif //FUNCTION_LIBRARY_H




