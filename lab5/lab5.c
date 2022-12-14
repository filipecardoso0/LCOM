// IMPORTANT: you must include the following line in all your C files
#include <lcom/lcf.h>

#include <lcom/lab5.h>

#include <stdint.h>
#include <stdio.h>

// Any header files included below this line should have been created by you

#include "graphics_card.h"
#include "kbd.h"

int main(int argc, char *argv[]) {
  // sets the language of LCF messages (can be either EN-US or PT-PT)
  lcf_set_language("EN-US");

  // enables to log function invocations that are being "wrapped" by LCF
  // [comment this out if you don't want/need it]
  lcf_trace_calls("/home/lcom/labs/lab5/trace.txt");

  // enables to save the output of printf function calls on a file
  // [comment this out if you don't want/need it]
  lcf_log_output("/home/lcom/labs/lab5/output.txt");

  // handles control over to LCF
  // [LCF handles command line arguments and invokes the right function]
  if (lcf_start(argc, argv))
    return 1;

  // LCF clean up tasks
  // [must be the last statement before return]
  lcf_cleanup();

  return 0;
}

int(video_test_init)(uint16_t mode, uint8_t delay) {
  
  vg_init(mode);

  sleep(delay);
  
  if (vg_exit()) return 1;

  return 0;
}

int(video_test_rectangle)(uint16_t mode, uint16_t x, uint16_t y,
                          uint16_t width, uint16_t height, uint32_t color) {

  vg_init(mode);
  if (vg_draw_rectangle(x, y, width, height, color)) return 1;

  uint8_t irq_set;
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
        }
      }
    }
  }
  
  if (kbd_unsubscribe()) return 1;

  if (vg_exit()) return 1;

  return 0;
}

int(video_test_pattern)(uint16_t mode, uint8_t no_rectangles, uint32_t first, uint8_t step) {

  vg_init(mode);
  if (draw_pattern(mode, no_rectangles, first, step)) return 1;

  uint8_t irq_set;
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
        }
      }
    }
  }
  
  if (kbd_unsubscribe()) return 1;

  if (vg_exit()) return 1;

  return 0;

  return 1;
}

int(video_test_xpm)(xpm_map_t xpm, uint16_t x, uint16_t y) {

  vg_init(MODE_INDEXED);
  
  enum xpm_image_type type = XPM_INDEXED;
  xpm_image_t img;
  uint8_t* map = xpm_load(xpm, type, &img);
  xpm_draw(map, x, y, img.width, img.height);

  uint8_t irq_set;
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
        }
      }
    }
  }
  
  if (kbd_unsubscribe()) return 1;

  if (vg_exit()) return 1;

  return 1;
}

int(video_test_move)(xpm_map_t xpm, uint16_t xi, uint16_t yi, uint16_t xf, uint16_t yf,
                     int16_t speed, uint8_t fr_rate) {

  if (speed == 0 || fr_rate == 0) return 1;

  vg_init(MODE_INDEXED);
  
  enum xpm_image_type type = XPM_INDEXED;
  xpm_image_t img;
  uint8_t* map = xpm_load(xpm, type, &img);

  int ipc_status, r;
  uint8_t irq_timer, irq_kbd; 
  message msg;

  if (timer_subscribe_int(&irq_timer)) return 1;
  if (kbd_subscribe(&irq_kbd)) return 1;

  uint16_t x = xi, y = yi;

  extern int counter;
  int frames = 0;


  if (xpm_draw(map, xi, yi, img.width, img.height)) return 1;

  while (scancode != ESC_BREAK_KEY) {
    if ( (r = driver_receive(ANY, &msg, &ipc_status)) != 0 ) { 
      printf("driver_receive failed with: %d", r);
      continue;
    }
    if (is_ipc_notify(ipc_status)) {
      switch (_ENDPOINT_P(msg.m_source)) {
        case HARDWARE:			
          if (msg.m_notify.interrupts & BIT(irq_timer)) {
            if (x < xf || y < yf) {
              timer_int_handler();
              if (counter == (int)sys_hz() / fr_rate) {
                counter = 0;
                if (speed > 0) {
                  if (x < xf) x += speed;
                  else y += speed;
                  if (paint_screen(BLACK)) return 1;
                  if (x > xf || y > yf) {
                    if (xpm_draw(map, xf, yf, img.width, img.height)) return 1;
                  }
                  else {
                    if (xpm_draw(map, x, y, img.width, img.height)) return 1;
                  }
                }
                else if (frames == abs(speed)) {
                  if (paint_screen(BLACK)) return 1;
                  if (xpm_draw(map, x, y, img.width, img.height)) return 1;
                  if (x < xf) x++;
                  else y++;
                  frames = 0;
                }
                frames++;
              }
            }
          }
          if (msg.m_notify.interrupts & BIT(irq_kbd)) {
            kbc_ih();
          }
      }
    }
  }

  if (timer_unsubscribe_int()) return 1;
  
  if (kbd_unsubscribe()) return 1;

  if (vg_exit()) return 1;

  return 0;
}

int(video_test_controller)() {
  /* To be completed */
  printf("%s(): under construction\n", __func__);

  return 1;
}
