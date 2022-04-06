#include <lcom/lcf.h>
#include <lcom/lab3.h>
#include <stdbool.h>
#include <stdint.h>

#include "kbd.h"

uint32_t cnt = 0;

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
  uint8_t bytes[2];
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

  if(sys_outb(OBF, KBD_IRQ)) return 1; 

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
  uint8_t statuscode, cmdbyte;
  uint8_t bytes[2];

  if (sys_outb(STATREG, R_CMDBYTE)) return 1;
  if (util_sys_inb(OBF, &cmdbyte)) return 1;

  while (scancode != ESC_BREAK_KEY){
    printf("Here 1\n");
    util_sys_inb(STATREG, &statuscode);
    printf("Here 2\n");
    if (statuscode & OBF_FULL){ //return 1;
      printf("Here 3\n");
      // if ((AUX & statuscode) == 0) return 1;
      printf("Here 4\n");
      kbc_ih();
      printf("Here 5\n");
      if (!parse_scancode(&make, &size, bytes))
        kbd_print_scancode(make, size, bytes);
      printf("Here 6\n");  
    }
    tickdelay(micros_to_ticks(DELAY_US));
    printf("Here 7\n");
  } 
  
  
  if (sys_outb(STATREG, cmdbyte)) return 1;
  printf("Here 8\n");
  if (kbd_print_no_sysinb(cnt)) return 1; //Prints sys_inb
  printf("Here 9\n");
  return 0;
}

int(kbd_test_timed_scan)(uint8_t n) {
  /* To be completed by the students */
  printf("%s is not yet implemented!\n", __func__);

  return 1;
}
