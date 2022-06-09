#ifndef BOARD_MODEL_H
#define BOARD_MODEL_H

#include "snake_model.h"
#include "wall_model.h"
#include "fruit_model.h"

struct board {
  uint16_t width, height;
  snake_t* snake1, *snake2;
  wall_t** walls;
  fruit_t* fruit; 
};

typedef struct board board_t;

board_t* board_new(uint16_t width, uint16_t height);

void board_delete(board_t* board);

// void board_set_snake(board_t* board, snake_t* snake, int n_snake);

// void board_set_walls(board_t* board, wall_t* walls);

uint16_t board_get_width(board_t* board);

uint16_t board_get_height(board_t* board);

snake_t* board_get_snake(board_t* board, int n_snake);

wall_t** board_get_walls(board_t* board);

#endif
