#ifndef GRAPHICS_CARD_H_
#define GRAPHICS_CARD_H_

#include <lcom/lcf.h>

#include <lcom/lab5.h>

#include <stdint.h>
#include <stdio.h>

#include "graphics.h"

int set_graphics_mode(uint16_t);
int draw_rectangle(uint16_t mode, uint16_t x, uint16_t y, uint16_t width, uint16_t height, uint32_t color);

#endif
