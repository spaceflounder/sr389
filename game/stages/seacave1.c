
/*
 *
 *  Underground world 2-2
 *
 *
 */

#include <stdio.h>
#include "allegro5/allegro.h"
#include "allegro5/allegro_audio.h"
#include "allegro5/allegro_acodec.h"


#include "state.h"
#include "font.h"
#include "video.h"
#include "camera.h"
#include "sprite.h"
#include "tile.h"
#include "hitbox.h"
#include "sound.h"
#include "particle.h"

#include "../game.h"
#include "./seaCave1.h"


unsigned int bgBrightness;
unsigned int bgFlickerFlag;



static void makeDrops(float dropFromY)
{

    /* make droplets appear on screen, from position y */
    float x = ((float)rand()/(float)(RAND_MAX)) * (screenWidth * 1.5);
    x = x + camera.x;
    struct SPRITE *p = getNewParticle(x, dropFromY, 0, 0, 0.01, 0, 0.01, "droplet.png",
                   al_map_rgba_f(1, 1, 1, 1), al_map_rgba_f(0.7, 0.7, 0.8, 0.7), al_map_rgba_f(0.1, 0.1, 0.2, 0.1));
    p->SetAY(p, 0.1);
    p->__internal__z = 0;

}



static void drawTorches(void)
{

    /* draw a few torches on the screen on the cave wall */
    const unsigned int torchImg = searchForBmp("torch.png");
    al_draw_bitmap(bmpLib[torchImg].data, 36, 105, 0);
    al_draw_bitmap(bmpLib[torchImg].data, 90, 121, 0);
    al_draw_bitmap(bmpLib[torchImg].data, 154, 100, 0);
    al_draw_bitmap(bmpLib[torchImg].data, 205, 116, 0);
    al_draw_bitmap(bmpLib[torchImg].data, 236, 112, 0);
    al_draw_bitmap(bmpLib[torchImg].data, 278, 122, 0);
    al_draw_bitmap(bmpLib[torchImg].data, 360, 112, 0);
    al_draw_bitmap(bmpLib[torchImg].data, 420, 120, 0);

}


static void stageLighting(void)
{

    // employ stage lighting
    drawLightingMask(al_map_rgba_f(0.15, 0.15, 0.15, 0.9));
    drawStateLighting();

}


static void stageStart(void)
{


    /* standard stage startup */
    isUnderground = true;
    LOADSTAGE
    preventCameraLeft = true;
    preventCameraUp = true;
    preventCameraDown = true;
    setBackgroundImage("bgCave.png");
    levelExitSound = "pipe.ogg";

    /* always add the player */
    makeMario(4 * 16, 7 * 16);
    camera.y = camera.y + 16;
    isIcey = false;

    player->direction = RIGHT;

    /* set victory sound effect */
    levelExitSound = "walking.ogg";

    /* play super cool mario music at stage start */
    playMusic("Super_Mario_Bros_Water_Main_OC_ReMix.ogg");

    // torches
    bgBrightness = 250;
    bgFlickerFlag = false;

    // specialty objects
    makeHorizontalElevator(175 * 16, 9 * 16, 190 * 16, 1.5);
    makeBlooper(34 * 16, 24 * 16, 4 * 16, 1);


}


static void stageUpdate(void)
{

    // make water droplets from ceiling
    if (!getRandom(0, 8))
        makeDrops(8);

    UPDATESTAGE

}



static void stageDraw(void)
{

    /* note - order of draw is important */

    /* draw cave background */
    al_draw_tinted_bitmap(bmpLib[bgIndex].data, al_map_rgba(bgBrightness, bgBrightness, bgBrightness, bgBrightness), 0, 0, 0);
    drawTorches();
    if (bgFlickerFlag > 60)
    {
        --bgBrightness;
    }
    else
    {
        ++bgBrightness;
    }
    if (!bgFlickerFlag)
    {
        bgFlickerFlag = 120;
        bgBrightness = 250;
    }
    bgFlickerFlag--;

    // and the rest of the stage on top of bg
    drawStage();
    drawHUD();

}


static void stageClose(void)
{

    /* activated on stage close */
    UNLOADSTAGE

}



void gotoSeaCave1(void) {


    newState(stageStart, playerControl, NULL, stageLighting, stageClose, stageUpdate, stageDraw);

}






