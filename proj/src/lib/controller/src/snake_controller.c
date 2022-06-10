#include <lcom/lcf.h>

#include "../include/snake_controller.h"

void
snake_step(snake_t* snake, action_t action)
{
    switch (action) {
        case UP: 
            if (snake->size == 1 || snake->head_direction != SOUTH)
                snake->head_direction = NORTH;
            break;
        case DOWN: 
            if (snake->size == 1 || snake->head_direction != NORTH)
                snake->head_direction = SOUTH;
            break;
        case LEFT: 
            if (snake->size == 1 || snake->head_direction != EAST)
                snake->head_direction = WEST;
            break;
        case RIGHT: 
            if (snake->size == 1 || snake->head_direction != WEST)
                snake->head_direction = EAST;
            break;
        default: break;
    }
    snake_move(snake);
}

void
snake_move(snake_t* snake)
{
    switch (snake->head_direction) {
        case NORTH: snake_move_up(snake); break;
        case SOUTH: snake_move_down(snake); break;
        case EAST: snake_move_right(snake); break;
        case WEST: snake_move_left(snake); break;
    }
}

void 
snake_move_left(snake_t* snake)
{
    snake_set_position(snake, position_get_left(snake_get_head_position(snake)));
}

void
snake_move_right(snake_t* snake)
{
    snake_set_position(snake, position_get_right(snake_get_head_position(snake)));
}

void 
snake_move_up(snake_t* snake)
{
    snake_set_position(snake, position_get_up(snake_get_head_position(snake)));
}

void
snake_move_down(snake_t* snake)
{
    snake_set_position(snake, position_get_down(snake_get_head_position(snake)));
}
