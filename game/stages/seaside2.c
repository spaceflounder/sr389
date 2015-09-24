/*
 *
 *  Ice world stage 1
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
#include "seaSide2.h"



static void stageStart(void)
{


    /* standard stage startup */
    isUnderground = false;
    LOADSTAGE
    setBackgroundImage("bgBeach.png");
    preventCameraLeft = true;
    preventCameraUp = true;
    preventCameraDown = true;

    /* always add the player */
    makeMario(5 * 16, 9 * 16);
    camera.y = camera.y + 16;
    isIcey = false;
    player->direction = RIGHT;

    /* set victory sound effect */
    levelExitSound = "walking.ogg";

    // used for beach levels
    makeWaterLine(10, -1);
    playMusic("beach.ogg");

    // custom cheep cheep code
    //                  x        y       activate  speed interval number
    makeCheepCheepSpawn((35 * 16), 2 * 16, 30 * 16, -2.5, 0.5, 5);
    makeCheepCheepSpawn((39 * 16), 2 * 16, 30 * 16, 2.5, 0.5, 5);
    makeCheepCheepSpawn((49 * 16), 6 * 16, 30 * 16, -2.5, 0.5, -1);
    makeCheepCheepSpawn((51 * 16), 6 * 16, 30 * 16, 2.5, 0.5, -1);
    makeCheepCheepSpawn((87 * 16), 3 * 16, 86 * 16, -2.5, 0.3, -1);
    makeCheepCheepSpawn((89 * 16), 3 * 16, 89 * 16, 2.5, 1, -1);
    makeCheepCheepSpawn((105 * 16), 6 * 16, 105 * 16, -4, 0.2, -1);
    makeCheepCheepSpawn((109 * 16), 6 * 16, 105 * 16, 4, 0.2, -1);
    makeCheepCheepSpawn((128 * 16), 2 * 16, 124 * 16, -2.5, 0.3, -1);
    makeCheepCheepSpawn((130 * 16), 2 * 16, 124 * 16, 2.5, 0.3, -1);
    makeCheepCheepSpawn((139 * 16), 5 * 16, 124 * 16, -5.5, 0.5, -1);
    makeCheepCheepSpawn((141 * 16), 5 * 16, 147 * 16, 2.5, 0.3, -1);
    makeCheepCheepSpawn((148 * 16), 3 * 16, 140 * 16, -2.5, 0.5, 3);
    makeCheepCheepSpawn((152 * 16), 3 * 16, 140 * 16, 2.5, 0.5, -1);
    makeCheepCheepSpawn((159 * 16), 5 * 16, 159 * 16, -4.5, 0.2, -1);
    makeCheepCheepSpawn((161 * 16), 5 * 16, 159 * 16, 4.5, 2.5, 2);
    makeCheepCheepSpawn((166 * 16), 5 * 16, 159 * 16, -4.5, 1.7, 2);
    makeCheepCheepSpawn((170 * 16), 5 * 16, 159 * 16, 4.5, 0.2, -1);
    makeCheepCheepSpawn((191 * 16), 7 * 16, 191 * 16, 4.5, 1, 1);
    makeCheepCheepSpawn((208 * 16), 5 * 16, 192 * 16, -4.5, 1, 1);

    // custom blooper code --
    //              x    activate   y     seconds
    makeBlooper(66 * 16, 64 * 16, 5 * 16, 3);
    makeBlooper(99 * 16, 94 * 16, 2 * 16, 1);
    makeBlooper(156 * 16, 150 * 16, 0, 1);
    makeBlooper(205 * 16, 200 * 16, 5 * 16, 1);


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


static void stageClose(void)
{

    /* activated on stage close */
    UNLOADSTAGE

}



void gotoSeaSide2(void) {


    newState(stageStart, playerControl, NULL, NULL, stageClose, stageUpdate, stageDraw);

}






