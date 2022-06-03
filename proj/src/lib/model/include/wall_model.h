#ifndef WALL_MODEL_H
#define WALL_MODEL_H

#include "position.h"

struct wall {
  position_t* position;
};

typedef struct wall wall_t;

wall_t* wall_new(position_t* position);

void wall_delete(wall_t* wall);

void wall_set_position(wall_t* wall, position_t* position);

position_t* wall_get_position(wall_t* wall);

#endif
