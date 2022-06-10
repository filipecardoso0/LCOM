#include "../include/board_model.h"

board_t* 
board_new(uint16_t width, uint16_t height)
{
  board_t* new_board = (board_t*)malloc(sizeof(board_t));
  if (new_board == NULL) return NULL;

  new_board->width = width;
  new_board->height = height;

  // init snakes
  position_t* snake1_pos = position_new(3 * width / 4, height / 2);
  snake_t* snake1 = snake_new(snake1_pos);
  position_t* snake2_pos = position_new(width / 4, height / 2);
  snake_t* snake2 = snake_new(snake2_pos);
  new_board->snake1 = snake1;
  new_board->snake2 = snake2;

  // init walls
  int wall_idx = 0;
  new_board->walls = (wall_t**)malloc(sizeof(wall_t*) * 2 * (width + height - 2));
  for (uint16_t x = 0; x < width; x++) {
    position_t* wall_pos1 = position_new(x, 0);
    position_t* wall_pos2 = position_new(x, height - 1);
    new_board->walls[wall_idx++] = wall_new(wall_pos1);
    new_board->walls[wall_idx++] = wall_new(wall_pos2);
  }
  for (uint16_t y = 1; y < height - 1; y++) {
    position_t* wall_pos1 = position_new(0, y);
    position_t* wall_pos2 = position_new(width - 1, y);
    new_board->walls[wall_idx++] = wall_new(wall_pos1);
    new_board->walls[wall_idx++] = wall_new(wall_pos2);
  }

  //init fruit -> fruit will always spawn in a random place
  position_t* randompos; 
  randompos = position_new_randompos(width, height); 
  fruit_t* fruit = fruit_new(randompos); 
  new_board->fruit = fruit; 

  new_board->snake1_dbuffer = *snake1;
  new_board->snake2_dbuffer = *snake2;

  return new_board;
}

void 
board_delete(board_t* board)
{
  snake_delete(board->snake1);
  snake_delete(board->snake2);
  for (int i = 0; i < 2 * (board->width + board->height - 2); i++) {
    wall_delete(board->walls[i]);
  }
  free(board->walls);
  free(board);
}

uint16_t 
board_get_width(board_t* board)
{
  return board->width;
}

uint16_t 
board_get_height(board_t* board)
{
  return board->height;
}

snake_t* 
board_get_snake(board_t* board, int n_snake)
{
  switch (n_snake) {
    case 0 : return board->snake1;
    case 1 : return board->snake2;
    default: return NULL;
  }
}

wall_t** 
board_get_walls(board_t* board)
{
  return board->walls;
}
