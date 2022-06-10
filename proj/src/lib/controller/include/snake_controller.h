#include "../../state/include/snake_state.h"
#include "action.h"

extern snake_state_t snake_1_state;
extern snake_state_t snake_2_state;
extern snake_t p1;
extern snake_t p2;

void snake_controller(key_press_t key_press);

void snake_move_left(snake_t* snake);

void snake_move_right(snake_t* snake);

void snake_move_up(snake_t* snake);

void snake_move_down(snake_t* snake);
