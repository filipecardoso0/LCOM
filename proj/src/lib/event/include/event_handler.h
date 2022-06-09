#ifndef _EVENT_HANDLER_H
#define _EVENT_HANDLER_H

#include "../../controller/include/controller.h"
#include "../../../drivers/kbd/include/key_keyboard.h"

/**
 * @brief Handles keyboard events
 * Must add params
 */
void kbd_handler(uint8_t* scancode);

/**
 * @brief Handles mouse events
 * Must add params
 */
void mouse_handler();

/**
 * @brief Handles game events
 * Must add params
 */
void game_handler();

#endif