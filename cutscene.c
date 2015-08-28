/*
 *
 *
 *      CUTSCENE.C
 *
 *      Cutscene commands for sprites, for SR389 engine
 *
 *
 */


#include <stdio.h>

#include "allegro5/allegro.h"

#include "sprite.h"
#include "video.h"
#include "state.h"
#include "camera.h"

#include "cutscene.h"





static void startCutscene(void)
{


}


static void endCutscene(void)
{


}


void startCustomCutscene(void)
{

    /* used for cutscenes that haven't been defined automatically
     * these are more work but sometimes unavoidable
     */

    startCutscene();


}


void endCustomCutscene(void)
{

    /* used for cutscenes that haven't been defined automatically
     * these are more work but sometimes unavoidable
     */

    endCutscene();


}


unsigned int refreshCutscene(void)
{

    /* custom cutscene refresh - called within a loop */
    /* update only this sprite and draw */
    preDrawCycle();
    if (state.draw != NULL)
        state.draw();
    if (state.light != NULL) {
        drawLight();
    }
    postDrawCycle();
    al_rest(0.006);
    return true;

}


void moveSpriteCutsceneDirection(struct SPRITE *s, unsigned int animIndex, unsigned int loopAnim, unsigned int direction, float distance, float speed)
{

    // only move sprite by specfic direction in cutscene
    startCutscene();
    switch (direction) {
    case UP:
        do {
            if (refreshCutscene()) {
                s->__internal__vy = -speed;
                updateSprite(s);
                s->SetAnim(s, animIndex, loopAnim);
            }
        } while (s->box.centerY > distance);
        s->__internal__vy = 0;
        s->box.y = distance;
        break;
    case DOWN:
        do {
            if (refreshCutscene()) {
                s->__internal__vy = speed;
                updateSprite(s);
                s->SetAnim(s, animIndex, loopAnim);
            }
        } while (s->box.centerY < distance);
        s->__internal__vy = 0;
        s->box.y = distance;
        break;
    case LEFT:
        do {
            if (refreshCutscene()) {
                s->__internal__vx = -speed;
                updateSprite(s);
                s->SetAnim(s, animIndex, loopAnim);
            }
        } while (s->box.centerX > distance);
        s->__internal__vx = 0;
        s->box.x = distance;
        break;
    case RIGHT:
        do {
            if (refreshCutscene()) {
                s->__internal__vx = speed;
                updateSprite(s);
                s->SetAnim(s, animIndex, loopAnim);
            }
        } while (s->box.centerX < distance);
        s->__internal__vx = 0;
        s->box.x = distance;
        break;
    }
    endCutscene();

}


void moveSpriteCutscene(struct SPRITE *s, unsigned int animIndex, unsigned int loopAnim, float x, float y, float speed)
{

    /* move sprite in a cutscene, to x and y */
    struct HITBOX h;
    newHitbox(&h, x, y, 1, 1);
    startCutscene();
    do {

        /* update only this sprite and draw */
        if (refreshCutscene()) {
            SetVelocityBetweenHitboxes(s, h, speed);
            updateSprite(s);
            s->SetAnim(s, animIndex, loopAnim);
        }

    } while (!checkCollide(s->box, h));
    endCutscene();

}



