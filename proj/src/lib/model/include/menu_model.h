#ifndef MENU_MODEL_H
#define MENU_MODEL_H

#include "xpm.h"
#include "../include/sprite.h"


/* XPM IMAGES */
#include "exitbutton.xpm"
#include "snake.io.xpm"
#include "start.xpm"

struct menu {
  uint16_t width, height;
  sprite_t* models[]; 
};

typedef struct menu menu_t;

menu_t* menu_new(uint16_t width, uint16_t height);

void menu_delete(menu_t* menu);

uint16_t menu_get_width(menu_t* menu);

uint16_t menu_get_height(menu_t* menu);

#endif
