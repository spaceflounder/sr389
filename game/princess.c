/*
 *
 *
 *      PRINCESS.C
 *
 *
 *      Princess Toadstool, for cutscenes
 *
 *
 *
 *
 *
 *
 */

#include "allegro5/allegro.h"

#include "sprite.h"
#include "state.h"

/* princess and luigi share a sheet */
#include "game.h"
#include "princessLuigi.h"


static void update(struct SPRITE *s)
{

    /* princess update */
    if (s->direction == RIGHT) {
        s->flipped = ALLEGRO_FLIP_HORIZONTAL;
    } else {
        s->flipped = false;
    }
    updateSprite(s);

}


struct SPRITE *makePrincess(float x, float y)
{

    struct SPRITE *s = getNewSprite();
    attachAnim_PrincessLuigi(s);

    s->solid = true;
    newHitbox(&s->box, x, y, 14, 20);
    s->SetMaxSpeedX(s, 2);
    s->SetMaxSpeedY(s, 2);
    s->SetDragY(s, 0.5);
    s->SetDragX(s, 0.1);
    s->collidable = true;
    s->direction = LEFT;
    s->id = ID_GENERIC;
    s->SetAnim(s, princessStand, true);
    s->update = update;

    return s;

}

