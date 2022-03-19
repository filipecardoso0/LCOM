#include <lcom/lcf.h>
#include <lcom/timer.h>

#include <stdint.h>

#include "i8254.h"

int (timer_set_frequency)(uint8_t timer, uint32_t freq) {
  
  return 1;
}

int (timer_subscribe_int)(uint8_t *bit_no) {
    /* To be implemented by the students */
  printf("%s is not yet implemented!\n", __func__);

  return 1;
}

int (timer_unsubscribe_int)() {
  /* To be implemented by the students */
    printf("%s is not yet implemented!\n", __func__);

  return 1;
}

void (timer_int_handler)() {
  /* To be implemented by the students */
  printf("%s is not yet implemented!\n", __func__);
}

int (timer_get_conf)(uint8_t timer, uint8_t *st) {
  uint8_t control_word, timer_aux;
  
  control_word = TIMER_RB_CMD | TIMER_RB_COUNT_ | TIMER_RB_SEL(timer);

  if (sys_outb(TIMER_CTRL, control_word)) return 1; 

  switch (timer) {
    case 0: timer_aux = TIMER_0;
      break;
    case 1: timer_aux = TIMER_1;
      break;
    case 2: timer_aux = TIMER_2;
      break;
  }

  if (util_sys_inb(timer_aux, st)) return 1;

  return 0;
}

int (timer_display_conf)(uint8_t timer, uint8_t st,
                        enum timer_status_field field) {

  union timer_status_field_val timer_conf; 
  
  switch (field) {
    case tsf_all: timer_conf.byte = st; break;
    case tsf_initial: timer_conf.in_mode = ((BIT(5) & st) | (BIT(4) & st)) >> 4; break;
    case tsf_mode: timer_conf.count_mode = ((BIT(3) & st) | (BIT(2) & st) | (BIT(1) & st)) >> 1;break;
    case tsf_base: timer_conf.bcd = BIT(0) & st; break;
  }

  if (timer_print_config(timer, field, timer_conf)) return 1; 

  return 0;
}