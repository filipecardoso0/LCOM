#include "../include/snake_model.h"

struct tail_piece {
    tail_piece_t* next_piece;
    disposition_t dispos;
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
  snake->size++;
  tail_piece_t* next = snake->tail;
  while (next != NULL) {
    next = snake_get_next_tail(next);
  }
  next = (tail_piece_t*)malloc(sizeof(tail_piece_t));
  next->next_piece = NULL;

  // JUST FOR TESTING
  next->dispos = DDOWN;
}

void 
snake_set_position(snake_t* snake, position_t* position)
{
  snake->head_pos = position;
}

position_t* 
snake_get_position(snake_t* snake)
{
  return snake->head_pos;
}

tail_piece_t* 
snake_get_next_tail(tail_piece_t* tail)
{
  return tail->next_piece;
}

disposition_t 
snake_get_tail_disposition(tail_piece_t* tail)
{
  return tail->dispos;
}
