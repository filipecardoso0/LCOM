#include "../include/game_state.h"

board_t* board = NULL;

void 
game_state_step(action_t action)
{

  if (action == EXIT) {
    set_app_state_null();
  }

  if (board == NULL) {
    board = board_new(50, 50);
    board_first_draw(board);
  }
  
  board_step(board, action);
  board_draw(board);
}
