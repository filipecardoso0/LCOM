#include "../include/menu_controller.h"

int 
menu_step(menu_t* menu, action_t action) 
{

  switch(action) {
    case EXIT: set_app_state_null(); return 1;
    case SELECT: 
      if (menu_is_selected_exit(menu)) { 
        set_app_state_null();
        return 1;
      }
      else if (menu_is_selected_1p(menu)) { 
        set_app_state_game();
        return 1;
      }
      break;
    case LEFT:
      menu_prev_entry(menu);
      break;
    case RIGHT:
      menu_next_entry(menu);
      break;
    default: break;
  }
  return 0;
}
