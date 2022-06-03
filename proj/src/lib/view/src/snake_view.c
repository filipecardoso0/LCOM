#include "../include/snake_view.h"

int 
snake_draw(snake_t* snake)
{
  position_t* position = position_new_from_position(snake->head_pos);
  if (vg_draw_rectangle(position->x * 10, position->y * 10, 10, 10, 0xffffff)) return 1;
  tail_piece_t* next = snake->tail;
  while (next != NULL) {
    switch (snake_get_tail_disposition(next)) {
      case DUP: position = position_get_up(position); break;
      case DDOWN: position = position_get_down(position); break;
      case DLEFT: position = position_get_left(position); break;
      case DRIGHT: position = position_get_right(position); break;
    }
    next = snake_get_next_tail(next);
    if (vg_draw_rectangle(position->x * 10, position->y * 10, 10, 10, 0xffffff)) return 1;
  }
  position_delete(position);
  return 0;
}
