#include "../include/utils.h"

int(util_get_LSB)(uint16_t val, uint8_t *lsb) {
  *lsb = val & 0xFF;

  return 0;
}

int(util_get_MSB)(uint16_t val, uint8_t *msb) {
  *msb = (val & 0xFF00) >> 8;
  
  return 0;
}

int (util_sys_inb)(int port, uint8_t* value) {

  if (sys_inb(port, (uint32_t*) value)) return 1;
  
  return 0;
}