#include "utils.h"

int(util_get_LSB)(uint16_t val, uint8_t *lsb) {
  *lsb = val & _LSB;

  return 0;
}

int(util_get_MSB)(uint16_t val, uint8_t *msb) {
  *msb = (val & _MSB) >> 8;
  
  return 0;
}

int (util_sys_inb)(int port, uint8_t* value) {

  cnt++;
  uint32_t* ptr32 = (uint32_t*)malloc(sizeof(uint8_t));
  if (sys_inb(port, ptr32)) return 1;
  *value = *ptr32;
  free(ptr32);
  return 0;
}
