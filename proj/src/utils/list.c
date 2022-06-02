#include <stdio.h>
#include <stdlib.h>
#include "screen.h"

typedef struct{
    Node* next;
    screenPixel* cell;
    int size;
}list;

typedef struct{
    list snakeTail;
    int minSize;
}snake;


/**
 * @brief Creates a snake object. Allocates memory internally
 * 
 * @param snake pointer to where the snake will be stored
 * @param size the size of the snake
 * @return pointer to the created snake upon success, NULL otherwise 
 */
snake* createSnake(snake* snake, int size);
    

/**
 * @brief Creates a snake object. Allocates memory internally
 * 
 * @param snake pointer to the new snake 
 * @param size the size of the snake
 * @param pos the position of the snake
 * @return pointer to the created snake upon success, NULL otherwise
 */
snake* createSnake(snake* snake, int size, screenPixel* pos);/**
 * @brief 
 * 
 */

/**
 * @brief 
 * 
 * @param snake pointer to the snake
 * @param foo pointer to the food piece to be eaten
 * @return poitner to the snake upon success, NULL otherwise
 */
snake* eatFoo(snake* snake, foo* foo)

snake* collides(snake* snake, 
    

