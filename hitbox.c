

/*
 * HITBOX.C
 *
 * Hitbox system for collidable objects in SR389 engine
 *
 */

#include <stdio.h>

#include "hitbox.h"
#include "sprite.h"

/* collision table - what happens when two sprites collide? store answer in here */
void (*collsionTable[MAX_TABLE][MAX_TABLE])(struct SPRITE *s1, struct SPRITE *s2);


void resetCollisionTable()
{

    /* reset the collision table on engine start */
    unsigned int i = 0;
    unsigned int k = 0;
    for (i = 0; i < MAX_TABLE; ++i)
    {
        for (k = 0; k < MAX_TABLE; ++k)
        {
            collsionTable[i][k] = NULL;
        }
    }

}


int checkCollide(struct HITBOX h1, struct HITBOX h2)
{

    // check collision between two hitboxes
    return !(h1.left >= h2.right ||
                 h2.left >= h1.right ||
                 h1.top >= h2.bottom ||
                 h2.top >= h1.bottom);


}


int checkOverlap(float x1, float y1, float w1, float h1, float x2, float y2, float w2, float h2)
{

    // check overlap between two areas
    return !(x1 >= x2 + w2 ||
                 x2 >= x1 + w1 ||
                 y1 >= y2 + h2 ||
                 x2 >= y1 + h1);

}



void newHitbox(struct HITBOX *h, float x, float y, float width, float height)
{

    /* create new hitbox */
    h->x = x;
    h->y = y;
    resizeHitbox(h, width, height);

    /* check all axis by default */
    h->check[UP] = true;
    h->check[DOWN] = true;
    h->check[LEFT] = true;
    h->check[RIGHT] = true;

    // finish with update
    updateHitbox(h);

}


void resizeHitbox(struct HITBOX *h, float width, float height)
{

    /* resize width and height of hitbox */
    h->width = width;
    h->height = height;

}


void updateHitbox(struct HITBOX *h)
{

    /* update hitbox based on x and y */
    h->left = h->x;
    h->top = h->y;
    h->bottom = h->y + h->height;
    h->right = h->x + h->width;
    h->centerX = h->x + (h->width / 2);
    h->centerY = h->y + (h->height / 2);

    // default - check all axis
    h->check[UP] = true;
    h->check[DOWN] = true;
    h->check[LEFT] = true;
    h->check[RIGHT] = true;


}

