#ifndef _GAME_STATE_H
#define _GAME_STATE_H

#include "../../controller/include/board_controller.h"
#include "../../view/include/board_view.h"
#include "state.h"

// /**
//  * @brief Returns current state of all game-related entities
//  */
// typedef struct{
//     game_state_t game_state;
//     foo_state_t foo_state;
//     player_state_t player_state;
// }game_state_info_t;

// /**
//  * @brief Game state machine
//  */
// enum game_state_t{START, ON_GOING, OVER};

// /**
//  * @brief Foo state machine - defined in here due to it's simplicity
//  */
// enum foo_state_t{NEW, EATEN};

// static game_state_t g_state = OVER;
// static foo_state_t f_state = EATEN;

// /**
//  * @brief Returns a game_state_info struct containing all the information
//  *        regarding game-relented entities
//  * 
//  * @return game_state_info_t the game_state_info object
//  */
// game_state_info_t get_game_state();

// /**
//  * @brief Set's the current game state to START
//  * 
//  * @return int 0 upon success, 1 if game's state is already set to START
//  */
// int set_game_state_start();

// /**
//  * @brief Set's the current game state to ON_GOING
//  * 
//  * @return int 0 upon success, 1 if game's state is already set to ON_GOING
//  */
// int set_game_state_on();

// /**
//  * @brief Set's the current game state to OVER
//  * 
//  * @return int 0 upon success, 1 if game's state is already set to OVER
//  */
// int set_game_state_over();

// /**
//  * @brief Set's foo's state to NEW
//  * 
//  * @return int 0 upon success, 1 if foo's state is already NEW
//  */
// int set_foo_state_new();

// /**
//  * @brief Set's foo's state to EATEN
//  * 
//  * @return int 0 upon success, 1 if foo's state is already EATEN
//  */
// int set_foo_state_eaten();

/**
 * @brief Changes the game state according to the action made by the user.
 * 
 * @param action input action: it can be whether is uses an valid game key, selects an option or when he/she wants to exit or does nothing.
 */
void game_state_step(action_t action);

#endif 
