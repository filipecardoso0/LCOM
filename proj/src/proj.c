#include <lcom/lcf.h>

#include <lcom/proj.h>

#include <stdio.h>

#include "lib/state/include/state.h"
#include "lib/event/include/event.h"
#include "drivers/kbd/include/kbd.h"
#include "drivers/mouse/include/mouse.h"
#include "drivers/timer/include/timer.h"

#define FPS 5

uint8_t scancode; 

int main(int argc, char* argv[]) {
  // sets the language of LCF messages (can be either EN-US or PT-PT)
  lcf_set_language("EN-US");

  // enables to log function invocations that are being "wrapped" by LCF
  // [comment this out if you don't want/need it]
  lcf_trace_calls("/home/lcom/labs/proj/trace.txt");

  // enables to save the output of printf function calls on a file
  // [comment this out if you don't want/need it]
  lcf_log_output("/home/lcom/labs/proj/output.txt");

  // handles control over to LCF
  // [LCF handles command line arguments and invokes the right function]
  if (lcf_start(argc, argv))
    return 1;

  // LCF clean up tasks
  // [must be the last statement before return]
  lcf_cleanup();

  return 0;

}

int(proj_main_loop)(int argc, char *argv[]) {

    vg_init(MODE_DIRECT_24);

    set_app_state_menu();

    // loop stuff
    uint8_t irq_set_kbd, irq_set_timer;
    int ipc_status, r;
    message msg;

    // subscribe interrupts
    if (timer_subscribe_int(&irq_set_timer)) return 1;
    if (kbd_subscribe(&irq_set_kbd)) return 1;

    while (get_app_state() != SNULL) {
      if ( (r = driver_receive(ANY, &msg, &ipc_status)) != 0 ) { 
        printf("driver_receive failed with: %d", r);
        continue;
      }
      if (is_ipc_notify(ipc_status)) {
        switch (_ENDPOINT_P(msg.m_source)) {
          case HARDWARE:			
            if (msg.m_notify.interrupts & BIT(irq_set_timer)) {
              timer_int_handler();
              timer_event();
            }
            if (msg.m_notify.interrupts & BIT(irq_set_kbd)) {
              kbc_ih();
              kbd_event(scancode);
            }
        }
        if (counter == (int) sys_hz() / FPS) {
          counter = 0;
          state_step();
        }
      }
    }

    if (kbd_unsubscribe()) {
      perror("ERROR: Something went wrong while unsubscribing Keyboard interrupts\n");
      return 1;
    }

    if (timer_unsubscribe_int()){
      perror("ERROR: Something went wrong while unsubscribing timer interrupts\n");
      return 1;
    }
    
    // if (mouse_unsubscribe_int()){
    //   perror("ERROR: Something went wrong while unsubscribing mouse interrupts\n");
    //   return 1;
    // }

    vg_exit();

    return 0;

}

