/*
 *
 *
 *      DRAW.C
 *
 *
 *      Ordered draw functions for SR389
 *      This allows us a poor man's zbuffering
 *
 *
 *
 */

#include "allegro5/allegro.h"

#include "camera.h"
#include "medlib.h"
#include "sprite.h"


#define DRAW_LAYERS                 8
#define MAX_DRAW_INSTRUCTIONS       32768

static struct {

    /* a local struct acts as our instructions database */

    struct SPRITE *s[DRAW_LAYERS][MAX_DRAW_INSTRUCTIONS];

    unsigned int numberOfInstructions[DRAW_LAYERS];

} draws;


void addSpriteToLayer(const unsigned int layer, struct SPRITE *s)
{

    /* add sprite to draw instruction stack */
    draws.s[layer][draws.numberOfInstructions[layer]] = s;
    ++draws.numberOfInstructions[layer];

}


void resetDrawLayer(const unsigned int layer)
{

    /* reset draw system, so we can use it in next state */
    draws.numberOfInstructions[layer] = 0;

}


void resetAllDrawLayers(void)
{

    /* return all draw layers to blank, no instructions */
    unsigned int i;
    for (i = 0; i < DRAW_LAYERS; ++i) {
        resetDrawLayer(i);
    }

}


void finalizeDrawLayer(const unsigned int layer)
{

    /* finalize draw instructions, outputting sprites in layer to screen */
    unsigned int i;
    al_hold_bitmap_drawing(true);
    for (i = 0; i < draws.numberOfInstructions[layer]; ++i) {
        if (draws.s[layer][i]->draw)
            draws.s[layer][i]->draw(draws.s[layer][i]);
    }
    al_hold_bitmap_drawing(false);

    // prep for next draw cycle already
    resetDrawLayer(layer);

}



#undef DRAW_LAYERS
#undef MAX_DRAW_INSTRUCTIONS
