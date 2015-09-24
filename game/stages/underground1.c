
/*
 *
 *  Underground world 1-3
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

#include "../game.h"
#include "./game/stages/undeground1.h"


unsigned int bgBrightness;
unsigned int bgFlickerFlag;


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

    /* always add the player */
    makeMario(1 * 16, 5 * 16);
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
    makeQb(14 * 16, 6 * 16, poisonMushroomInTheBox);
    makeQb(16 * 16, 6 * 16, poisonMushroomInTheBox);
    makeQb(32 * 16, 7 * 16, poisonMushroomInTheBox);
    makeQb(62 * 16, 4 * 16, poisonMushroomInTheBox);
    makeQb(127 * 16, 4 * 16, poisonMushroomInTheBox);
    makeQb(143 * 16, 6 * 16, poisonMushroomInTheBox);
    makeTrickElevator(66 * 16, 8 * 16, 67 * 16, 0, 1.5);
    makeTrickElevator(72 * 16, 8 * 16, 72 * 16, 0, 3);
    makeTrickElevator(146 * 16, 2 * 16, 146 * 16, 2, 0);

}


static void stageUpdate(void)
{

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



void gotoUnderground1(void) {


    newState(stageStart, playerControl, NULL, stageLighting, stageClose, stageUpdate, stageDraw);

}





