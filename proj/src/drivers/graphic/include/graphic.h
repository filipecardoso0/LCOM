#ifndef GRAPHICS_H
#define GRAPHICS_H

#include <lcom/lcf.h>

#include <lcom/lab5.h>

#include <stdint.h>
#include <stdio.h>

#include "graphic_macros.h"

void *(vg_init)(uint16_t mode);
int(vg_draw_pixel)(uint16_t x, uint16_t y, uint32_t color);
int(vg_draw_hline)(uint16_t x, uint16_t y, uint16_t len, uint32_t color);
int(vg_draw_rectangle)(uint16_t x, uint16_t y, uint16_t width, uint16_t height, uint32_t color);
int paint_screen(uint32_t color);
int (vg_xpm_img_draw)(xpm_image_t* image, uint16_t x, uint16_t y); 

#endif
