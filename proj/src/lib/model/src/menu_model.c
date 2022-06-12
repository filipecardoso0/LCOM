#include "../include/menu_model.h"

menu_t* 
menu_new(uint16_t width, uint16_t height)
{
  menu_t* new_menu = (menu_t*) malloc(sizeof(menu_t)); 
  if(new_menu == NULL){
    perror("Something Went Wrong while trying to generate game menu."); 
    return NULL; 
  }

  new_menu->width = width; 
  new_menu->height = height; 
  new_menu->models = xpm_new((const char *const *)cursor_xpm, 200, 200);

  return new_menu;
}

void 
menu_delete(menu_t* board)
{
  //TO BE IMPLEMENTED
}

uint16_t 
menu_get_width(menu_t* menu)
{
  return menu->width;
}

uint16_t 
menu_get_height(menu_t* menu)
{
  return menu->height;
}

xpm_t* 
menu_get_models(menu_t* menu)
{
  return menu->models;
}

