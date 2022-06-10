#ifndef SNAKE_CONTROLLER_H
#define SNAKE_CONTROLLER_H

#include "../../state/include/snake_state.h"
#include "../../model/include/snake_model.h"
#include "../../state/include/action.h"

void snake_step(snake_t* snake, action_t action);

void snake_move(snake_t* snake);

void snake_move_left(snake_t* snake);

void snake_move_right(snake_t* snake);

void snake_move_up(snake_t* snake);

void snake_move_down(snake_t* snake);

#endif
