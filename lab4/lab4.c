// IMPORTANT: you must include the following line in all your C files
#include <lcom/lcf.h>
#include <stdint.h>
#include <stdio.h>

#include "mouse.h"
#include "utils.h" 

//Global variables
extern int hook_id; 
extern uint8_t packetbyte; 

uint8_t packets[3]; 
struct packet packet; 

// Any header files included below this line should have been created by you

int main(int argc, char *argv[]) {
  // sets the language of LCF messages (can be either EN-US or PT-PT)
  lcf_set_language("EN-US");

  // enables to log function invocations that are being "wrapped" by LCF
  // [comment this out if you don't want/need/ it]
  lcf_trace_calls("/home/lcom/labs/lab4/trace.txt");

  // enables to save the output of printf function calls on a file
  // [comment this out if you don't want/need it]
  lcf_log_output("/home/lcom/labs/lab4/output.txt");

  // handles control over to LCF
  // [LCF handles command line arguments and invokes the right function]
  if (lcf_start(argc, argv))
    return 1;

  // LCF clean up tasks
  // [must be the last statement before return]
  lcf_cleanup();

  return 0;
}

// MUST BE IMPLEMENTED

int (mouse_test_packet)(uint32_t cnt) {
  
  uint8_t irq_set; //Stores hook_id of the device that will be interrupted
  int ipc_status, r;
  message msg;
  int currbytecntr = 0; 

  //PART 1 -> configure the mouse properly

  //Enables data reporting in streaming mode by the mouse
  if(mouse_enables_data_reporting()) return 1; 

  //Subscribes mouse interrupts on irq port 12
  if(mouse_subscribe_int(&irq_set)) return 1; 

  //PART 1 -> Done

  while ( cnt > 0 ) {
    if ( (r = driver_receive(ANY, &msg, &ipc_status)) != 0 ) { 
      printf("driver_receive failed with: %d", r);
      continue;  
    }
    if (is_ipc_notify(ipc_status)) {
      switch (_ENDPOINT_P(msg.m_source)) {
        case HARDWARE:			
          if (msg.m_notify.interrupts & BIT(irq_set)) { //Bit(irq_set) setups a bit mask on hook_id
            //PEDRO SOUTO TIP: Don't need to bother about checking if OBF has data & if AUX is set

            //Mouse ih reads 1 byte of the OBF in each interrupt
            mouse_ih(); 

            //Asserting packet synchronization
            if( (currbytecntr == 0) && (packetbyte & ALWAYS_ACTIVE)){
              packets[currbytecntr] = packetbyte; 
              currbytecntr++; 
            }
            else if(currbytecntr == 1){
              packets[currbytecntr] = packetbyte;
              currbytecntr++; 
            }
            //We have read the whole packet
            else if(currbytecntr == 2){   

              packets[currbytecntr] = packetbyte; 
              currbytecntr = 0; 

              for(int i=0; i<3; i++){
                packet.bytes[i] = packets[i]; 
              }

              mouse_parse_packet(&packet);
              mouse_print_packet(&packet); 
              cnt--; 
            }
            else
              continue; 
        }
      }
    } 
  }

  // PART 5 -> reset the mouse to Minix's default configuration, before exiting

  if(mouse_reset_to_default()) return 1; 

  // PART 5 -> DONE

  return 0;
}

int (mouse_test_async)(uint8_t idle_time) {
    /* To be completed */
    printf("%s(%u): under construction\n", __func__, idle_time);
    return 1;
}

int (mouse_test_gesture)(uint8_t x_len, uint8_t tolerance) {
    /* To be completed */
    printf("%s: under construction\n", __func__);
    return 1;
}


////// DOESN'T NEED TO BE IMPLEMENTED

int (mouse_test_remote)(uint16_t period, uint8_t cnt) {
    /* This year you need not implement this. */
    printf("%s(%u, %u): under construction\n", __func__, period, cnt);
    return 1;
}

