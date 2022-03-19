#include <lcom/lcf.h>

#include <stdint.h>

int(util_get_LSB)(uint16_t val, uint8_t *lsb) {
  *lsb = val & GET_LSB;

  return 0;
}

int(util_get_MSB)(uint16_t val, uint8_t *msb) {
  *msb = val & GET_MSB;
  
  return 0;
}

int (util_sys_inb)(int port, uint8_t* value) {

  if (sys_inb(port, (uint32_t*) value)) return 1;

  return 0;
}
