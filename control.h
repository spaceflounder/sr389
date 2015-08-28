/* Control library module header */

#ifndef CONTROLLIB_H
#define CONTROLLIB_H

#include "allegro5/allegro.h"


/* standard control input object
 * contains both keyboard and joystick data
 */

#define JOYSTICK_MAX                    12
#define CONTROLLER_INPUT_MAX            12

#define BUTTON_A                4
#define BUTTON_B                5
#define BUTTON_C                6
#define BUTTON_D                7
#define BUTTON_E                8
#define BUTTON_PAUSE            9
#define SHOULDER_LEFT           10
#define SHOULDER_RIGHT          11


/* SR389 directions/sides */
#define LEFT            0
#define UP              1
#define RIGHT           2
#define DOWN            3
#define FORWARD         4
#define LOWERLEFT       5
#define LOWERRIGHT      6
#define UPPERLEFT       7
#define UPPERRIGHT      8

/* hardware control input - what we get straight from allegro key and js
 * through a bit of pointer trickery
 */
struct HWCONTROLINPUT
{

    /* key handler arrays */
    int pressedKeys[ALLEGRO_KEY_MAX];

    /* joystick */
    int pressedJS[JOYSTICK_MAX];

};


/* user-definable control subsystem */
struct CONTROLLER
{

    // is key pressed? trigger here
    int *pressedInputs[CONTROLLER_INPUT_MAX];

    // released keys timers - only trigger released key for one frame exactly
    int releasedKeyTimers[CONTROLLER_INPUT_MAX];

};


void resetControlSystem(struct CONTROLLER *controller, struct HWCONTROLINPUT *hwcontrol);
void flushController(struct HWCONTROLINPUT *hwControl);
void clearKeyBuf(struct CONTROLLER *controller);
void maintainKeyBuf(struct CONTROLLER *controller);
void initKeyBuffer(struct CONTROLLER *controller);
void setControllerDefaults(struct HWCONTROLINPUT *hwControl, struct CONTROLLER *controller);
void handleReleasedKeys(struct CONTROLLER *controller);
unsigned int isKeyReleased(int x, struct CONTROLLER *controller);

#endif // CONTROLLIB_H
