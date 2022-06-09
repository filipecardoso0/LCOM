#include "../include/event.h";

void event_dispatcher(){
  switch(event.eventType){
    case KBD: kbd_handler(event.eventData); break;
    case MOUSE: break;
    default: break;
  }
}

void kbd_event(uint8_t* scancode){
  event.eventType = KBD;
  event.eventData = scancode;
  event_dispatcher();
}