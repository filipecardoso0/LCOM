#include "../include/wall_view.h"

int 
wall_draw(wall_t* wall)
{
  if (vg_draw_rectangle(wall->position->x * 10, wall->position->y * 10, 10, 10, 0xf1f3f1)) return 1;
  return 0;
}
