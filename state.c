/*
 *
 *
 *      STATE.C
 *
 *      State control module - routines for executing states
 *
 *
 *
 */


#include <stdio.h>
#include <math.h>

#include "allegro5/allegro.h"
#include "allegro5/allegro_primitives.h"
#include "draw.h"
#include "hitbox.h"
#include "control.h"
#include "keymap.h"
#include "sprite.h"
#include "state.h"
#include "video.h"
#include "font.h"
#include "camera.h"
#include "sound.h"
#include "particle.h"


/* current running state */
struct STATE state;



/* sprite layers on this state */
int bgIndex;
struct SPRITE fx[MAX_FX];
struct SPRITE sprites[MAX_SPRITES];


// lighting
ALLEGRO_BITMAP *lightmap = NULL;


void setBackgroundImage(char *name) {

    /* set background image index */
    bgIndex = searchForBmp(name);

}


void initBuffers()
{

    /* set up sprite lists for first use */
    int i;
    for (i = 0; i < MAX_SPRITES; ++i) {
        createSprite(&sprites[i]);
        sprites[i].SetAlive(&sprites[i], false);
    }
    for (i = 0; i < MAX_FX; ++i) {
        createSprite(&fx[i]);
        fx[i].SetAlive(&fx[i], false);
    }
    resetEmitters();
    lightmap = al_create_bitmap(screenWidth, screenHeight);

}


void shutdownState(void)
{

    /* shutdown game state -- we're exiting */
    al_destroy_bitmap(lightmap);

}


void defaultStateControl(struct CONTROLLER *controller)
{

    /* default behavior - terminate whole game on escape button press */
    if (isKeyReleased(BUTTON_E, controller)) {
        state.terminate = true;
    }
}


void updateSprites(void)
{

    // update all main use sprites
    int i = 0;
    for (i = 0; i < MAX_SPRITES; ++i) {
        if (sprites[i].__internal__alive)
            if (sprites[i].update)
                sprites[i].update(&sprites[i]);
    }

}


void updateFX(void)
{

    // update fx layer
    int i;
    for (i = 0; i < MAX_FX; ++i) {
        if (fx[i].__internal__alive) {
            if (fx[i].update) {
                fx[i].update(&fx[i]);
            }
        }
    }

}


void updateState(void)
{

    /* update all sprites in this state */
    updateSprites();
    updateFX();
    updateEmitters();

}


void drawLightingMask(ALLEGRO_COLOR c)
{

    // draw color
    // MUST be called before the rest of state lighting
    al_clear_to_color(c);

}


void drawStateLighting(void)
{

    // draw the myriad lights accompanying the sprites this state
    int i;
    for (i = 0; i < MAX_SPRITES; ++i) {
        if (sprites[i].light) {
            if (sprites[i].GetAlive(&sprites[i])) {
                if (checkCollide(camera, sprites[i].box)) {
                    sprites[i].light(&sprites[i]);
                }
            }
        }
    }
    for (i = 0; i < MAX_FX; ++i) {
        if (fx[i].light) {
            if (fx[i].GetAlive(&fx[i])) {
                fx[i].light(&fx[i]);
            }
        }
    }

}


void drawLight(void)
{

    // does this state employ lighting? do specialty lighting routines
    if (state.light) {
        al_set_target_bitmap(lightmap);
        state.light();
        setToBackBuffer();
        al_set_blender(ALLEGRO_DEST_MINUS_SRC, ALLEGRO_ONE, ALLEGRO_ONE);
        al_draw_bitmap(lightmap, 0, 0, 0);
        al_set_blender(ALLEGRO_ADD, ALLEGRO_ONE, ALLEGRO_INVERSE_ALPHA);
    }

}


void setSpriteOrder(void)
{

    /* set sprite order */
    unsigned int i;
    for (i = 0; i < MAX_SPRITES; ++i) {

        /* add sprite draw instruction to master list */
        if (sprites[i].__internal__alive)
            addSpriteToLayer(sprites[i].__internal__z, &sprites[i]);
    }
    for (i = 0; i < MAX_FX; ++i) {

        /* add fx (usually particles) to draw instruction to master list */
        if (fx[i].__internal__alive)
            addSpriteToLayer(fx[i].__internal__z, &fx[i]);
    }

}


void drawState(void)
{


    /* draw all sprites in layer - used for states without tiles (the default) */
    setSpriteOrder();
    finalizeDrawLayer(0);
    finalizeDrawLayer(1);
    finalizeDrawLayer(2);
    finalizeDrawLayer(3);
    finalizeDrawLayer(4);
    finalizeDrawLayer(5);
    finalizeDrawLayer(6);
    finalizeDrawLayer(7);
    drawLight();

}



void nextState(void *(gotoFunc))
{

    /* store goto routine for the next state
     * then close this one
     */
    state.nextState = gotoFunc;
    state.active = false;

}


struct SPRITE *getNewSprite(void)
{

    /* make new sprite */
    struct SPRITE *s;
    int i;
    for (i = 0; i < MAX_SPRITES; ++i) {
        if (!sprites[i].__internal__alive) {
            s = &sprites[i];
            createSprite(s);
            return s;
        }
    }
    return NULL;

}


struct SPRITE *getNewFX(void)
{

    // create new fx sprite
    int i;
    for (i = 0; i < MAX_FX; ++i) {
        if (!fx[i].__internal__alive) {
            createSprite(&fx[i]);
            return &fx[i];
        }
    }
    return NULL;

}


void runState(ALLEGRO_TIMER *timer)
{

    ALLEGRO_EVENT_QUEUE *events = NULL;
    ALLEGRO_EVENT event;
    struct HWCONTROLINPUT hwControl;
    struct CONTROLLER controller;
    unsigned int redraw = false;
    setHardwareControl(&hwControl);
    resetControlSystem(&controller, &hwControl);
    deserializeControllerMapFromFile(&hwControl, &controller);
    events = al_create_event_queue();
    resetAllDrawLayers();
    al_register_event_source(events, al_get_timer_event_source(timer));
    al_register_event_source(events, al_get_keyboard_event_source());
    al_register_event_source(events, al_get_joystick_event_source());

    /* begin loop */
    do {

        /* handle hw/allegro control system */
        al_wait_for_event(events, &event);
        switch (event.type) {
        case ALLEGRO_EVENT_KEY_DOWN:
            hwControl.pressedKeys[event.keyboard.keycode] = true;
            break;
        case ALLEGRO_EVENT_KEY_UP:
            hwControl.pressedKeys[event.keyboard.keycode] = false;
            break;
        case ALLEGRO_EVENT_JOYSTICK_BUTTON_DOWN:
            hwControl.pressedJS[event.joystick.button] = true;
            break;
        case ALLEGRO_EVENT_JOYSTICK_BUTTON_UP:
            hwControl.pressedJS[event.joystick.button] = false;
            break;
        case ALLEGRO_EVENT_TIMER:

            /* only do normal control function if current state is unpaused, and redraw */
            if (!state.paused)
                SAFERUN(state.control)(&controller);
            handleReleasedKeys(&controller);
            redraw = true;
        }

        /* exit game if we've received a terminate flag from state */
        if (state.terminate)
            state.active = false;

        /* handle redraw */
        if (redraw && al_is_event_queue_empty(events)) {
            preDrawCycle();

            /* update and draw, normal state */
            if (!state.paused && state.active) {
                SAFERUN(state.update)();
                SAFERUN(state.draw)();
                drawLight();
            }

            /* update and draw, combined into one function, paused state */
            else {
                if (state.paused) {
                    SAFERUN(state.pause)(&controller);
                    drawLight();
                }
            }

            /* finish draw */
            postDrawCycle();
            redraw = false;

        }

        // keep keybuffer from getting full of bunk keypresses
        maintainKeyBuf(&controller);

        // permit state change if nextstate is called
        if (!state.active && state.nextState) {

            // go to next state, flush controls
            state.nextState();
            flushController(&hwControl);
            clearKeyBuf(&controller);
            al_flush_event_queue(events);

        }

    } while (state.active);
    al_destroy_event_queue(events);

}



void fadeIn()
{

    /* fades into new state */
    float screenAlpha;

    /* prep transition by running state init and update, just once */
    SAFERUN(state.init)();
    SAFERUN(state.update)();

    /* now begin transition */
    al_set_blender(ALLEGRO_ADD, ALLEGRO_ONE, ALLEGRO_INVERSE_ALPHA);
    for (screenAlpha = 1; screenAlpha > 0; screenAlpha = screenAlpha - 0.05) {

        /* fade in new state */
        preDrawCycle();
        SAFERUN(state.draw)();
        drawLight();
        al_draw_filled_rectangle(0, 0, screenWidth, screenHeight, al_map_rgba_f(0, 0, 0, screenAlpha));
        postDrawCycle();
        al_rest(0.01);

    }


}

void fadeOut()
{

    /* fade out current state */
    float screenAlpha = 0;
    for (screenAlpha = 0; screenAlpha < 1; screenAlpha = screenAlpha + 0.05)
    {

        /* handle state fadeout */
        preDrawCycle();
        SAFERUN(state.draw)();
        drawLight();
        al_set_blender(ALLEGRO_ADD, ALLEGRO_ONE, ALLEGRO_INVERSE_ALPHA);
        al_draw_filled_rectangle(0, 0, screenWidth, screenHeight, al_map_rgba_f(0, 0, 0, screenAlpha));
        postDrawCycle();
        al_rest(0.01);

    }

}

void newState(void *(startFunc), void *(controlFunc), void *(pauseFunc), void *(lightFunc),
              void *(killFunc), void *(updateFunc), void *(drawFunc))
{

    /* only do state transition if draw function exists */
    if (state.draw != NULL)
        fadeOut();

    /* set new state */
    playFrameSounds = true;
    if (state.kill)
        state.kill();
    initBuffers();
    state.active = true;
    state.paused = false;
    state.init = startFunc;
    if (controlFunc == NULL)
        state.control = defaultStateControl;
    else
        state.control = controlFunc;
    state.kill = killFunc;
    state.update = updateFunc;
    state.draw = drawFunc;
    state.pause = pauseFunc;
    state.light = lightFunc;
    state.nextState = NULL;

    /* default back color is black */
    state.backColor = al_map_rgb(0, 0, 0);
    al_clear_to_color(al_map_rgb(0, 0, 0));

    /* and do state fade-in */
    initCamera();
    if (state.draw != NULL)
        fadeIn();

}


/* determine if two sprites have cells in common */
unsigned int commonCell(struct SPRITE *s1, struct SPRITE *s2)
{

    unsigned int i;
    unsigned int k;
    for (i = 0; i < MAX_CELLS; ++i)
    {
        for (k = 0; k < MAX_CELLS; ++k)
        {
            if (s1->cell[i] != BLANK_CELL && s2->cell[k] != BLANK_CELL)
            {
                if (s1->cell[i] == s2->cell[k])
                    return true;
            }
        }
    }
    return false;

}






