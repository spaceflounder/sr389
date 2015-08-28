#ifndef TILELIB_H
#define TILELIB_H

/* header for tile library */

#include "sprite.h"
#include "camera.h"
#include "medlib.h"
#include "sound.h"

/* tile map in memory */
#define MAX_LAYERS              5
#define MAX_TILEMAP_WIDTH       512
#define MAX_TILEMAP_HEIGHT      512
#define MAX_AXIS                2
#define AXIS_X                  0
#define AXIS_Y                  1
#define MAX_HASHMAP_CELLS       256
#define MAX_HASHMAPS            2
#define LAYER_BG                0
#define LAYER_HARD              1
#define LAYER_SOFT              2
#define LAYER_FG                3
#define LAYER_OBJ               4
#define HASHMAP_SOFT            0
#define HASHMAP_HARD            1
#define MAX_TILES_PER_HASH      64
extern unsigned int tileMap[MAX_LAYERS][MAX_TILEMAP_WIDTH][MAX_TILEMAP_HEIGHT][MAX_AXIS];


/* hashmap for sprite-tile collisions */
struct HASHMAP {
    struct HITBOX tile[MAX_TILES_PER_HASH];
    struct HITBOX area;
    unsigned int tileNum;
};
extern struct HASHMAP hashmap[MAX_HASHMAPS][MAX_HASHMAP_CELLS];


#define BLANK_CELL          255

/* current number of cells in the level hashmap */
extern unsigned int hashmapCellsMax;

// stage width and height
extern unsigned int stageWidthInTiles;
extern unsigned int stageHeightInTiles;


// tile width and height, usually 16x16 px
extern unsigned int tileWidth;
extern unsigned int tileHeight;

// is stage shaking?
extern unsigned int jiggleTiles;


/*
 * sprite-tile update and check
 */
#define UPDATESTAGE    updateState(); updateStageSprites();


/* special macro - will draw the tiles in any stage that calls for it, using the SR389
 * engine tile format
 */

#define DRAWBACKIMG                 if (bgIndex != -1) al_draw_bitmap(bmpLib[bgIndex].data, 0, 0, 0);
#define DRAWBACK                    drawTileLayer(0, stageWidthInTiles, stageHeightInTiles);
#define DRAWTILES                   drawTileLayer(1, stageWidthInTiles, stageHeightInTiles);drawTileLayer(2, stageWidthInTiles, stageHeightInTiles);
#define DRAWFORE                   drawTileLayer(3, stageWidthInTiles, stageHeightInTiles);

/* macro to check sprite sides against the present tilemap */
#define CHECKSIDE(x1, x2)                checkSide(x1, x2)



/*  macro for loading objects and tiles from tiled
 *
 */
#define LOADSTAGE                    jiggleTiles = false; bgIndex = -1; initCamera(); clearTileMap(); loadSR389Map(); loadObjs(); setCameraBounds((stageWidthInTiles * tileWidth), stageHeightInTiles * tileHeight);
#define UNLOADSTAGE                  clearSpecialMsg();



/* function interface for SR389 tile library */
void clearTileMap(void);
void loadTileSet(const char *filename);
void unloadTileSet(void);
void drawTileLayer(const unsigned int layer, const unsigned int map_w, const unsigned int map_h);
void drawStage(void);
void updateStageSprites(void);
unsigned int checkSpriteForCell(struct SPRITE *s, unsigned int c);
unsigned int checkSide(struct SPRITE *s, unsigned int side);


#endif // TILELIB_H
