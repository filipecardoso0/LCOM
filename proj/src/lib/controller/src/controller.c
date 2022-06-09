#include "../include/controller.h"

void controller(key_press_t key){
    switch(app_state){
        case GAME: {
            switch(key){
                case W: snake_controller(UP, 0); break;
                case S: snake_controller(DOWN, 0); break;
                case A: snake_controller(LEFT, 0); break;
                case D: snake_controller(RIGHT, 0); break;
                case AU: snake_controller(UP, 1); break;
                case AD: snake_controller(DOWN, 1); break;
                case AL: snake_controller(LEFT, 1); break;
                case AR: snake_controller(RIGHT, 1); break;
                case ESC: break;
                case SPACE: break;
                case ENTER: break; 
            }
        }
        case MENU: break;
        case SNULL: break;
    }
}