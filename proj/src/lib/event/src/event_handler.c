#include "../include/event_handler.h"

void kbd_handler(uint8_t* scancode){
  switch(*scancode){
    case W_PRESSED: controller(W); break;
    case A_PRESSED: controller(A); break;
    case S_PRESSED: controller(S); break;
    case D_PRESSED: controller(D); break;
    case AU_PRESSED: controller(AU); break;
    case AD_PRESSED: controller(AD); break;
    case AL_PRESSED: controller(AL); break;
    case AR_PRESSED: controller(AR); break;
    case ESC_PRESSED: controller(ESC); break;
    case SPACE_PRESSED: controller(SPACE); break;
    case ENTER_PRESSED: controller(ENTER); break; 
    default: perror("Error parsing scancode\n");
  }
}

void timer_handler(){
}

void mouse_handler(struct packet *mouse_packet){
  if(mouse_packet->bytes[0] & RIGHT_PRESS) //needs controller implementation
  else if(mouse_packet->bytes[0] & MID_PRESS) //needs controller implemantation
  else if(mouse_packet->bytes[0] & LEFT_PRESS) //needs controller implemantation
  else
    perror("Error parsing mouse packet \n"); 

  
}
