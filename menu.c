/*
 *
 *
 *
 *
 *
 *      MENU.C
 *
 *
 *      In-game menu system
 *
 *
 *
 *
 *
 *
 *
 *
 *
 *
 */


#include <stdio.h>

#include "allegro5/allegro5.h"
#include "allegro5/allegro_primitives.h"

#include "sprite.h"
#include "control.h"
#include "font.h"
#include "medlib.h"
#include "menu.h"




// default menu border size, can be changed here
static float borderSize = 8;


void menuState(struct GAMEMENU *menu, struct CONTROLLER *controller)
{

    /* create a pseudo game state for a menu */
    menuControl(menu, controller);
    drawMenu(menu);

}



void drawMenuCommand(struct GAMEMENU *menu, struct MENUCOMMAND *cmd)
{

    // draw individual menu command
    print(menu->font, menu->x + cmd->x, menu->y + cmd->y, cmd->text);

}


void closeMenu(struct GAMEMENU *menu __attribute__ ((unused)))
{

    // close menu when we're done with it


}



void menuControl(struct GAMEMENU *menu, struct CONTROLLER *controller)
{

    // default menu control system
    if (isKeyReleased(UP, controller)) {
        if (menu->selectedCommandIndex > 0) {
            --menu->selectedCommandIndex;
        }
    }
    if (isKeyReleased(DOWN, controller)) {
        if (menu->selectedCommandIndex < (menu->numberOfCommands - 1)) {
            ++menu->selectedCommandIndex;
        }
    }
    if (isKeyReleased(BUTTON_A, controller)) {
        if (menu->command[menu->selectedCommandIndex].activate) {
            closeMenu(menu);
            menu->command[menu->selectedCommandIndex].activate();
        }
    }

}


struct MENUCOMMAND *addMenuCommand(struct GAMEMENU *menu, int index, char *text, void (*activate)(void))
{

    // new menu command
    menu->command[index].x = borderSize + (menu->itemHeight * 2);
    menu->command[index].y = borderSize + (menu->itemHeight * 2) +
            (menu->numberOfCommands * (menu->itemHeight + 2));
    menu->command[index].text = text;
    menu->command[index].activate = activate;
    menu->command[index].draw = drawMenuCommand;
    ++menu->numberOfCommands;
    return &menu->command[index];

}


void makeMenu(struct GAMEMENU *menu, char *title, ALLEGRO_COLOR color, ALLEGRO_FONT *font, char *selector, float x, float y, float width)
{

    // create a new menu for in-game
    menu->title = title;
    menu->bgColor = color;
    menu->x = x;
    menu->y = y;
    menu->width = width;
    menu->numberOfCommands = 0;
    menu->selectedCommandIndex = 0;
    menu->font = font;
    menu->itemHeight = font->height;
    menu->active = true;
    menu->selector = selector;
    int i;
    for (i = 0; i < MAX_MENU_COMMANDS; ++i) {
        menu->command[i].activate = NULL;
        menu->command[i].draw = NULL;
        menu->command[i].select = NULL;
        menu->command[i].selectedSound = "";
        menu->command[i].text = "";
        menu->command[i].x = 0;
        menu->command[i].y = 0;
    }

}


void drawMenu(struct GAMEMENU *menu)
{

    /* draw in-game menu */
    int i = 0;
    al_draw_filled_rectangle(menu->x, menu->y, menu->x + menu->width, menu->y + ((menu->numberOfCommands + 2) * menu->itemHeight) + (borderSize * 2), menu->bgColor);
    printCenter(menu->font, menu->x + (menu->width / 2), menu->y + borderSize, menu->title);
    for (i = 0; i < menu->numberOfCommands; ++i) {
        menu->command[i].draw(menu, &menu->command[i]);
    }
    al_draw_bitmap(bmpLib[searchForBmp(menu->selector)].data, menu->x + borderSize, menu->y + borderSize + (menu->itemHeight * 2) + (menu->selectedCommandIndex * (menu->itemHeight + 2)), 0);

}


