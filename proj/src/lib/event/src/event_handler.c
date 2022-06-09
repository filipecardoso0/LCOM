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
    default: printf("Error parsing scancode\n");
}