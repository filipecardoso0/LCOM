#include <lcom/lcf.h>
#include <i8254.h>

#include <stdint.h>

/*
Obtém o LSB de um inteiro de 2 B;

Como?

& lógico de val com _LSB (0x00FF) e guardar em lsb;
*/

int(util_get_LSB)(uint16_t val, uint8_t *lsb) {
  *lsb = val & _LSB;

  return 0;
}

/*
Obtém o MSB de um inteiro de 2 B;

Como?

& lógico de val com _MSB (0xFF00), fazer shift para a direita de 1 B e guardar em msb;
*/

int(util_get_MSB)(uint16_t val, uint8_t *msb) {
  *msb = (val & _MSB) >> 8;
  
  return 0;
}

int (util_sys_inb)(int port, uint8_t* value) {

  if (sys_inb(port, (uint32_t*) value)) return 1;
  return 0;
}
