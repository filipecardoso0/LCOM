#include "../include/snake_controller.h";

void snake_controller(action_t action, uint8_t player){
    switch(action){
        case UP:{
            if(!player){
                if(snake_1_state == ALIVE) 
                snake_move_up(p1);
                break;
            }
            else if (snake_2_state == ALIVE){
                snake_move_up(p2);
                break;
            }
            break;
        }
        case DOWN:{
            if(!player){
                if(snake_1_state == ALIVE) 
                snake_move_down(p1);
                break;
            }
            else if (snake_2_state == ALIVE){
                snake_move_down(p2);
                break;
            }
            break;
        }
        case LEFT:{
            if(!player){
                if(snake_1_state == ALIVE) 
                snake_move_left(p1);
                break;
            }
            else if (snake_2_state == ALIVE){
                snake_move_left(p2);
                break;
            }
            break;
        }
        case RIGHT:{
            if(!player){
                if(snake_1_state == ALIVE) 
                snake_move_right(p1);
                break;
            }
            else if (snake_2_state == ALIVE){
                snake_move_right(p2);
                break;
            }
            break;
        }
        default: printf("Invalid action\n");
    }
}

void snake_move_left(snake_t* snake);

void snake_move_right(snake_t* snake);

void snake_move_up(snake_t* snake);

void snake_move_down(snake_t* snake);
