
/*
 *
 *
 *
 *
 *      tilelib.c
 *
 *      Tile map library for SR389
 *
 *      Includes a few convenience macros for setting up a tile stage
 *
 *
 *
 *
 *
 */



#include <stdio.h>
#include <math.h>

#include "allegro5/allegro.h"
#include "allegro5/allegro_primitives.h"

#include "draw.h"
#include "hitbox.h"
#include "sprite.h"
#include "camera.h"
#include "medlib.h"
#include "video.h"
#include "state.h"

#include "tile.h"

/* tileset graphic - load this only once, at startup */
ALLEGRO_BITMAP *tileset;


// tile map and tile dimensions
unsigned int stageWidthInTiles;
unsigned int stageHeightInTiles;
unsigned int tileWidth;
unsigned int tileHeight;


/* jiggle tiles if true - earthquake effect */
unsigned int jiggleTiles;


/* memory allocated for entire tile map */
unsigned int tileMap[MAX_LAYERS][MAX_TILEMAP_WIDTH][MAX_TILEMAP_HEIGHT][MAX_AXIS];


/* current max number of cells in the loaded hashmap */
unsigned int hashmapCellsMax;


/* collision array of hitboxes for hard tileset */
struct HASHMAP hashmap[MAX_HASHMAPS][MAX_HASHMAP_CELLS];


/* THE TILE FUNCTION LIBRARY - DUH DUH DAAAAAAAH!! */


void clearTileMap(void)
{

    // clean tile map, in between levels
    unsigned int layer;
    unsigned int axis;
    unsigned int w;
    unsigned int h;
    unsigned int index;
    unsigned int tile;
    for (layer = 0; layer < MAX_LAYERS; ++layer) {
        for (w = 0; w < MAX_TILEMAP_WIDTH; ++w) {
            for (h = 0; h < MAX_TILEMAP_HEIGHT; ++h) {
                for (axis = 0; axis < MAX_AXIS; ++axis) {
                    tileMap[layer][w][h][axis] = 0;
                }
            }
        }
    }
    for (layer = 0; layer < MAX_HASHMAPS; ++layer) {
        for (index = 0; index < MAX_HASHMAP_CELLS; ++index) {
            newHitbox(&hashmap[layer][index].area, 0, 0, 0, 0);
            hashmap[layer][index].tileNum = 0;
            for (tile = 0; tile < MAX_TILES_PER_HASH; ++tile) {
                newHitbox(&hashmap[layer][index].tile[tile], 0, 0, 0, 0);
            }
        }
    }


}


void loadTileSet(const char *filename)
{

    /* load tileset into memory - we store it in it's own location, to keep it
     * out of the image library */

    tileset = al_load_bitmap(filename);

}


void unloadTileSet(void)
{

    /* exiting game - remove tileset from memory */

    al_destroy_bitmap(tileset);

}


unsigned int checkSpriteForCell(struct SPRITE *s, unsigned int c)
{

    /* check the cell data of a sprite it see if sprite occupies a given cell on the stage */
    unsigned int i;
    for (i = 0; i < MAX_CELLS; ++i) {
        if (s->cell[i] == c) {
            return 1;
        }
    }
    return 0;

}



void drawTileLayer(const unsigned int layer, const unsigned int map_w, const unsigned int map_h)
{

    /* draw tiles on the screen */
    unsigned int x = (map_w - 1);
    unsigned int y;
    unsigned const int gx = 0;
    unsigned const int gy = 1;

    /* map axis loop
     * we defer drawing because all the tiles come from the same bitmap in memory
     * this set of loops is kind of exotic, but it's all in the name of optimization
     */
    al_hold_bitmap_drawing(true);
    do {
        --x;
        y = (map_h - 1);
        do {
            --y;
            unsigned int tileSheetOffsetX = tileMap[layer][x][y][gx];
            unsigned int tileSheetOffsetY = tileMap[layer][x][y][gy];
            if (tileSheetOffsetX || tileSheetOffsetY) {

                /* we have an active tile here in camera, draw it */

                if (checkOverlap((x * tileWidth) - floorf(camera.x), (y * tileHeight) - floorf(camera.y), tileWidth, tileHeight, 0, 0, camera.width, camera.height)) {
                    if (jiggleTiles) {
                        float jiggleX = ((float)rand()/(float)(RAND_MAX)) * 16;
                        float jiggleY = ((float)rand()/(float)(RAND_MAX)) * 16;
                        al_draw_bitmap_region(tileset, tileSheetOffsetX, tileSheetOffsetY, tileWidth, tileHeight,
                                          (x * tileWidth) - floorf(camera.x) + jiggleX, (y * tileHeight) - floorf(camera.y) + jiggleY, 0);
                    } else {
                        al_draw_bitmap_region(tileset, tileSheetOffsetX, tileSheetOffsetY, tileWidth, tileHeight,
                                      (x * tileWidth) - floorf(camera.x), (y * tileHeight) - floorf(camera.y), 0);
                    }
                }

            }

        } while (y);
    } while (x);

    al_hold_bitmap_drawing(false);

}


/* adjust sprite against hitbox, x and y */
static float spriteAdjustHitboxX(struct SPRITE *s, struct HITBOX h, const unsigned int halfTile)
{

    /* build a secondary temp hitbox for horizontal collisions */
    float halfHeight = (s->box.height / 4);
    struct HITBOX hc;
    float returnVal = 0;
    newHitbox(&hc, s->box.x, s->box.centerY, s->box.width, halfHeight);

    /* adjust horizontal - if we need to adjust vertical, we will after this */
    if (checkCollide(hc, h) && halfTile == 2) {
        if (s->box.left < h.right) {
            if (h.check[LEFT]) {
                if (s->GetVX(s) > 0) {
                    s->isTouching[RIGHT] = 2;
                    returnVal = (h.left - (s->box.width));
                }
            }
        }
        if (s->box.right > h.left) {
            if (h.check[RIGHT]) {
                if (s->GetVX(s) < 0) {
                    s->isTouching[LEFT] = 2;
                    returnVal = (h.right + 1);
                }
            }
        }
    }
    return returnVal;

}


static float spriteAdjustHitboxY(struct SPRITE *s, struct HITBOX h, const unsigned int halfTile)
{

    /* build a secondary, temp hitbox for vertical collisions */
    updateHitbox(&h);
    float returnVal = 0;

    /* adjust vertical */
    if (checkCollide(s->box, h)) {
        if (s->box.top < h.top) {
            if (h.check[UP]) {
                if (s->GetVY(s) > 0) {
                    s->isTouching[DOWN] = 2;
                    returnVal = (h.top - (s->box.height));
                }
            }
        }
        if (s->box.bottom > h.bottom) {
            if (halfTile == 2) {
                if (h.check[DOWN]) {
                    if (s->GetVY(s) < 0) {
                        s->isTouching[UP] = 2;
                        returnVal = h.bottom + 1;
                    }
                }
            }
        }
    }
    return returnVal;
}




static void spriteTileHashCheck(struct SPRITE *s)
{

    /* check the sprite for collision against tile hashmaps */
    unsigned int hardness;
    unsigned int i;
    unsigned int c;
    for (hardness = 0; hardness < MAX_HASHMAPS; ++hardness) {
        //if (s->collidable) {
            for (i = 0; i < MAX_CELLS; ++i) {
                if (s->cell[i] != BLANK_CELL) {
                    if (hashmap[hardness][s->cell[i]].tileNum) {
                        for (c = 0; c < hashmap[hardness][s->cell[i]].tileNum; ++c) {

                            if (checkCollide(s->box, hashmap[hardness][s->cell[i]].tile[c])) {

                                /* adjust sprite position now against the hitbox */
                                // x adjustments first
                                float x = spriteAdjustHitboxX(s, hashmap[hardness][s->cell[i]].tile[c], hardness + 1);
                                if (x) {
                                    s->box.x = x;
                                    updateHitbox(&s->box);
                                }

                                // now y adjustments
                                float y = spriteAdjustHitboxY(s, hashmap[hardness][s->cell[i]].tile[c], hardness + 1);
                                if (y) {
                                    s->box.y = y;
                                    updateHitbox(&s->box);
                                }
                                if (x || y)
                                    return;

                            }
                        }
                    }

                }
            }
        //}
    }

}


static void markCell(struct SPRITE *s, unsigned int c)
{

    /* mark sprite within one of the hashmap cells */
    unsigned int i;
    for (i = 0; i < MAX_CELLS; ++i) {
        if (s->cell[i] == BLANK_CELL) {
            s->cell[i] = c;
            return;
        }
    }

}


static void spriteUpdateHashmap(struct SPRITE *s)
{

    /* update sprite collision hashmap with tilemap */
    unsigned int c;
    unsigned int i;
    for (c = 0; c < MAX_CELLS; ++c) {
        s->cell[c] = BLANK_CELL;
    }
    for (i = 0; i < hashmapCellsMax; ++i) {
        if (checkCollide(s->box, hashmap[HASHMAP_HARD][i].area)) {

            /* sprite is in this area, mark it */
            markCell(s, i);

        }
    }

}


void updateStageSprites(void)
{

    /* check primary sprite array against hashmaps and other groundtile-type sprites */
    int i, k;
    for (i = 0; i < MAX_SPRITES; ++i) {
        if (sprites[i].__internal__alive) {
            if (sprites[i].collidable) {
                spriteUpdateHashmap(&sprites[i]);
                if (!sprites[i].groundTile) {
                    if (sprites[i].solid)
                        spriteTileHashCheck(&sprites[i]);

                    /* check all other sprites in this layer against the one
                       do two checks - one for sprite collision routines, next for sprite hardness */
                    for (k = 0; k < MAX_SPRITES; ++k) {
                        if (sprites[k].__internal__alive && i != k && sprites[k].collidable) {
                            if (commonCell(&sprites[i], &sprites[k])) {
                                if (sprites[i].collides(&sprites[i], &sprites[k])) {
                                    if (collsionTable[sprites[i].id][sprites[k].id]) {
                                        collsionTable[sprites[i].id][sprites[k].id](&sprites[i], &sprites[k]);
                                    }
                                }
                            }
                        }
                    }

                    for (k = 0; k < MAX_SPRITES; ++k) {
                        if (sprites[k].__internal__alive && i != k && sprites[k].collidable) {
                            if (commonCell(&sprites[i], &sprites[k])) {
                                if (sprites[i].collides(&sprites[i], &sprites[k])) {
                                    if (sprites[k].groundTile) {
                                        if (sprites[i].solid) {

                                            /* adjust sprite position now against the hitbox */
                                            // x adjustments first
                                            float x = spriteAdjustHitboxX(&sprites[i], sprites[k].box, sprites[k].groundTile);
                                            if (x) {
                                                sprites[i].box.x = floorf(x);
                                                updateHitbox(&sprites[i].box);
                                            }

                                            // now y adjustments
                                            float y = spriteAdjustHitboxY(&sprites[i], sprites[k].box, sprites[k].groundTile);
                                            if (y) {
                                                sprites[i].box.y = floorf(y);
                                                updateHitbox(&sprites[i].box);
                                            }


                                        }
                                    }
                                }
                            }
                        }
                    }


                }
            }
        }
    }

}


/* draw stage -- draw current tile stage */
void drawStage(void)
{

    // the order is important, because we need back to front
    // defer drawing for better gpu use
    setSpriteOrder();
    handleShakeyCam();
    finalizeDrawLayer(0);
    al_hold_bitmap_drawing(true);
    DRAWBACK
    al_hold_bitmap_drawing(false);

    // tiles
    finalizeDrawLayer(1);
    finalizeDrawLayer(2);
    finalizeDrawLayer(3);
    al_hold_bitmap_drawing(true);
    DRAWTILES
    al_hold_bitmap_drawing(false);
    finalizeDrawLayer(4);
    finalizeDrawLayer(5);
    finalizeDrawLayer(6);

    // foreground
    DRAWFORE
    al_hold_bitmap_drawing(false);
    finalizeDrawLayer(7);

}




/* check sprite sides for possible collision */
unsigned int checkSide(struct SPRITE *s, unsigned int side)
{

    /* we've defined a local hitbox on the stack to check for possible collision with either tile layer */
    unsigned int i;
    unsigned int t;
    unsigned int cell;
    struct HITBOX h;
    switch (side) {
    case LEFT:
        newHitbox(&h, s->box.left - s->GetMaxSpeedX(s), s->box.centerY, s->GetMaxSpeedX(s), 1);
        break;
    case RIGHT:
        newHitbox(&h, s->box.right, s->box.centerY, s->GetMaxSpeedX(s), 1);
        break;
    case UP:
        newHitbox(&h, s->box.centerX, s->box.top - 2, 1, 2);
        break;
    case LOWERLEFT:
        newHitbox(&h, s->box.left - s->GetMaxSpeedX(s), s->box.bottom, s->GetMaxSpeedX(s), 1);
        break;
    case LOWERRIGHT:
        newHitbox(&h, s->box.right, s->box.bottom, s->GetMaxSpeedX(s), 1);
        break;
    case UPPERLEFT:
        newHitbox(&h, s->box.left - s->GetMaxSpeedX(s), s->box.top, s->GetMaxSpeedX(s), 1);
        break;
    case UPPERRIGHT:
        newHitbox(&h, s->box.right, s->box.top, s->GetMaxSpeedX(s), 1);
        break;
    default:
        newHitbox(&h, s->box.centerX, s->box.bottom + 1, 1, 1);
        break;
    }

    /* now check all the cells in the map to see if our local hitbox falls into one of the cells */
    for (i = 0; i < hashmapCellsMax; ++i) {

            if (checkCollide(h, hashmap[HASHMAP_HARD][i].area)) {

                /* we've hit a cell. now check for collision with all the tiles in it */
                cell = i;
                if (hashmap[HASHMAP_HARD][i].tileNum > 0) {

                    for (t = 0; t < hashmap[HASHMAP_HARD][i].tileNum; ++t) {
                        if (checkCollide(h, hashmap[HASHMAP_HARD][i].tile[t]))

                            /* side is blocked. return true */
                            return 1;

                    }
                }
            }
    }

    /* finally, look at all objects for possible collision */
    for (i = 0; i < MAX_SPRITES; ++i) {

        /* otherwise continue checks */
        if (sprites[i].groundTile == 2) {
            if (checkSpriteForCell(&sprites[i], cell))
            {
                if (checkCollide(h, sprites[i].box))
                {

                    /* object collision here, return true */
                    return 1;

                }
            }
        }

    }

    /* no collision, return 0 */
    return 0;

}


