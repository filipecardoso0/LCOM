#ifndef GRAPHICS_CARD_H_
#define GRAPHICS_CARD_H_

#include <lcom/lcf.h>

#include <lcom/lab5.h>

#include <stdint.h>
#include <stdio.h>

#include "graphics.h"

int draw_pattern(uint16_t mode, uint8_t no_rectangles, uint32_t first, uint8_t step);
int xpm_draw(uint8_t* map, uint16_t x, uint16_t y, uint16_t width, uint16_t height);

#endif
