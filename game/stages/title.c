/*
 *
 *
 *
 *      TITLE.C
 *
 *
 *      Title screen -- "SUPER EVIL LAND"
 *
 *
 *
 *
 */

#include <stdio.h>
#include <stdlib.h>

#include "allegro5/allegro.h"

#include "control.h"
#include "font.h"
#include "menu.h"
#include "state.h"

#include "game/game.h"


// title menu
static struct GAMEMENU menu;

// title background
static unsigned int bgTitleIndex = 0;
static float fadeTitleValue;
static const float fadeTitleIncrement = 0.005;

// string buffers for file display
static char buffer[16];
static char fileA[32];
static char fileB[32];
static char fileC[32];

// fade in number for logo
static float fadeValue;
static const float fadeIncrement = 0.01;
static unsigned int logoGraphicIndex;


/* menu options */
static void theGameBegins(void)
{
    loadGame();
    nextState(gotoOverworld);
}

static void startGameMenuItemA(void)
{

    /* start new game */
    setSaveFile("selA.sav");
    theGameBegins();

}
static void startGameMenuItemB(void)
{

    /* start new game */
    setSaveFile("selB.sav");
    theGameBegins();

}
static void startGameMenuItemC(void)
{

    /* start new game */
    setSaveFile("selC.sav");
    theGameBegins();

}

static void exitGameMenuItem(void)
{

    /* exit game */
    state.terminate = true;
    state.nextState = NULL;

}

static void controlMapMenuItem(void)
{

    /* prep for mapping controls */
    al_rest(1);
    gotoControlMappingMenu();

}


static void makeMainMenu(void);
static void makeFileMenu(void)
{

    /* file menu load */
    makeMenu(&menu, "File Select", al_map_rgba_f(0.1, 0.1, 0.1, 0.8), font, "selector.png", 110, 100, 200);
    addMenuCommand(&menu, 0, fileA, startGameMenuItemA);
    addMenuCommand(&menu, 1, fileB, startGameMenuItemB);
    addMenuCommand(&menu, 2, fileC, startGameMenuItemC);
    addMenuCommand(&menu, 3, "Delete File", NULL);
    addMenuCommand(&menu, 4, "Back", makeMainMenu);

}


static void getSaveFileStats(char *filename)
{

    /* retrieve save file stats -- last world and level completed */
    FILE *f;
    unsigned int w;
    unsigned int l;
    buffer[0] = '\0';
    f = fopen(filename, "r");
    if (f) {
        fscanf(f, " %u  %u ", &w, &l);
        sprintf(buffer, "World %u-%u", w + 1, l + 1);
        fclose(f);
    } else {
        strcpy(buffer, "empty");
    }

}


static void makeMainMenu(void)
{

    /* set main menu for title screen */
    makeMenu(&menu, "", al_map_rgba_f(0.1, 0.1, 0.1, 0.8), font, "selector.png", 110, 100, 200);
    addMenuCommand(&menu, 0, "Game Start!", makeFileMenu);
    addMenuCommand(&menu, 1, "Speedrunner Mode", NULL);
    addMenuCommand(&menu, 2, "Set Controls", controlMapMenuItem);
    addMenuCommand(&menu, 3, "Set Sound Volume", NULL);
    addMenuCommand(&menu, 4, "Set Music Volume", NULL);
    addMenuCommand(&menu, 5, "Quit", exitGameMenuItem);

}


/* main title state routines */
static void titleControl(struct CONTROLLER *controller)
{

    /* allow player to manipulate the menu system -- escape quits also */
    if (isKeyReleased(BUTTON_E, controller)) {
        state.terminate = true;
        state.nextState = NULL;
    }
    menuControl(&menu, controller);

}


static void draw(void)
{

    /* draw title state */
    al_draw_tinted_bitmap(bmpLib[bgTitleIndex].data,
                          al_map_rgba_f(fadeTitleValue, fadeTitleValue, fadeTitleValue, fadeTitleValue),
                          0, 0,
                          0);
    drawState();
    drawMenu(&menu);
    al_draw_tinted_bitmap(bmpLib[logoGraphicIndex].data,
                          al_map_rgba_f(fadeValue, fadeValue, fadeValue, fadeValue),
                          80, (40 * fadeValue) - 20,
                          0);

}


static void update(void)
{

    /* update title state */
    if (fadeValue < 1) {
        fadeValue = fadeValue + fadeIncrement;
    }
    if (fadeTitleValue < 1) {
        fadeTitleValue = fadeTitleValue + fadeTitleIncrement;
    }
    updateState();

}





static void startTitle(void)
{

    /* start title state */
    fadeValue = 0;
    fadeTitleValue = 0;
    logoGraphicIndex = searchForBmp("logo.png");
    bgTitleIndex = searchForBmp("bgTitle.png");
    makeMainMenu();

    /* pull file stats from the current games in progress */
    buffer[0] = '\0';
    getSaveFileStats("selA.sav");
    sprintf(fileA, "File A ... %s", buffer);
    getSaveFileStats("selB.sav");
    sprintf(fileB, "File B ... %s", buffer);
    getSaveFileStats("selC.sav");
    sprintf(fileC, "File C ... %s", buffer);

}


void gotoTitle(void) {

    newState(startTitle, titleControl, NULL, NULL, NULL, update, draw);

}

