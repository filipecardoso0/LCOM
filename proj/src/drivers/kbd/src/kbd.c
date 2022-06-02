#include "../include/kbd.h"

int hook_id_kbd = 1;
uint8_t scancode;
bool error, two_bytes = false;

int parse_scancode(bool *make, size_t *size, uint8_t *bytes) {
  if (error) return -1;
  if (scancode == TWO_BYTES) {
    bytes[0] = scancode;
    two_bytes = true;
    return 1;
  }
  else {
    if (two_bytes) {
      two_bytes = false;
      *size = 2;
      bytes[1] = scancode;
    }
    else {
      *size = 1;
      bytes[0] = scancode;
    }
    *make = !(scancode & BREAK);
  }
  return 0;
}

void (kbc_ih)(void) {
  uint8_t st;
  error = false;

  if (util_sys_inb(STATREG, &st)) return;

  if (st & PAR_ERROR || st & TIMEOUT) {
    util_sys_inb(OBF, &scancode);
    error = true;
    return;
  }
  if (util_sys_inb(OBF, &scancode)) return;
}

int (kbd_subscribe)(uint8_t *bit_no) {
  *bit_no = hook_id_kbd; 

  if (sys_irqsetpolicy(KBD_IRQ, IRQ_REENABLE | IRQ_EXCLUSIVE, &hook_id_kbd) != OK) return 1;

  return 0;
}

int (kbd_unsubscribe)() {
  
  if (sys_irqrmpolicy(&hook_id_kbd)) return 1;
  
  return 0;
}
