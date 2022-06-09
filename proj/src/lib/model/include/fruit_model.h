#ifndef FRUIT_MODEL_H
#define FRUIT_MODEL_H

#include "position.h"

typedef struct {
  position_t* position;
} fruit_t;

fruit_t* fruit_new(position_t* position);

void fruit_delete(fruit_t* fruit);

void fruit_set_position(fruit_t* fruit, position_t* position);

position_t* fruit_get_position(fruit_t* wall);

#endif
