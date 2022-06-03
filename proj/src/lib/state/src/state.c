#include "../include/state.h"

app_state_t 
get_app_state()
{
  return app_state;
}

int 
set_app_state_menu()
{
  if (app_state == MENU) return 1;
  app_state = MENU;
  return 0;
}

int 
set_app_state_game()
{
  if (app_state == GAME) return 1;
  app_state = GAME;
  return 0;
}

int 
set_app_state_null()
{
  if (app_state == SNULL) return 1;
  app_state = SNULL;
  return 0;
}
