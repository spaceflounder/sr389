
/*
 *
 *
 *      CONTROLLIB.C
 *
 *
 *      Game control input library for BRINSTAR engine
 *
 *
 *
 *
 */

#include <stdio.h>
#include "allegro5/allegro.h"

#include "control.h"


void resetControlSystem(struct CONTROLLER *controller, struct HWCONTROLINPUT *hwcontrol)
{

    // reset controller system
    int i;
    for (i = 0; i < CONTROLLER_INPUT_MAX; ++i) {
        controller->pressedInputs[i] = 0;
        controller->releasedKeyTimers[i] = 0;
    }
    for (i = 0; i < ALLEGRO_KEY_MAX; ++i) {
        hwcontrol->pressedKeys[i] = 0;
    }
    for (i = 0; i < JOYSTICK_MAX; ++i) {
        hwcontrol->pressedJS[i] = 0;
    }

}


void clearKeyBuf(struct CONTROLLER *controller)
{

    int i;
    for (i = 0; i < CONTROLLER_INPUT_MAX; ++i)
        if (controller->releasedKeyTimers[i] > 0)
            controller->releasedKeyTimers[i] = 0;

}


void maintainKeyBuf(struct CONTROLLER *controller)
{

    int i;
    for (i = 0; i < CONTROLLER_INPUT_MAX; ++i)
        if (controller->releasedKeyTimers[i] > 0)
            --controller->releasedKeyTimers[i];

}


void handleReleasedKeys(struct CONTROLLER *controller)
{

    /* check controller for released buttons / keys */
    int i;
    for (i = 0; i < CONTROLLER_INPUT_MAX; ++i) {
        if (controller->pressedInputs[i]) {
            if (*controller->pressedInputs[i]) {
                controller->releasedKeyTimers[i] = 8;
            }
        }
    }

}


void flushController(struct HWCONTROLINPUT *hwControl)
{

    /* while anything exists in controller input buffers, prevent game from continuing */
    int i;
    for (i = 0; i < ALLEGRO_KEY_MAX; ++i) {
        hwControl->pressedKeys[i] = false;
    }

}

void setControllerDefaults(struct HWCONTROLINPUT *hwControl, struct CONTROLLER *controller)
{

    /* default controller mapping, used when controller map file is not found */
    controller->pressedInputs[UP] = &hwControl->pressedKeys[ALLEGRO_KEY_UP];
    controller->pressedInputs[DOWN] = &hwControl->pressedKeys[ALLEGRO_KEY_DOWN];
    controller->pressedInputs[LEFT] = &hwControl->pressedKeys[ALLEGRO_KEY_LEFT];
    controller->pressedInputs[RIGHT] = &hwControl->pressedKeys[ALLEGRO_KEY_RIGHT];
    controller->pressedInputs[BUTTON_A] = &hwControl->pressedKeys[ALLEGRO_KEY_F];
    controller->pressedInputs[BUTTON_B] = &hwControl->pressedKeys[ALLEGRO_KEY_D];
    controller->pressedInputs[BUTTON_C] = &hwControl->pressedKeys[ALLEGRO_KEY_R];
    controller->pressedInputs[BUTTON_D] = &hwControl->pressedKeys[ALLEGRO_KEY_E];
    controller->pressedInputs[BUTTON_E] = &hwControl->pressedKeys[ALLEGRO_KEY_ESCAPE];
    controller->pressedInputs[BUTTON_PAUSE] = &hwControl->pressedKeys[ALLEGRO_KEY_ENTER];

}


unsigned int isKeyReleased(int x, struct CONTROLLER *controller)
{

    /* check for released key */
    if (controller->releasedKeyTimers[x] == 1) {
        return true;
    }
    return false;

}
