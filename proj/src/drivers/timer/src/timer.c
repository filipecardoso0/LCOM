#include <lcom/lcf.h>
#include <lcom/timer.h>

#include <stdint.h>

#include "../include/timer_macros.h"

int counter = 0; 
int hook_id = 0; 

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
  *bit_no = hook_id; 

  if (sys_irqsetpolicy(TIMER0_IRQ, IRQ_REENABLE, &hook_id) != OK) return 1;

  return 0;
}

int (timer_unsubscribe_int)() {

  if (sys_irqrmpolicy(&hook_id) != OK) return 1;

  return 0;
}

void (timer_int_handler)() {
  counter++;
}
