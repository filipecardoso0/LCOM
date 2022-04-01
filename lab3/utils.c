#include <lcom/lcf.h>
#include <i8042.h>

#include <stdint.h>

extern int cnt;

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
  if (sys_inb(port, (uint32_t*) value)) return 1;
  return 0;
}
