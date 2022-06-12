#include "../include/menu_view.h"

//Empties screen
int
menu_empty_screen(menu_t* menu)
{
  if(vg_draw_rectangle(0, 0, menu->width, menu->height, BLACK)) return 1; 

  return 0; 
}


int 
menu_draw(menu_t* menu)
{
  //TO BE IMPLEMENTED
  //menu_empty_screen(menu); 
  for (int i = 0; i < 3; i++)
    sprite_draw(menu->models[i]);

  return 0; 
}



