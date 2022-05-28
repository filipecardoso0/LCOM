#include "mouse.h"

static int hook_id = 12;
static uint8_t packet[3];

int mouse_subscribe(uint8_t* bit_no) {
  *bit_no = hook_id;
  if (sys_irqsetpolicy(MOUSE_IRQ, IRQ_REENABLE | IRQ_EXCLUSIVE, &hook_id)) return 1;
  return 0;
}

int mouse_unsubscribe() {
  if (sys_irqrmpolicy(&hook_id)) return 1;
  return 0;
}

static int byte_counter = 0;

int get_byte_count() { return byte_counter; }

void (mouse_ih)(void) {
    uint8_t statuscode, byte;

    if(byte_counter >= 3) byte_counter = 0;

    if (util_sys_inb(STATREG, &statuscode)) return;

    if (statuscode & (TIMEOUT | PAR_ERROR)) {
        util_sys_inb(OBF, &byte);
        return;
    }

    if (!(statuscode & AUX) || !(statuscode & OBF_FULL)) return;

    if (util_sys_inb(OBF, &byte)) return;

    packet[byte_counter] = byte;
    byte_counter++;
}

struct packet mouse_get_packet() {
  struct packet pp;
  pp.bytes[0] = packet[0];
  pp.bytes[1] = packet[1];
  pp.bytes[2] = packet[2];
  pp.rb = pp.bytes[0] & RMB;
  pp.mb = pp.bytes[0] & MMB;
  pp.lb = pp.bytes[0] & LMB;
  pp.delta_x = pp.bytes[0] & X_SIGN ? (int16_t)(0xFF00 | pp.bytes[1]) : pp.bytes[1];
  pp.delta_y = pp.bytes[0] & Y_SIGN ? (int16_t)(0xFF00 | pp.bytes[2]) : pp.bytes[2];
  pp.x_ov = pp.bytes[0] & X_OVFL;
  pp.y_ov = pp.bytes[0] & Y_OVFL;

  return pp;
}

int mouse_disable_data_reporting() {
  
}
