#include <lcom/lcf.h>
#include <lcom/timer.h>

#include <stdint.h>

#include "i8254.h"

int counter = 0; 

int (timer_set_frequency)(uint8_t timer, uint32_t freq) {

  uint8_t*  st = (uint8_t*) malloc(sizeof(uint8_t));
  uint8_t target, ctrl_wrd, freq_lsb, freq_msb;
  uint16_t new_freq;
  uint32_t check_freq; 

  if (freq > TIMER_FREQ) return 1;
  
  check_freq = TIMER_FREQ / freq;
    
  if(check_freq > UINT16_MAX) return 1;
  else new_freq = check_freq;

  if (util_get_LSB(new_freq, &freq_lsb)) return 1;
  if (util_get_MSB(new_freq, &freq_msb)) return 1;
  
  if (timer_get_conf(timer, st)) return 1;

  ctrl_wrd = *st & 0x0F;
  ctrl_wrd |= TIMER_LSB_MSB;

  switch(timer){
    case 0: target = TIMER_0; break;
    case 1: target = TIMER_1; 
            ctrl_wrd |= TIMER_SEL1; break;
    case 2: target = TIMER_2; 
            ctrl_wrd |= TIMER_SEL2; break; 
    default: return 1;
  }

  if (sys_outb(TIMER_CTRL, ctrl_wrd)) return 1;

  if (sys_outb(target, (uint32_t) freq_lsb)) return 1;
  if (sys_outb(target, (uint32_t) freq_msb)) return 1;

  free(st);

  return 0;
}

int (timer_subscribe_int)(uint8_t *bit_no) {

  int *hook_id; 
  hook_id = (int*)malloc(sizeof(int));
  *hook_id = TIMER0_HOOKID; 

  *bit_no = *hook_id; 

  if (sys_irqsetpolicy(TIMER0_IRQ, IRQ_REENABLE, hook_id) != OK) return 1;
  if (sys_irqenable(hook_id) != OK) return 1;

  free(hook_id);

  return 0;
}

int (timer_unsubscribe_int)() {

  if (sys_irqdisable(TIMER0_HOOKID) != OK) return 1;
  if (sys_irqrmpolicy(TIMER0_HOOKID) != OK) return 1;

  return 0;
}

void (timer_int_handler)() {
  counter++;
}

int (timer_get_conf)(uint8_t timer, uint8_t *st) {
  uint8_t control_word, timer_aux;
  
  control_word = TIMER_RB_CMD | TIMER_RB_SEL(timer) | TIMER_RB_COUNT_ ; 

  if(sys_outb(TIMER_CTRL, control_word)) return 1; 

  switch (timer) {
    
    case 0: timer_aux = TIMER_0; break;
    case 1: timer_aux = TIMER_1; break;
    case 2: timer_aux = TIMER_2; break;
    default: return 1;

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
