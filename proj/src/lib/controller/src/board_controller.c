#include "../include/board_controller.h"

void board_step(board_t* board, action_t action){

  swith(action){
    case EXIT: board_delete(board); break;
    case SELECT: board_new(50, 50); break;
    case UP: snake_move_up(*board.snake1); break;
    case DOWN: snake_move_down(*board.snake1); break; 
    case LEFT: snake_move_left(*board.snake1); break;
    case RIGHT: snake_move_down(*board.snake1);break;
  }
}