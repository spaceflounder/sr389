#ifndef FONT_H
#define FONT_H


/*
 * font system header file
 *
 */

#include <allegro5/allegro.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>


// standard font for display
extern ALLEGRO_FONT *font;


// functions
unsigned int fontInit(void);
void print (ALLEGRO_FONT *fnt, int x, int y, char *text,...);
void printRight(ALLEGRO_FONT *fnt, int x, int y, char *text, ...);
void printCenter(ALLEGRO_FONT *fnt, int x, int y, char *text, ...);


#endif // FONT_H
