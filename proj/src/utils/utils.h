#ifndef _UTILS_H_
#define _UTILS_H_

#include <timermacros.h>
#include <stdint.h>

typedef struct{
    int row;
    int col;
}position;

extern uint32_t cnt;

int(util_get_LSB)(uint16_t, uint8_t*);
int(util_get_MSB)(uint16_t, uint8_t*);
int (util_sys_inb)(int port, uint8_t* value);

#endif // _UTILS_H_
