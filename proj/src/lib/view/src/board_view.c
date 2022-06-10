#include "../include/board_view.h"

int
board_clear(board_t* board) 
{
  // if (snake_get_body_piece_position(board->snake1_dbuffer->body_end)->x
  //           != snake_get_body_piece_position(board->snake1->body_end)->x ||
  //           snake_get_body_piece_position(board->snake1_dbuffer->body_end)->y
  //           != snake_get_body_piece_position(board->snake1->body_end)->y) {
  //   if (vg_draw_rectangle(snake_get_body_piece_position(board->snake1_dbuffer->body_end)->x * 10,
  //                         snake_get_body_piece_position(board->snake1_dbuffer->body_end)->y * 10,
  //                         10, 10, BLACK
  //   )) return 1;
  // }

  if (vg_draw_rectangle(10, 10, (board->width - 2) * 10, (board->height - 2) * 10, BLACK)) return 1;

  return 0;
}

int 
board_draw_elements(board_t* board)
{
  // Clear non-overlapping pixels
  if (board_clear(board)) return 1;

  for (int i = 0; i < 2 * (board->width + board->height - 2); i++) {
    if (wall_draw(board->walls[i])) return 1;
  }
  if (fruit_draw(board->fruit)) return 1; 
  if (snake_draw(board->snake1)) return 1;

  board->snake1_dbuffer = board->snake1;
  board->snake2_dbuffer = board->snake2;

  return 0;
}

