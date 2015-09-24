/*
 *
 *  Seaside stage 3
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
#include "seaSide3.h"



static void stageStart(void)
{


    /* standard stage startup */
    isUnderground = true;
    LOADSTAGE
    setBackgroundImage("bgBeach.png");
    preventCameraLeft = true;
    preventCameraUp = true;
    preventCameraDown = true;

    /* always add the player */
    makeMario(2 * 16, 10 * 16);
    camera.y = camera.y - 16;
    isIcey = false;
    player->direction = RIGHT;

    /* set victory sound effect */
    levelExitSound = "pipe.ogg";

    // used for beach levels
    makeWaterLine(10, -5);
    //playMusic("Super_Mario_Galaxy_To_the_Stars_OC_ReMix.ogg");
    playMusic("Super_Mario_Bros_2_Shiitake_Kingdom_OC_ReMix.ogg");

    // custom objects
    makeQb(7 * 16, 6 * 16, poisonMushroomInTheBox);
    makeHorizontalElevator(71 * 16, 13 * 16, 72 * 16, 0.3);
    makeBlooper(93 * 16, 90 * 16, 2 * 16, 1);
    makeBlooper(202 * 16, 198 * 16, 6 * 16, 1);

    // custom cheep cheep code
    //                  x        y       activate  speed interval number
    makeCheepCheepSpawn((18 * 16), (9 * 16) + 8, 12 * 16, -2.5, 0.5, -1);
    makeCheepCheepSpawn((21 * 16), (9 * 16) + 8, 12 * 16, 2.5, 0.5, -1);
    makeCheepCheepSpawn((33 * 16), (4 * 16) + 8, 12 * 16, -2.5, 0.5, -1);
    makeCheepCheepSpawn((35 * 16), (4 * 16) + 8, 12 * 16, 2.5, 0.5, -1);
    makeCheepCheepSpawn((69 * 16), (9 * 16) + 8, 70 * 16, -2.5, 0.2, 3);
    makeCheepCheepSpawn((71 * 16), (9 * 16) + 8, 70 * 16, 2.5, 0.2, 3);
    makeCheepCheepSpawn((159 * 16), (5 * 16) + 8, 154 * 16, -4.5, 0.2, 10);
    makeCheepCheepSpawn((164 * 16), (5 * 16) + 8, 154 * 16, 4.5, 0.2, 10);


}


static void stageUpdate(void)
{

    UPDATESTAGE
    updateWaterLine();
}



static void stageDraw(void)
{

    /* note - order of draw is important */
    al_draw_bitmap(bmpLib[bgIndex].data, -(camera.x * 0.02), 0, 0);
    drawStage();
    drawWaterLine();
    drawHUD();

}


static void stageLighting(void)
{

    // employ stage lighting
    drawLightingMask(al_map_rgba_f(0.15, 0.15 + (camera.x * 0.0001), 0.15 + (camera.x * 0.0001), 0.9));
    drawStateLighting();

}


static void stageClose(void)
{

    /* activated on stage close */
    UNLOADSTAGE

}



void gotoSeaSide3(void) {


    newState(stageStart, playerControl, NULL, stageLighting, stageClose, stageUpdate, stageDraw);

}







