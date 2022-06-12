#include <lcom/lcf.h>

#include "../include/snake_controller.h"

void
snake_step(snake_t* snake, board_t* board, action_t action)
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
    snake_move(snake, board);
}

void
snake_move(snake_t* snake, board_t* board)
{
    switch (snake->head_direction) {
        case NORTH: snake_move_up(snake, board); break;
        case SOUTH: snake_move_down(snake, board); break;
        case EAST: snake_move_right(snake, board); break;
        case WEST: snake_move_left(snake, board); break;
    }
}

void 
snake_move_left(snake_t* snake, board_t* board)
{
    if (board->fruit->position->x == position_get_left(snake_get_head_position(snake))->x &&
        board->fruit->position->y == position_get_left(snake_get_head_position(snake))->y) {
        snake_increase_size(snake, position_get_left(snake_get_head_position(snake)));
        return;
    }


    if (board_is_empty(board, position_get_left(snake_get_head_position(snake))))
        snake_set_position(snake, position_get_left(snake_get_head_position(snake)));
    else{
        //Two Manners of Game Over Happening
        if(snake->body_end == snake->body_start){
            //Maybe add Game Over Screen???
            printf("Game Over"); 
            //set_snake_state_dead()
        }
        if(snake_decrease_size(snake)){
            printf("Game Over"); 
            //set_snake_state_dead()
        }
    }
}

void
snake_move_right(snake_t* snake, board_t* board)
{
    if (board->fruit->position->x == position_get_right(snake_get_head_position(snake))->x &&
        board->fruit->position->y == position_get_right(snake_get_head_position(snake))->y) {
        snake_increase_size(snake, position_get_right(snake_get_head_position(snake)));
        return;
    }


    if (board_is_empty(board, position_get_right(snake_get_head_position(snake))))
        snake_set_position(snake, position_get_right(snake_get_head_position(snake)));
    else{
        //Two Manners of Game Over Happening
        if(snake->body_end == snake->body_start){
            //Maybe add Game Over Screen???
            printf("Game Over"); 
            //set_snake_state_dead()
        }
        if(snake_decrease_size(snake)){
            printf("Game Over"); 
            //set_snake_state_dead()
        }
    }
}

void 
snake_move_up(snake_t* snake, board_t* board)
{
    if (board->fruit->position->x == position_get_up(snake_get_head_position(snake))->x &&
        board->fruit->position->y == position_get_up(snake_get_head_position(snake))->y) {
        snake_increase_size(snake, position_get_up(snake_get_head_position(snake)));
        return;
    }


    if (board_is_empty(board, position_get_up(snake_get_head_position(snake))))
        snake_set_position(snake, position_get_up(snake_get_head_position(snake)));
    else{
        //Two Manners of Game Over Happening
        if(snake->body_end == snake->body_start){
            //Maybe add Game Over Screen???
            printf("Game Over"); 
            //set_snake_state_dead()
        }
        if(snake_decrease_size(snake)){
            printf("Game Over"); 
            //set_snake_state_dead()
        }
    }
}

void
snake_move_down(snake_t* snake, board_t* board)
{
    if (board->fruit->position->x == position_get_down(snake_get_head_position(snake))->x &&
        board->fruit->position->y == position_get_down(snake_get_head_position(snake))->y) {
        snake_increase_size(snake, position_get_down(snake_get_head_position(snake)));
        return;
    }


    if (board_is_empty(board, position_get_down(snake_get_head_position(snake))))
        snake_set_position(snake, position_get_down(snake_get_head_position(snake)));
    else{
        //Two Manners of Game Over Happening
        if(snake->body_end == snake->body_start){
            //Maybe add Game Over Screen???
            printf("Game Over"); 
            //set_snake_state_dead()
        }
        if(snake_decrease_size(snake)){
            printf("Game Over"); 
            //set_snake_state_dead()
        }
    }
}
