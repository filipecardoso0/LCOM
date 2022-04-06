#include "kbd.h"


bool parse_scancode(bool *make, size_t *size, uint8_t *bytes){
  if (scancode == 0xFFFF) return 1;

  uint8_t lsb, msb;

  if (util_get_LSB(scancode, &lsb)) return 1;
  if (util_get_MSB(scancode, &msb)) return 1;

  if(lsb & BREAK) *make = false;
  else *make = true;

  if(msb == TWO_BYTES) {
    size = (size_t *) 2;
    bytes[1] = msb;
  }
  else size = (size_t *) 1;

  bytes[0] = lsb;
  return 0;
}

void (kbc_ih)(void) {
  uint8_t st, buffer;
  if (util_sys_inb(STATREG, &st)) return;
  
  if(st & PAR_ERROR || st & TIMEOUT){
    scancode = 0xFFFF;
    printf("Error\n");
    return;
  } 


  if (util_sys_inb(OBF, &buffer)) return;

  if(buffer == TWO_BYTES){
    scancode |= buffer;
    scancode = scancode << (8);
    if(util_sys_inb(OBF, &buffer)) return;
  }
  
  scancode |= buffer;
}

int (kbd_subscribe)(uint8_t *bit_no) {
  *bit_no = hook_id; 

  if (sys_irqsetpolicy(KBD_IRQ, IRQ_REENABLE | IRQ_EXCLUSIVE, &hook_id) != OK) return 1;

  return 0;
}

int (kbd_unsubscribe)() {
  
  if (sys_irqrmpolicy(&hook_id)) return 1;
  
  return 0;
}
