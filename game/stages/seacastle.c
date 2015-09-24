
/*
 *
 *  THE BEACH STAGE CASTLE
 *
 *      It's scary
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
#include "particle.h"
#include "sound.h"

#include "../game.h"
#include "seaCastle.h"


static unsigned int thunderTimer;


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


static void stageStart(void)
{


    /* standard stage startup */
    isUnderground = true;
    LOADSTAGE
    setBackgroundImage("bgSeacastle.png");
    levelExitSound = "pipe.ogg";
    preventCameraLeft = true;
    preventCameraUp = true;
    preventCameraDown = true;

    /* always add the player */
    makeMario(5 * 16, 6 * 16);
    //makeMario(142 * 16, 5 * 16);
    camera.y = camera.y + 16;
    isIcey = false;

    player->direction = RIGHT;

    // used for beach levels
    makeWaterLine(10, -100);

    // music
    playMusic("Super_Mario_World_Koopa_vs_Kefka_OC_ReMix.ogg");

    // thunder timer for windows
    thunderTimer = 0;

    // elevators
    makeHorizontalElevator(48 * 16, 5 * 16, 72 * 16, 1);
    makeHorizontalElevator(80 * 16, 11 * 16, 85 * 16, 1);
    makeClassicElevator(93 * 16, 9 * 16);
    makeClassicElevator(100 * 16, 9 * 16);
    makeClassicElevator(107 * 16, 9 * 16);
    makeClassicElevator(127 * 16, 8 * 16);
    makeTrickElevator(132 * 16, 8 * 16, 132 * 16, 0, 5);

    // custom blooper code --
    //              x    activate   y     seconds
    makeBlooper(169 * 16, 163 * 16, 10 * 16, 9);
    makeBlooper(173 * 16, 168 * 16, 10 * 16, 9);
    makeBlooper(177 * 16, 172 * 16, 10 * 16, 9);
    makeBlooper(181 * 16, 176 * 16, 10 * 16, 9);

    /* plus boss, the big bertha */
    makeBertha(196 * 16, 192 * 16, 16);
    // makeBowser2(196 * 16, 7 * 16);

}


static void stageUpdate(void)
{

    UPDATESTAGE
    updateWaterLine();

    // make water droplets from ceiling
    if (!getRandom(0, 8))
        makeDrops(16);

    // thunder
    if (thunderTimer) {
        --thunderTimer;
    } else {
        if (!getRandom(0, 50)) {
            thunderTimer = 10;
        }
    }

}


static void stageLighting(void)
{

    // employ stage lighting
    drawLightingMask(al_map_rgba_f(0.1, 0.1, 0.1, 0.9));
    drawStateLighting();

}


static void stageDraw(void)
{

    /* note - order of draw is important */
    if (thunderTimer) {
        al_draw_bitmap(bmpLib[searchForBmp("thunderstorm.png")].data, 0, 0, 0);
    }
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



void gotoSeaCastle(void) {


    newState(stageStart, playerControl, NULL, stageLighting, stageClose, stageUpdate, stageDraw);

}






