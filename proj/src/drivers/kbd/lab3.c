#include <lcom/lcf.h>
#include <lcom/lab3.h>
#include <stdbool.h>
#include <stdint.h>

#include "kbd.h"
#include "timer.c"

uint32_t cnt = 0; 
uint8_t bytes[2];


int(kbd_test_timed_scan)(uint8_t n) {

  uint8_t irq_set_timer;
  uint8_t irq_set_kbd; 
  bool make;
  size_t size;
  int ipc_status, r;
  message msg;
  extern int counter; 

  if (timer_subscribe_int(&irq_set_timer)) return 1; 
  if (kbd_subscribe(&irq_set_kbd)) return 1; 

  while (scancode != ESC_BREAK_KEY && counter < (int) (n * sys_hz())) {
    if ( (r = driver_receive(ANY, &msg, &ipc_status)) != 0 ) { 
      printf("driver_receive failed with: %d", r);
      continue;  
    }
    if (is_ipc_notify(ipc_status)) {
      switch (_ENDPOINT_P(msg.m_source)) {
        case HARDWARE:	

          //Handles Timer0
          if (msg.m_notify.interrupts & BIT(irq_set_timer)) { /* BIT() ATIVA A BITMASK CORRESPONDENTE AO irq_set_timer */ 
            timer_int_handler();
          }
 
          //Handles Keyboard -> If a key was pressed resets the timer counter
          if (msg.m_notify.interrupts & BIT(irq_set_kbd)) { 
            counter = 0; 
            kbc_ih();
            if (!parse_scancode(&make, &size, bytes))
              kbd_print_scancode(make, size, bytes);
        }
      }
    }
  }

  if (kbd_unsubscribe()) return 1;

  if (timer_unsubscribe_int()) return 1;

  if (kbd_print_no_sysinb(cnt)) return 1;
  cnt = 0;

  return 0;
}
