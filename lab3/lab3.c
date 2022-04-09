#include <lcom/lcf.h>
#include <lcom/lab3.h>
#include <stdbool.h>
#include <stdint.h>

#include "kbd.h"
#include "timer.c"

uint32_t cnt = 0; 
uint8_t bytes[2];

int main(int argc, char *argv[]) {
  // sets the language of LCF messages (can be either EN-US or PT-PT)
  lcf_set_language("EN-US");

  // enables to log function invocations that are being "wrapped" by LCF
  // [comment this out if you don't want/need it]
  lcf_trace_calls("/home/lcom/labs/lab3/trace.txt");

  // enables to save the output of printf function calls on a file
  // [comment this out if you don't want/need it]
  lcf_log_output("/home/lcom/labs/lab3/output.txt");

  // handles control over to LCF
  // [LCF handles command line arguments and invokes the right function]
  if (lcf_start(argc, argv))
    return 1;

  // LCF clean up tasks
  // [must be the last statement before return]
  lcf_cleanup();

  return 0;
}

int(kbd_test_scan)() {
  
  uint8_t irq_set;
  bool make;
  size_t size;
  int ipc_status, r;
  message msg;

  if (kbd_subscribe(&irq_set)) return 1;

  while (scancode != ESC_BREAK_KEY) {
    if ( (r = driver_receive(ANY, &msg, &ipc_status)) != 0 ) { 
      printf("driver_receive failed with: %d", r);
      continue;  
    }
    if (is_ipc_notify(ipc_status)) {
      switch (_ENDPOINT_P(msg.m_source)) {
        case HARDWARE:			
          if (msg.m_notify.interrupts & BIT(irq_set)) { 
            kbc_ih();
            if (!parse_scancode(&make, &size, bytes))
              kbd_print_scancode(make, size, bytes);
        }
      }
    }
  }

  // if(sys_outb(OBF, KBD_IRQ)) return 1; 

  //Keyboard unsubscribe
  if (kbd_unsubscribe()) return 1;

  //Prints sys_inb
  if (kbd_print_no_sysinb(cnt)) return 1;
  cnt = 0;

  return 0;
}

int (kbd_test_poll)() {

  bool make;
  size_t size;
  uint8_t statuscode;
  uint8_t bytes[2];

  while (scancode != ESC_BREAK_KEY) {
    if (util_sys_inb(STATREG, &statuscode)) return 1;
    if (statuscode & OBF_FULL && !(statuscode & AUX)) { 
      kbc_ih();
      if (!parse_scancode(&make, &size, bytes))
        kbd_print_scancode(make, size, bytes);
    }
    tickdelay(micros_to_ticks(DELAY_US));
  } 
  
  // Issue command to write command byte and write it
  for (unsigned i = 0; i < 5000; i++) {
    if (util_sys_inb(STATREG, &statuscode)) return 1;
    if( (statuscode & IBF_FULL) == 0 ) {
      if (sys_outb(CMDREG, W_CMDBYTE)) return 1;
      if (sys_outb(IBF, INT)) return 1;
      break;
    }
    tickdelay(micros_to_ticks(DELAY_US));
  } 

  if (kbd_print_no_sysinb(cnt)) return 1;

  return 0;
}




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
