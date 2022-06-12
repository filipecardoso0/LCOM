#include <lcom/lcf.h>

#include <lcom/proj.h>

#include <stdio.h>

#include "lib/state/include/state.h"
#include "lib/event/include/event.h"
#include "drivers/kbd/include/kbd.h"
#include "drivers/mouse/include/mouse.h"
#include "drivers/timer/include/timer.h"

#define FPS 60 

struct packet packet; 
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

    //timer_set_frequency(0, FPS); 

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
        if (counter == (int) sys_hz() / 4) {
          counter = 0;
          state_step();
        }
      }
    }

    // uint8_t packets[3]; 

    // // Driver Receive Loop
    // uint8_t irq_set_kbd, irq_set_timer, irq_set_mouse;
    // int ipc_status, r;
    // message msg;
    // int counter= 0; 
    // uint8_t currbytecntr = 0x00; 

    // // Subscribe TIMER0 interrupts
    // if (timer_subscribe_int(&irq_set_timer)) return 1;
    // // Subscribe KBD interrupts
    // if (kbd_subscribe(&irq_set_kbd)) return 1;
    // // Enables Mouse Data Reporting in streaming mode 
    // if(mouse_enables_data_reporting()) return 1; 
    // // Subscribe Mouse interrupts
    // if (mouse_subscribe_int(&irq_set_mouse)) return 1; 

    // while (scancode != ESC_BREAK) {
    //     if ( (r = driver_receive(ANY, &msg, &ipc_status)) != 0 ) {
    //         printf("driver_receive failed with: %d", r);
    //         continue;
    //     }
    //     if (is_ipc_notify(ipc_status)) {
    //         switch (_ENDPOINT_P(msg.m_source)) {
    //             case HARDWARE:
    //             counter++; 
    //                 // Handles TIMER0 interrupts
    //                 if (msg.m_notify.interrupts & BIT(irq_set_timer)) {
    //                     timer_int_handler();
    //                     //timer_event(); 
    //                 }

    //                 //Only update this devices @ Each 10 Frames 
    //                 if(counter == 10){
    //                     // Handles KBD interrupts
    //                     if (msg.m_notify.interrupts & BIT(irq_set_kbd)) {
    //                         kbc_ih(); 
    //                         //kbc_event(&scancode); 
    //                     }
    //                     counter = 0; 
    //                 }

    //                  //Handles Mouse interrupts -> (QUESTION: Might be better to leave it out of the above if once we would only get the full mouse information every 30 Frames)
    //                 if (msg.m_notify.interrupts & BIT(irq_set_mouse)) { 

    //                     //Mouse ih reads 1 byte of the OBF in each interrupt
    //                     mouse_ih(); 

    //                     //Asserting packet synchronization
    //                     if ( (currbytecntr == 0) && (packetbyte & ALWAYS_ACTIVE)) {
    //                       packets[currbytecntr] = packetbyte; 
    //                       currbytecntr++; 
    //                     }
    //                     else if (currbytecntr == 1) {
    //                       packets[currbytecntr] = packetbyte;
    //                       currbytecntr++; 
    //                     }
    //                     //We have read the whole packet
    //                     else if (currbytecntr == 2) {   

    //                       packets[currbytecntr] = packetbyte; 
    //                       currbytecntr = 0; 

    //                       for(int i=0; i<3; i++){
    //                           packet.bytes[i] = packets[i]; 
    //                       }

    //                       mouse_parse_packet(&packet);
    //                       //Sends the parsed packet to mouse event
    //                       //mouse_event(&packet); 
    //                 }
                
    //             }
    //     }
    //         }
    //     }
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

