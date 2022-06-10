#ifndef TIMER_H
#define TIMER_H

#include <lcom/lcf.h>

extern int counter;

int (timer_subscribe_int)(uint8_t *bit_no);
int (timer_unsubscribe_int)();

#endif
