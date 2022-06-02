#ifndef SNAKE_MODEL_H
#define SNAKE_MODEL_H

#include <stdio.h>
#include <stdlib.h>

// #include "list.h"
// #include "utils.h"
#include "food.h"
#include "position.h"

struct tail_piece;

typedef struct tail_piece tail_piece_t;

struct snake {
    uint16_t size;
    position_t* head_pos;
    tail_piece_t* tail;
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
 */
void snake_increase_size(snake_t* snake);


/**
 * @brief Sets a new position for a snake
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
position_t* snake_get_position(snake_t* snake);

// typedef struct {
//     list snakeTail;
//     position* headPos;
//     int minSize;
// }snake;

// typedef enum{UP, DOWN, LEFT, RIGHT} moveAction;

// /**
//  * @brief Creates a snake object. Allocates memory internally
//  * 
//  * @param snake pointer to where the snake will be stored
//  * @param size the size of the snake
//  * @return pointer to the created snake upon success, NULL otherwise 
//  */
// snake* createSnake(snake* snake, int size);
    

// /**
//  * @brief Creates a snake object. Allocates memory internally
//  * 
//  * @param snake pointer to the new snake 
//  * @param size the size of the snake
//  * @param pos the position of the snake
//  * @return pointer to the created snake upon success, NULL otherwise
//  */
// snake* createSnake(snake* snake, int size, position* pos);

// /**
//  * @brief Verifies if the the snake's next move will result in a collision
//  * 
//  * @param snake pointer to the snake
//  * @param cell the cell to where the snake wants to move
//  * @return 0 if there's no collision, 1 if there's a collision
//  */
// int collides(snake* snake, position* newPos);

// /**
//  * @brief moves snake according to user action. Verifies if it the movement
//  * results in a collision. If so, snake dies.
//  * 
//  * @param snake pointer to the snake
//  * @param move pointer to the moveAction to be performed
//  * @return snake* 
//  */
// snake* move(snake* snake, moveAction* move);

// /**
//  * @brief Moves snake up
//  * 
//  * @param snake pointer to the snake
//  */
// void moveUp(snake* snake);

// /**
//  * @brief Move snake down
//  * 
//  * @param snake pointer to the snake
//  */
// void moveDown(snake* snake);

// /**
//  * @brief Move snake to the left
//  * 
//  * @param snake pointer to the snake
//  */
// void moveLeft(snake* snake);

// /**
//  * @brief Move snake to the right
//  * 
//  * @param snake 
//  */
// void moveRight(snake* snake);

// /**
//  * @brief Makes snake eat food. Adds new node to the end of the snakeTail
//  * list and increments size by one.
//  * 
//  * @param snake pointer to the snake
//  * @param food pointer to the food piece to be eaten
//  * @return poitner to the snake upon success, NULL otherwise
//  */
// snake* eatFood(snake* snake, food* food);

// /**
//  * @brief Verfies if snake went under the minimum size and died
//  * 
//  * @param snake pointer to the snake
//  * @return 0 if snake is dead, 1 otherwise 
//  */
// int isDead(snake* snake);

#endif
