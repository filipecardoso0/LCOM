#include "../include/menu_view.h"

int 
menu_draw(menu_t* menu)
{
  
  sprite_draw(menu->models[0]);

  for (int i = 1; i <= menu->n_entries; i++)
    if (menu_is_selected(menu, i))
      sprite_draw(menu->selected_models[i]);
    else
      sprite_draw(menu->models[i]);

  return 0; 
}
