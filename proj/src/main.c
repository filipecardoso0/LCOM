#include <stdio.h>
// #include "controller.h"

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

int main(int argc, char* argv[]){
    printf("Welcome to SnakeTown\n");
    return 0;
}
