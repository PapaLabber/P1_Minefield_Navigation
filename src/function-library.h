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
} Cell;

// Funktion prototyper
void read_map_test();
void parse_map_test();
void process_map_test();
Cell* read_map_from_file (const char* file, int* rows, int* columns, int* num_cells);


#endif //FUNCTION_LIBRARY_H




