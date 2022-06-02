#ifndef _MENU_STATE_H_
#define _MENU_STATE_H_

enum menu_state_t{MAIN, ONE_P, TWO_P, HELP, OFF};

static menu_state_t menu_state = OFF;

/**
 * @brief Returns the menu's current state
 * 
 * @return menu_state_t menu's current state
 */
menu_state_t get_menu_state();

/**
 * @brief Set's the current menu state to MAIN
 * 
 * @return int 0 upon success, 1 if menu_state is already set to MAIN
 */
int set_menu_state_main();

/**
 * @brief Set's the current menu state to ONE(player)
 * 
 * @return int 0 upon success, 1 if menu_state is already set to ONE
 */
int set_menu_state_one();

/**
 * @brief Set's the current menu state to TWO(players)
 * 
 * @return int 0 upon success, 1 if menu_state is already set to TWO
 */
int set_menu_state_two();

/**
 * @brief Set's the current menu state to HELP
 * 
 * @return int 0 upon success, 1 if menu_state is already set to HELP
 */
int set_menu_state_help();

/**
 * @brief Set's the current menu state to OFF
 * 
 * @return int 0 upon success, 1 if menu_state is already set to OFF
 */
int set_menu_state_off();


#endif