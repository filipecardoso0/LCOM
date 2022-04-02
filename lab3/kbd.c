#include <lcom/lcf.h>

#include "i8042.h"

int hook_id = 1;
uint8_t bytes[2];

int parse_scancode(bool *make, size_t *size, uint8_t *bytes){
    if (bytes[0] == 0xFF && bytes[1] == 0xFF) return 1;

  if(bytes[0] & BREAK) *make = false;
  else *make = true;

  if(bytes[1] == TWO_BYTES) size = (size_t *) 2;
  else size = (size_t *) 1;

  return 0;
}

void (kbc_ih)(void) {
  uint8_t st, scancode;
  if (util_sys_inb(STATREG, &st)) return;

  if(st & PAR_ERROR || st & TIMEOUT){
    for(int i = 0; i < 2; i++)
      bytes[i] = 0xFF;
    printf("Error");
    return;
  } 

  if (util_sys_inb(OBF, &scancode)) return;
  if(scancode == TWO_BYTES){
    bytes[1] = scancode;
    if(util_sys_inb(OBF, &scancode)) return;
  }

  bytes[0] = scancode;
}

int kbd_subscribe(uint8_t *hook_id) {
  
  if (sys_irqsetpolicy(KBD_IRQ, IRQ_REENABLE | IRQ_EXCLUSIVE, (int *) hook_id)) return 1;

  return 0;
}

int kbd_unsubscribe(uint8_t *hook_id) {
  
  if (sys_irqrmpolicy( (int *) hook_id)) return 1;
  
  return 0;
}
