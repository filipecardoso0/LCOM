#include <lcom/lcf.h>

#include <stdbool.h>
#include <stdint.h>

extern int counter; 

int(timer_handle_interrupt)(uint8_t time) {
 
  int ipc_status, r;

  uint8_t irq_set; 

  message msg;

  if (timer_subscribe_int(&irq_set)) return 1;

  while ( counter < time * (int)sys_hz()) {
    if ( (r = driver_receive(ANY, &msg, &ipc_status)) != 0 ) { 
      printf("driver_receive failed with: %d", r);
      continue;
    }
    if (is_ipc_notify(ipc_status)) {
      switch (_ENDPOINT_P(msg.m_source)) {
        case HARDWARE:			
          if (msg.m_notify.interrupts & BIT(irq_set)) { /* BIT() ATIVA A BITMASK CORRESPONDENTE AO irq_set */ 
            timer_int_handler();

            if(counter % (int) sys_hz() == 0)
              timer_print_elapsed_time();
          }
          break;
      }
    }
  }

  if(timer_unsubscribe_int()) return 1;

  return 0;
}
