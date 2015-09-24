
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
#include <stdlib.h>
#include "allegro5/allegro.h"

#include "control.h"


static const unsigned int serializedKeyboard = 0;
static const unsigned int serializedJoystick = 1;


/* serializeable version of the game's keymap
 * two parameters -- which control input, keyboard or joystick, and contains input on hardware
 */
static unsigned char serializedControllerMap[CONTROLLER_INPUT_MAX][2];


static void setControllerDefaults(struct HWCONTROLINPUT *hwControl, struct CONTROLLER *controller)
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

    /* perm hardware registers, in case we need to fix something on the menus */
    controller->pressedInputs[KEYBOARD_ENTER] = &hwControl->pressedKeys[ALLEGRO_KEY_ENTER];
    controller->pressedInputs[KEYBOARD_LEFT] = &hwControl->pressedKeys[ALLEGRO_KEY_LEFT];
    controller->pressedInputs[KEYBOARD_RIGHT] = &hwControl->pressedKeys[ALLEGRO_KEY_RIGHT];
    controller->pressedInputs[KEYBOARD_DOWN] = &hwControl->pressedKeys[ALLEGRO_KEY_DOWN];
    controller->pressedInputs[KEYBOARD_UP] = &hwControl->pressedKeys[ALLEGRO_KEY_UP];

    /* set serialized verion of data to save it later */
    serializedControllerMap[UP][serializedKeyboard] = ALLEGRO_KEY_UP;
    serializedControllerMap[DOWN][serializedKeyboard] = ALLEGRO_KEY_DOWN;
    serializedControllerMap[LEFT][serializedKeyboard] = ALLEGRO_KEY_LEFT;
    serializedControllerMap[RIGHT][serializedKeyboard] = ALLEGRO_KEY_RIGHT;
    serializedControllerMap[BUTTON_A][serializedKeyboard] = ALLEGRO_KEY_F;
    serializedControllerMap[BUTTON_B][serializedKeyboard] = ALLEGRO_KEY_D;
    serializedControllerMap[BUTTON_C][serializedKeyboard] = ALLEGRO_KEY_R;
    serializedControllerMap[BUTTON_D][serializedKeyboard] = ALLEGRO_KEY_E;
    serializedControllerMap[BUTTON_E][serializedKeyboard] = ALLEGRO_KEY_ESCAPE;
    serializedControllerMap[BUTTON_PAUSE][serializedKeyboard] = ALLEGRO_KEY_ENTER;

    /* same for hardware so we don't lose it next time we load game */
    serializedControllerMap[KEYBOARD_ENTER][serializedKeyboard] = ALLEGRO_KEY_ENTER;
    serializedControllerMap[KEYBOARD_LEFT][serializedKeyboard] = ALLEGRO_KEY_LEFT;
    serializedControllerMap[KEYBOARD_RIGHT][serializedKeyboard] = ALLEGRO_KEY_RIGHT;
    serializedControllerMap[KEYBOARD_UP][serializedKeyboard] = ALLEGRO_KEY_UP;
    serializedControllerMap[KEYBOARD_DOWN][serializedKeyboard] = ALLEGRO_KEY_DOWN;

}

int *setControlMapping(struct HWCONTROLINPUT *hwcontrol, const unsigned int controllerInput)
{

    /* return pressed input for control mapping menu, and remember the controller input mapping for future */
    int i;
    for (i = 0; i < ALLEGRO_KEY_MAX; ++i) {
        if (hwcontrol->pressedKeys[i]) {
            serializedControllerMap[controllerInput][serializedKeyboard] = (unsigned char)i;
            return &hwcontrol->pressedKeys[i];
        }
    }
    for (i = 0; i < JOYSTICK_MAX; ++i) {
        if (hwcontrol->pressedJS[i]) {
            serializedControllerMap[controllerInput][serializedJoystick] = (unsigned char)i;
            return &hwcontrol->pressedJS[i];
        }
    }
    return NULL;

}


unsigned int deserializeControllerMapFromFile(struct HWCONTROLINPUT *hwcontrol, struct CONTROLLER *controller)
{

    /* check for controller file -- if exists, dump into current hardware control structure */
    FILE *f;
    int i;
    f = fopen("controls.dat", "rb+");
    if (f) {
        fread(serializedControllerMap, sizeof(char), sizeof(serializedControllerMap), f);
        fclose(f);
        for (i = 0; i < CONTROLLER_INPUT_MAX; ++i) {
            if (serializedControllerMap[i][serializedKeyboard]) {
                controller->pressedInputs[i] = &hwcontrol->pressedKeys[serializedControllerMap[i][serializedKeyboard]];
            }
            if (serializedControllerMap[i][serializedJoystick]) {
                controller->pressedInputs[i] = &hwcontrol->pressedJS[serializedControllerMap[i][serializedJoystick]];
            }
        }
    } else {
        setControllerDefaults(hwcontrol, controller);
    }

}


unsigned int serializeControllerMapToFile(void)
{

    /* dump serializable control structure to controls.dat */
    FILE *f;
    f = fopen("controls.dat", "wb+");
    if (f) {
        fwrite(serializedControllerMap, sizeof(char), sizeof(serializedControllerMap), f);
        fclose(f);
    }

}


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
    for (i = 0; i < JOYSTICK_MAX; ++i) {
        hwControl->pressedJS[i] = false;
    }

}



unsigned int isKeyReleased(int x, struct CONTROLLER *controller)
{

    /* check for released key */
    if (controller->releasedKeyTimers[x] == 1) {
        return true;
    }
    return false;

}
