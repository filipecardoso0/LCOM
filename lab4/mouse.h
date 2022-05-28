#ifndef MOUSE_H
#define MOUSE_H

#include <lcom/lcf.h>

#include "mouse_macros.h"
#include "kbc_macros.h"
#include "utils.h"

int mouse_subscribe(uint8_t* bit_no);
int mouse_unsubscribe();
void (mouse_ih)(void);
int get_byte_count();
struct packet mouse_get_packet();
int mouse_disable_data_reporting();

#endif
