#ifndef SPRITE_H
#define SPRITE_H

#include <lcom/lcf.h>
#include "../../../drivers/graphic/include/graphic.h"

typedef struct sprite{
  int x, y; 
  int width, height; 
  int xspeed, yspeed; 
  xpm_image_t* img; 
} sprite_t;

sprite_t* sprite_new(const char* const* xpm, int x, int y); 

void sprite_delete(sprite_t* sprite); 

int sprite_get_width(sprite_t* sprite); 

int sprite_get_height(sprite_t* sprite); 

int sprite_get_xspeed(sprite_t* sprite); 

int sprite_get_yspeed(sprite_t* sprite); 

int sprite_get_x(sprite_t* sprite); 

int sprite_get_y(sprite_t* sprite); 

xpm_image_t* sprite_get_image(sprite_t* sprite); 

void sprite_draw(sprite_t* sprite); 

#endif

