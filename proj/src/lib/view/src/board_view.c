#include "../include/board_view.h"

int 
board_draw_elements(board_t* board)
{
  for (int i = 0; i < 2 * (board->width + board->height - 2); i++) {
    if (wall_draw(board->walls[i])) return 1;
  }
  if (snake_draw(board->snake1)) return 1;
  if (fruit_draw(board->fruit)) return 1; 
  return 0;
}

