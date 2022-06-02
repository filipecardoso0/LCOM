#include <stdio.h>
#include <stdlib.h>
#include "utils.h"

typedef struct{
    position* pos;
    uint8_t spawnTimer;
} foo;

/**
 * @brief Spawns a new foo in a random empty position
 * 
 */
void spawn_foo();

/**
 * @brief Get the spawn timer object
 * 
 * @return uint8_t foo's spawn timer value
 */
uint8_t get_spawn_timer();

/**
 * @brief Sets foo's spawn timer
 * 
 * @param time the new time
 */
void set_spawn_timer(uint8_t time);

/**
 * @brief Deletes position object and resets spawn timer
 * 
 */
void got_eaten();