
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
#include "particle.h"

#include "../game.h"
#include "ice1.h"


/* snowy effect, back and front of screen */
#define MAX_SNOW                512

struct HITBOX snowBack[MAX_SNOW];
struct HITBOX snowFront[MAX_SNOW];
unsigned int snowTimer;
unsigned int snowIndex;


ALLEGRO_COLOR stage_backColor;


// each level gets a unique integer indentifier
static const unsigned int levelID = 1;


static void makeSnow(void)
{

    /* make two snowflakes - one back, one front */
    if (snowIndex >= MAX_SNOW) {
        snowIndex = 0;
    }
    else
    {
        int newSnowLocation;
        newSnowLocation = getRandom(0, 500);
        newHitbox(&snowBack[snowIndex], newSnowLocation, -5, 5, 3);
        snowBack[snowIndex].width = ((float)rand()/(float)(RAND_MAX)) * 3;
        snowBack[snowIndex].height = ((float)rand()/(float)(RAND_MAX)) * 1;
        newSnowLocation = getRandom(0, 500);
        newHitbox(&snowFront[snowIndex], newSnowLocation, -5, 5, 3);
        snowFront[snowIndex].width = ((float)rand()/(float)(RAND_MAX)) * 3;
        snowFront[snowIndex].height = ((float)rand()/(float)(RAND_MAX)) * 1;
        ++snowIndex;
    }

}

static void updateSnow(void)
{

    /* update routine for both front and back snow effect layers */
    unsigned int i;
    if (!snowTimer--)
    {
        snowTimer = 25;
        for (i = 0; i < 2; ++i)
        {
            makeSnow();
        }

    }
    for (i = 0; i < MAX_SNOW; ++i)
    {
        float calcSnowDrift;
        calcSnowDrift = getRandom(-10, 1) / 100;
        snowBack[i].x = snowBack[i].x + calcSnowDrift;
        snowFront[i].x = snowFront[i].x - 0.1;
        snowBack[i].y = snowBack[i].y + 0.2;
        snowFront[i].y = snowFront[i].y + 0.2;
        snowBack[i].width = snowBack[i].width + 0.01;
        snowFront[i].width = snowFront[i].width + 0.01;
        snowBack[snowIndex].height = ((float)rand()/(float)(RAND_MAX)) * 1;
        snowFront[snowIndex].height = ((float)rand()/(float)(RAND_MAX)) * 1;
        updateHitbox(&snowBack[i]);
        updateHitbox(&snowFront[i]);
    }

}

static void drawSnow(struct HITBOX snowLayer[])
{

    /* draw one layer of snow */
    int snowyGraphic = searchForBmp("snow.png");
    unsigned int i = MAX_SNOW;
    do {
        --i;
        struct HITBOX current = snowLayer[i];
        //al_draw_bitmap(bmpLib[snowyGraphic].data, current.x, current.y, 0);
        //al_draw_rotated_bitmap(bmpLib[snowyGraphic].data, 0, 0, current.x, current.y, current.width, 0);
        al_draw_scaled_rotated_bitmap(bmpLib[snowyGraphic].data, 0, 0, current.x, current.y, current.height, current.height, current.width, 0);
    } while (i);

}



static void stageStart(void)
{

    /* standard stage startup */
    isUnderground = true;
    LOADSTAGE
    preventCameraLeft = true;
    preventCameraUp = true;
    preventCameraDown = true;

    /* always add the player */
    makeMario(5 * 16, 10 * 16);
    player->direction = RIGHT;

    /* ice level, player is slidey, plus prep snow */
    setBackgroundImage("bgTrees.png");
    playMusic("SunkenSecrets.ogg");
    //player->movement.dx = 0.01;
    isIcey = true;
    snowTimer = 0;
    snowIndex = 0;
    int i;
    for (i = 0; i < (MAX_SNOW / 2); ++i)
    {
        snowBack[i].x = getRandom(0, 420);
        snowFront[i].x = getRandom(0, 420);
        snowBack[i].y = getRandom(0, 240);
        snowFront[i].y = getRandom(0, 240);
        updateHitbox(&snowBack[i]);
        updateHitbox(&snowFront[i]);
    }


}


static void stageUpdate(void)
{

    /* make stage get a bit lighter as player gets closer to the end */
    int lighter = (int)camera.x * 0.01;
    stage_backColor = al_map_rgb(175 - lighter, 175 - lighter - lighter, 250 - lighter - lighter);

    /* custom snow effect - for ice stages */
    updateSnow();

    // only do normal updates if player is alive
    if (!isPlayerDying) {
        updateState();
    } else {
        player->update(player);
        updateFX();
    }
    UPDATESTAGE
}





static void stageDraw(void)
{

    /* use this one to draw stage */
    al_clear_to_color(stage_backColor);
    ALLEGRO_COLOR tint = al_map_rgba(255 - ((int)camera.x * 0.05), 255 - ((int)camera.x * 0.05), 255 - ((int)camera.x * 0.05), 255 - ((int)camera.x * 0.05));
    al_draw_tinted_bitmap(bmpLib[bgIndex].data, tint, 40, 165 - (player->box.y * 0.02), 0);
    al_hold_bitmap_drawing(true);
    drawSnow(snowBack);
    DRAWBACK
    drawStateBack();
    DRAWTILES
    drawSnow(snowFront);
    DRAWFORE
    drawStateFront();
    al_hold_bitmap_drawing(false);
    drawHUD();

}


static void stageClose(void)
{

    /* activated on stage close */
    UNLOADSTAGE

}



void gotoIce1(void) {

    /* go to ice 1 stage */
    newState(stageStart, playerControl, NULL, NULL, stageClose, stageUpdate, stageDraw);

}




