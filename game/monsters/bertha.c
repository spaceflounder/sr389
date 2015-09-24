/*
 *
 *          BERTHA.C
 *
 *
 *          Big Bertha, boss attack
 *
 *
 */

#include <stdio.h>
#include <math.h>
#include "allegro5/allegro.h"

#include "medlib.h"
#include "state.h"
#include "sprite.h"


#include "../game.h"
#include "bertha.h"


static const float gravity = 0.3;
static const float speed = 3;
static const float timeToAttack = 1;

struct BERTHA {
    float activationPointX;
    float height;
};



static void ceaseAttack(struct SPRITE *s)
{

    // bertha flies into air with y velocity
    s->direction = DOWN;
    s->SetAnim(s, berthaSwim, true);

}


static void attack(struct SPRITE *s)
{

    // bertha flies into air with y velocity
    s->SetVY(s, -(speed * 5));
    s->direction = UP;
    s->SetTimer(s, timeToAttack, ceaseAttack);

}


static void update(struct SPRITE *s)
{

    // bertha update, rise when player is near
    GET_EXTEND(BERTHA);
    if (player->box.centerX > data->activationPointX) {
        if (s->direction == FORWARD) {
            attack(s);
        }
    }
    if (s->direction == UP) {
        s->SetVY(s, -(speed));
    } else if (s->direction == DOWN) {
        if (!checkCollide(camera, s->box)) {
            s->direction = FORWARD;
        }
    }
    if (s->box.y > camera.bottom + 16)
        s->box.y = camera.bottom + 16;
    updateSprite(s);
    if (s->box.top < data->height) {
        s->box.y = data->height;
    }

    if (s->box.left < (camera.left - 10))
        s->__internal__alive = false;

}



struct SPRITE *makeBertha(float x, float activationPointX, float height)
{

    /* bertha, boss world 2 */
    struct SPRITE *s = getNewSprite();
    SPRITE_EXTEND(BERTHA);
    attachAnim_Bertha(s);
    newHitbox(&s->box, x, stageHeightInTiles * 16, 96, 96);
    s->__internal__z = 2;
    s->update = update;
    s->collidable = true;
    s->solid = false;
    s->id = ID_MONSTER;
    s->SetAY(s, gravity);
    s->direction = FORWARD;
    data->activationPointX = activationPointX;
    data->height = height;
    s->SetAnim(s, berthaJump, true);

    return s;

}

