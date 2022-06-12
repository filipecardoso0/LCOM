#include "../include/controller.h"

void controller(action_t action){
    switch(app_state){
        case GAME: {
            switch(action){
                case UP: board_step();
            }
        }
        case MENU: 
            break;
        case SNULL: break;
    }
}