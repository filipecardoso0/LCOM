#ifndef _EVENT_HANDLER_H
#define _EVENT_HANDLER_H

#include "controller.h"
//This is probably need a lot more methods
//Consider splitting them into different .h's if it starts getting too bloated

/**
 * @brief Acts as interface between events and handlers
 * This allows us a certain degree of decoupling
 */
void event_handler();

/**
 * @brief Handles timer events
 * Must add params
 */
void timer_handler();

/**
 * @brief Handles keyboard events
 * Must add params
 */
void kbd_handler();

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