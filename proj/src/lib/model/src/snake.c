#include "../include/snake.h"

struct tail_piece {
    tail_piece_t* next_piece;
    position_t* pos;
};

snake_t* 
snake_new(position_t* position)
{
  snake_t* new_snake = (snake_t*)malloc(sizeof(snake_t));
  if (new_snake == NULL) return NULL;

  new_snake->size = 1;
  new_snake->head_pos = position;
  new_snake->tail = NULL;

  return new_snake;
}

void
snake_delete(snake_t* snake)
{
  free(snake);
}

void 
snake_increase_size(snake_t* snake)
{

}

void 
snake_set_position(snake_t* snake, position_t* position)
{
  position_t* old_pos = position_new_from_position(snake->head_pos);
  snake->head_pos = position;
  tail_piece_t* next = snake->tail;
  while (next != NULL) {
    position_t* tmp_pos = position_new_from_position(old_pos);
    old_pos = position_new_from_position(next->pos);
    next->pos = position_new_from_position(tmp_pos);
    position_delete(tmp_pos);
    next = next->next_piece;
  }
  position_delete(old_pos);
}

position_t* 
snake_get_position(snake_t* snake)
{
  return snake->head_pos;
}
