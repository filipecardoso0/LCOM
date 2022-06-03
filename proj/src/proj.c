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

/**
 * General app brief:
 * > Main thing is the controller - highest level component, everything 
 *   happens through it. Ensures communication between each submodule
 * > Controller uses state and *_state API's to handle game mechanisms
 *      * gets information regarding current states
 *          - this dictates what can and can't be done
 *      * updates said information with API methods
 *      - this ensures there's a higher point to where everything converges
 *        and allows a good degree of structure and decoupling
 * > States are merely informative
 *      * contain information about what's going on with each model
 * > Models are game-backend specific
 *      * they don't alter states 
 *          - controller does this for them
 *      * they have information regarding object position
 *          - inner methods alter said information (i.e move, get eaten)
 *          - map.h contains a backend representation of the map
 *          - xpm.h will have all the required XPM's loaded into memory
 *              . this way we can load everything on start and ensure 
 *                responsiveness
 * > Events are the bridge between devices and controller
 *      * device triggers corresponding event.h::method
 *          - method will call event_dispatcher
 *      * event.dispatcher signals event_handler
 *      * event_handler triggers controller
 *          - the idea is to be able to retrieve information from the
 *            hardware while keeping a certain vertical organization:
 *              . hardware is decoupled from controller
 *              . hardware generates specific methods
 *              . said methods signal handler which in turn interacts with 
 *                controller
 * 
 * TODO:
 *  #finish view
 *  #finish map.h
 *      - must figure out how to make this not super unefficient
 *  #design controller and *_controller API's
 *  #dive into events:
 *      - figure out how dispatcher can process events
 *      - figure out how handlers will handl events
 *      - figure out how handler will communicate with controller
 * 
 */

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
