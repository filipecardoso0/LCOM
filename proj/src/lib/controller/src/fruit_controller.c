#include <lcom/lcf.h>

#include "../include/fruit_controller.h"

void
fruit_step(fruit_t* fruit, board_t* board)
{
  if((snake_get_head_position(board->snake1)->x == fruit->position->x &&
  snake_get_head_position(board->snake1)->y == fruit->position->y) 
  || (snake_get_head_position(board->snake2)->x == fruit->position->x && 
  snake_get_head_position(board->snake2)->y == fruit->position->y)){
    fruit_update_pos(fruit, board->width, board->height); 
  }
}


