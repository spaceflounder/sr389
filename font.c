
/*
 *
 * font.c
 *
 * font subsystem, used for with allegro
 *
 */

#include <stdio.h>
#include <stdarg.h>
#include <allegro5/allegro.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>

/* universal font name */
#define ALIENFONTNAME        "modern.ttf"
#define FONTNAME             "PressStart2P.ttf"


/* standard fonts */
ALLEGRO_FONT *font = NULL;


/* init font system, for game engine startup */
unsigned int fontInit(void) {

    /* return 1 on font init, 0 on fail */
    ALLEGRO_BITMAP *bmp = NULL;
    al_init_font_addon();
    al_init_ttf_addon();
    font = al_load_ttf_font(FONTNAME, 8, 0 );

   /* fail if load didn't work */
   if (!font){
      fprintf(stderr, "Could not load 'PressStart2P.ttf'.\n");
      return false;
   }

   al_destroy_bitmap(bmp);
   return true;

}





void print (ALLEGRO_FONT *fnt, int x, int y, char *text, ...)
{

    /* print text onscreen with default font
     * if first argument is null, use our default
     * note that there's a max 1028 chars for a string
     */
    if (fnt == NULL)
        fnt = font;
    va_list args;
    va_start (args, text);
    char formattedText[1028];
    vsprintf(formattedText, text, args);
    al_draw_text(fnt, al_map_rgb(255,255,255), x, y, ALLEGRO_ALIGN_LEFT, formattedText);
    va_end (args);

}

void printCenter(ALLEGRO_FONT *fnt, int x, int y, char *text, ...)
{

    /* print (center justified) text onscreen with default font
     * if first argument is null, use our default
     * note that there's a max 1028 chars for a string
     */
    if (fnt == NULL)
        fnt = font;
    va_list args;
    va_start (args, text);
    char formattedText[1028];
    vsprintf(formattedText, text, args);
    al_draw_text(fnt, al_map_rgb(255,255,255), x, y, ALLEGRO_ALIGN_CENTER, formattedText);
    va_end (args);

}



void printRight(ALLEGRO_FONT *fnt, int x, int y, char *text, ...)
{

    /* print (right justified) text onscreen with default font
     * if first argument is null, use our default
     * note that there's a max 1028 chars for a string
     */
    if (fnt == NULL)
        fnt = font;
    va_list args;
    va_start (args, text);
    char formattedText[1028];
    vsprintf(formattedText, text, args);
    al_draw_text(fnt, al_map_rgb(255,255,255), x, y, ALLEGRO_ALIGN_RIGHT, formattedText);
    va_end (args);

}

