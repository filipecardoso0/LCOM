#ifndef BOARD_CONTROLLER_H
#define BOARD_CONTROLLER_H

#include "../../model/include/board_model.h"
#include "snake_controller.h"
#include "fruit_controller.h"

void board_step(board_t* board, action_t action);

#endif
