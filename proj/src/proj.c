#include <lcom/lcf.h>
#include <lcom/proj.h>

#include <stdio.h>

// #include "lib/state/include/state.h"
// #include "lib/controller/include/board_controller.h"
// #include "lib/controller/include/action.h"
#include "lib/view/include/board_view.h"
#include "drivers/kbd/include/kbd.h"
#include "drivers/timer/include/timer_macros.h"
#include "utils/include/utils.h"
#include "drivers/kbd/include/key_keyboard.h"

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

    vg_init(MODE_DIRECT_16);

    board_t* board = board_new(50, 50);

    if (board_draw_elements(board)) return 1;

    // Driver Receive Loop
    uint8_t irq_set_kbd, irq_set_timer;
    bool make;
    size_t size;
    int ipc_status, r;
    message msg;

    // Subscribe TIMER0 interrupts
    if (timer_subscribe_int(&irq_set_timer)) return 1;
    // Subscribe KBD interrupts
    if (kbd_subscribe(&irq_set_kbd)) return 1;

    while (scancode != ESC_BREAK) {
        if ( (r = driver_receive(ANY, &msg, &ipc_status)) != 0 ) {
            printf("driver_receive failed with: %d", r);
            continue;
        }
        if (is_ipc_notify(ipc_status)) {
            switch (_ENDPOINT_P(msg.m_source)) {
                case HARDWARE:
                    // Handles TIMER0 interrupts
                    if (msg.m_notify.interrupts & BIT(irq_set_timer)) {
                        timer_int_handler();
                    }

                    // Handles KBD interrupts
                    if (msg.m_notify.interrupts & BIT(irq_set_kbd)) {
                        kbc_ih();
                        // To be implemented: Keyboard event -> In order to manage the scancodes
                        // kbd_event();
                    }
            }
        }
    }

    if (kbd_unsubscribe()) {
        perror("ERROR: Something went wrong while unsubscribing Keyboard interrupts\n");

    }

    if (timer_unsubscribe_int()){
        perror("ERROR: Something went wrong while unsubscribing timer interrupts\n");
        return 1;
    }

        // while (get_app_state() != SNULL) {

    //   switch (get_app_state()) {
    //     // GET USER ACTION FROM DRIVERS
    //     case GAME:
    //       // board_step(board, action);
    //       break;
    //     case MENU:
    //       // TODO
    //       break;
    //   }
    // }

    sleep(3);
    vg_exit();
    
    board_delete(board);

    return 0;

}
