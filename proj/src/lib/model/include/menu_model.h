#ifndef MENU_MODEL_H
#define MENU_MODEL_H

#include "xpm.h"

/* XPM IMAGES */
#include "test.xpm"

struct menu {
  uint16_t width, height;
  xpm_t* models;
};

typedef struct menu menu_t;

menu_t* menu_new(uint16_t width, uint16_t height);

void menu_delete(menu_t* menu);

uint16_t menu_get_width(menu_t* menu);

uint16_t menu_get_height(menu_t* menu);

xpm_t* menu_get_models(menu_t* menu);

#endif
