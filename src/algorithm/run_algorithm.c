#include <stdio.h>
#include <stdio.h>
#include <string.h>
#include <math.h>
#include <stdlib.h>
#include <stdbool.h>


typedef enum is_mine {
    no_mine,
    MRUD,
    PMA2,
    PMA3,
    PROM1
} is_mine;

typedef enum is_obstacle {
    no_obstacle,
    tree,
    stone,
    bush,
    tripwire,
    deep_water
} is_obstacle;


