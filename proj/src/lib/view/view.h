#include <stdio.h>
#include <stdlib.h>

#define ROWS 1024       //assuming fixed resolution
#define COLUMNS 768
#define CELLROWS 2
#define CELLCOLUMNS 2

static uint16_t h_res = 0; //we can extend to allow multiple
static uint16_t v_res = 0; //gfx modes - must allocate 
                           //screenMapping array with malloc


/**
 * @brief Representation of the screen in a 2-D array;
 * 
 */
typedef struct{ 
    char thing[CELLROWS][CELLCOLUMNS];
}screenCell;


