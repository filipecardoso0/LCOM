#ifndef SNAKE_MODEL_H
#define SNAKE_MODEL_H

#include <stdio.h>
#include <stdlib.h>

#include "position.h"

struct body_piece;

typedef struct body_piece body_piece_t;

struct snake {
    uint16_t size;
    body_piece_t* body_start;
    body_piece_t* body_end;
};

typedef struct snake snake_t;

/**
 * @brief Creates a snake object. Allocates memory internally
 * 
 * @param position the position of the snake
 * 
 * @return pointer to the created snake upon success, NULL otherwise 
 */
snake_t* snake_new(position_t* position);

/**
 * @brief Deletes a snake object from memory
 * 
 * @param snake the snake object that is to be deleted
 */
void snake_delete(snake_t* snake);

/**
 * @brief Increases the size of a snake
 * 
 * @param snake snake whose size is to be increased
 * @param position position where the snake will increase to
 */
void snake_increase_size(snake_t* snake, position_t* position);


/**
 * @brief Sets a new position for a snake
 * 
 * IMPORTANT: This is only meant to move the snake one
 * 'pixel' at a time and is not garanteed to work otherwise.
 * 
 * @param snake snake object whose position is to be set
 * @param position new position
 */
void snake_set_position(snake_t* snake, position_t* position);


/**
 * @brief Gets the position of a snake
 * 
 * @param snake snake object to get position from
 * 
 * @return position of the snake object
 */
position_t* snake_get_head_position(snake_t* snake);

body_piece_t* snake_get_next_body_piece(body_piece_t* body_piece);

position_t* snake_get_body_piece_position(body_piece_t* body_piece);

#endif
