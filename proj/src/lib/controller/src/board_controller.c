#include "../include/board_controller.h"

void board_step(board_t* board, action_t action) {

  switch(action) {
    case EXIT: break;
    case SELECT: break;
    default: snake_step(board->snake1, board, action);
  }
}
