#include "../include/menu_state.h"

menu_t* menu = NULL;

void 
menu_state_step(action_t action)
{

  if (action == EXIT) {
    set_app_state_null();
  }

  if (menu == NULL) {
    menu = menu_new(500, 500);
  }

  menu_step(menu, action);
  state_set_action(NOTHING);
  menu_draw(menu); 
}
