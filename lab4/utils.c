#include <stdint.h>
#include <lcom/lcf.h>

#include <stdint.h>

#include "utils.h"

int (utils_sys_inb)(int port, uint8_t* value){

  uint32_t reference; 
  if(sys_inb(port, &reference)) return 1; 
  *value = reference; 

  return 0; 
}


