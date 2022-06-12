#include "../include/fruit_view.h"

int 
fruit_draw(fruit_t* fruit)
{
  if (vg_draw_rectangle(fruit->position->x * 10, fruit->position->y * 10, 10, 10, 0xff0000)) return 1;
  return 0;
}

