#include "graphics_card.h"

int set_graphics_mode(uint16_t mode) {
  
  reg86_t reg86;

  memset(&reg86, 0, sizeof(reg86)); //Inicializar a struct

  reg86.ax = VBE_CALL; // VBE call, function 02 -- set VBE mode
  reg86.bx = BIT(14) | mode; // set bit 14: linear framebuffer
  reg86.intno = VBE_INT;
  if ( sys_int86(&reg86) != OK ) {
    printf("set_vbe_mode: sys_int86() failed \n");
    return 1;
  }
  if (reg86.al != VALID_FUNC) return 1;
  if (reg86.ah != SUCCESS_FUNC) return 1;  

  return 0;
}
