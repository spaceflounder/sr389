
/*
 *
 *    Desert stage 03
 *
 *
 */

#include <stdio.h>
#include <math.h>
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
#include "./jeff3Mod.h"



static void desertHaze(unsigned int index)
{

    /* get background from index number, then create a "heat haze"
     * distortion effect
     */

    float y;
    unsigned int i;
    al_draw_bitmap(bmpLib[index].data, 0, 10, 0);
    for (i = screenHeight; i > 10; --i)
    {
        y = sin((elapsed() * 10) + y) + i + 10;
        al_draw_bitmap_region(bmpLib[index].data, 0, i + 10, screenWidth, 1, 0, y + 10, 0);
    }

}


static void stageStart(void)
{


    /* standard stage startup */
    isUnderground = false;
    LOADSTAGE
    bgIndex = searchForBmp("bgDesert.png");
    preventCameraLeft = true;
    preventCameraUp = true;
    preventCameraDown = true;

    /* always add the player */
    makeMario(2 * 16, 8 * 16);
    levelExitSound = "walking.ogg";

    isIcey = false;

    // stage music
    playMusic("Super_Mario_World_2_Yoshi's_Island_Indian_Ragga_OC_ReMix.ogg");

}


static void stageUpdate(void)
{


    // only do normal updates if player is alive
    UPDATESTAGE
}



static void stageDraw(void)
{

    /* note - order of draw is important */
    desertHaze(bgIndex);
    drawStage();
    drawHUD();

}


static void stageClose(void)
{

    /* activated on stage close */
    UNLOADSTAGE

}



void gotoJeff3(void) {

    /* go to ice 1 stage */
    newState(stageStart, playerControl, NULL, NULL, stageClose, stageUpdate, stageDraw);


}








