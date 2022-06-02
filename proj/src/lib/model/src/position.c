#include "../include/position.h"

position_t* 
position_new(uint16_t x, uint16_t y)
{
  position_t* new_pos = (position_t*)malloc(sizeof(position_t));
  if (new_pos == NULL) return NULL;

  new_pos->x = x;
  new_pos->y = y;

  return new_pos;
}

position_t* 
position_new_from_position(position_t* position)
{
  position_t* new_pos = position_new(position->x, position->y);

  return new_pos;
}

void
position_delete(position_t* pos)
{
  free(pos);
}

position_t* 
position_get_right(position_t* pos)
{
  position_t* new_pos = position_new(pos->x + 1, pos->y);
  return new_pos;
}

position_t* 
position_get_left(position_t* pos)
{
  position_t* new_pos = position_new(pos->x - 1, pos->y);
  return new_pos;
}

position_t* 
position_get_up(position_t* pos)
{
  position_t* new_pos = position_new(pos->x, pos->y - 1);
  return new_pos;
}

position_t* 
position_get_down(position_t* pos)
{
  position_t* new_pos = position_new(pos->x, pos->y + 1);
  return new_pos;
}

uint16_t 
position_get_x(position_t* pos)
{
  return pos->x;
}

uint16_t 
position_get_y(position_t* pos)
{
  return pos->y;
}
