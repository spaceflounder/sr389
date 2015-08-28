#ifndef MENU_H
#define MENU_H

// header for in-game menu system

#include "allegro5/allegro_font.h"

#define MAX_MENU_COMMANDS           16



// individual menu commands
struct GAMEMENU;
struct MENUCOMMAND {

    char *text;
    char *selectedSound;

    void (*select)(struct MENUCOMMAND *cmd);
    void (*activate)(void);
    void (*draw)(struct GAMEMENU *, struct MENUCOMMAND *);

    float x;
    float y;

};


// entire menu as a struct
struct GAMEMENU {

    char *title;

    struct MENUCOMMAND command[MAX_MENU_COMMANDS];

    unsigned int active;

    int numberOfCommands;
    char *selector;
    int selectedCommandIndex;

    ALLEGRO_FONT *font;

    float x;
    float y;
    float itemHeight;
    float width;

    ALLEGRO_COLOR bgColor;

};


void closeMenu(struct GAMEMENU *menu);
void menuState(struct GAMEMENU *menu, struct CONTROLLER *controller);
void menuControl(struct GAMEMENU *menu, struct CONTROLLER *controller);
void drawMenuCommand(struct GAMEMENU *menu, struct MENUCOMMAND *cmd);
struct MENUCOMMAND *addMenuCommand(struct GAMEMENU *menu, int index, char *text, void (*activate)(void));
void drawMenu(struct GAMEMENU *menu);
void makeMenu(struct GAMEMENU *menu, char *title, ALLEGRO_COLOR color, ALLEGRO_FONT *font, char *selector, float x, float y, float width);


#endif // MENU_H

