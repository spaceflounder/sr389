#ifndef DRAW_H
#define DRAW_H

/* header for primary draw system */
#include "sprite.h"

void addSpriteToLayer(const unsigned int layer, struct SPRITE *s);
void resetAllDrawLayers(void);
void resetDrawLayer(const unsigned int layer);
void finalizeDrawLayer(const unsigned int layer);


#endif // DRAW_H

