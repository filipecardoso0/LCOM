#ifndef BOARD_VIEW_H
#define BOARD_VIEW_H

#include "../../model/include/board_model.h"
#include "wall_view.h"
#include "snake_view.h"
#include "fruit_view.h"

int board_first_draw(board_t* board);
int board_draw(board_t* board);

#endif
