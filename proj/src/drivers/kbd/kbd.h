#ifndef _KBD_H_
#define _KBD_H_

#include <lcom/lcf.h>
#include "utils.h"

extern int hook_id_kbd;
extern uint8_t scancode;

int parse_scancode(bool*, size_t*, uint8_t*);

void (kbc_ih)(void);
int (kbd_subscribe)(uint8_t*);
int (kbd_unsubscribe)();

#endif /* _KBD_H_ */ 
