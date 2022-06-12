#ifndef MENU_MODEL_H
#define MENU_MODEL_H

#include "xpm.h"
#include "../include/sprite.h"


/* XPM IMAGES */
#include "exitbutton.xpm"
#include "snake.io.xpm"
#include "start.xpm"

/**
 * @brief Struct that represents the menu. It contains the width and height of the screen and its components as well.
 * 
 */
struct menu {
  uint16_t width, height;
  sprite_t* models[]; 
};

typedef struct menu menu_t;

/**
 * @brief Creates a new menu.
 * 
 * @param width Menu's width.
 * @param height Menu's height.
 * @return menu_t* Points to the menu created.
 */
menu_t* menu_new(uint16_t width, uint16_t height);

/**
 * @brief Deletes a menu.
 * 
 * @param menu Points to the menu to be deleted.
 */
void menu_delete(menu_t* menu);

/**
 * @brief Returns the menu's width.
 * 
 * @param menu Points to the menu that will retrieve its width.
 * @return uint16_t Menu's width value.
 */
uint16_t menu_get_width(menu_t* menu);

/**
 * @brief Returns the menu's height.
 * 
 * @param menu Points to the menu that will retrieve its height.
 * @return uint16_t Menu's height value.
 */
uint16_t menu_get_height(menu_t* menu);

#endif
