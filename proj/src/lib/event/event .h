#ifndef _EVENT_H_
#define _EVENT_H_

#include "event_handler.h"

//This is probably need a lot more methods
//Consider splitting them into different .h's if it starts getting too bloated

/**
 * @brief Sends events to necessary handlers
 * Calls event_handler
 */
void event_dispatcher();

/**
 * @brief Receives events from timer
 * Must add params
 */
void timer_event();

/**
 * @brief Receives events from keyboard
 * Must add params
 */
void kbd_event();

/**
 * @brief Receives events from mouse
 * Must add params
 */
void mouse_event();

/**
 * @brief Receives game-specific events i.e start/end
 * Must add params
 */
void game_event();

#endif