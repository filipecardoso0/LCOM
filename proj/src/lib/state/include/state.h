#ifndef _STATE_H_
#define _STATE_H_

#include "game_state.h"
#include "menu_state.h"
#include "action.h"

enum app_state{MENU, GAME, SNULL};

typedef enum app_state app_state_t;

/**
 * @brief Interface to access different states
 *        Why not putting them all in this .h?
 *          - This way we keep everything decoupled and organized:
 *              * Allows us to focus on individual modules
 *              * Parts of the program can only access what they need
 *                  i.e snake.h and snake_ctrl can interact with snake_state.h
 *                  directly without loading unecessary data
 *              * Keeps system flexible
 *              * Makes debugging easier
 *          - Having a common interface delegating tasks makes circular
 *            includes less probable to occur
 */


/**
 * @brief Returns the current state of the app
 * 
 * @return app_state_t the app state
 */
app_state_t get_app_state();

/**
 * @brief Set's the app's state to MENU
 * 
 * @return int 0 upon success, 1 if app is already set to MENU
 */
int set_app_state_menu();

/**
 * @brief Set's the app's state to GAME
 * 
 * @return int 0 upon success, 1 if app is already set to GAME
 */
int set_app_state_game();


/**
 * @brief Set's the app's state to SNULL
 * 
 * @return int 0 upon success, 1 if app is already set to SNULL
 */
int set_app_state_null();

void state_step();

void state_set_action(action_t action);

action_t state_get_action();

#endif
