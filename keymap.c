/*
 *
 *
 *
 *          KEYMAP.C
 *
 *
 *          Keymap routines, for setting the controller inputs beyond the defaults
 *
 *
 *
 *
 *
 */

#include "allegro5/allegro.h"
#include "allegro5/allegro_primitives.h"

#include "control.h"
#include "font.h"
#include "state.h"
#include "video.h"



/* local reference to current input hardware */
static struct HWCONTROLINPUT *localHWController;

/* which button are we mapping to right now? */
static int whichButtonToMap;

/* text to display while we're waiting for input for the mapping operation */
static char *keymapStateText;

/* previous state, so we can return to it later */
static void (*previousState)(struct CONTROLLER *controller);


static void pauseKeymapState(struct CONTROLLER *controller)
{

    /* special pause state for keymapping */
    int *checkForKey;
    checkForKey = NULL;
    printCenter(NULL, screenWidth / 2, screenHeight / 2, keymapStateText);

    /* if the player has selected an input for a given controller button, end the pause keymap state */
    checkForKey = setControlMapping(localHWController, whichButtonToMap);
    if (checkForKey) {
        controller->pressedInputs[whichButtonToMap] = checkForKey;
        serializeControllerMapToFile();
        state.pause = previousState;
        al_rest(0.5);
    }

}



void setReturnState(void (*returnState)(struct CONTROLLER *controller))
{

    /* set return state for when we're done setting a keymap */
    previousState = returnState;

}


void setKeymapPauseMsg(char *msg)
{

    /* tell the player what input we're mapping */
    keymapStateText = msg;

}


void setHardwareControl(struct HWCONTROLINPUT *hwc)
{

    /* set input hardware for use by keymap routines */
    localHWController = hwc;

}


void mapButton(int buttonIndex)
{

    /* get input to map button on controller struct */
    whichButtonToMap = buttonIndex;
    state.pause = pauseKeymapState;

}

