/*
 *
 *      CHEEPCHEEP.C
 *
 *      Cheep cheep monster -- kind of the worst monster in mario, ever
 *
 *
 */

#include <stdio.h>
#include "allegro5/allegro.h"

#include "sprite.h"
#include "state.h"

#include "../game.h"
#include "cheepCheep.h"


static const float cheepCheepSpawnTime = 1;

static const float cheepCheepFallSpeed = 0.1099;
static const float cheepCheepMoveSpeed = 0.1099;


struct FISHSPAWNPOINT {

    float activationPoint;
    float spawnTime;
    int numberToSpawn;
    float speed;

};


static void updateFish(struct SPRITE *s)
{

    /* fish terminates when offscreen */
    if (s->box.y > camera.bottom) {
        s->__internal__alive = false;
    }
    if (s->GetVX(s) > 0) {
        s->SetAnim(s, 1, true);
    } else {
        s->SetAnim(s, 0, true);
    }
    if (s->GetScaleX(s) < 1) {
        s->SetScaleX(s, s->GetScaleX(s) + 0.05);
    }
    if (s->GetScaleY(s) < 1) {
        s->SetScaleY(s, s->GetScaleY(s) + 0.05);
    }
    updateSprite(s);

}


struct SPRITE *makeCheepCheep(float x, float y)
{

    /* create fish, usually from spawnpoint */
    struct SPRITE *s = getNewSprite();
    attachAnim_CheepCheep(s);
    s->SetAnim(s, 0, true);
    s->solid = false;
    s->SetVisible(s, true);
    newHitbox(&s->box, x + 2, y + 8, 20, 16);
    s->collidable = true;
    s->SetAY(s, cheepCheepFallSpeed);
    s->SetMaxSpeedY(s, 3);
    s->SetScaleY(s, 0.3);
    s->SetScaleX(s, 0.3);
    s->id = ID_STOMPABLE;
    s->update = updateFish;
    s->__internal__z = 4;
    return s;
}


void spawnFish(struct SPRITE *s)
{

    /* spawn fish when time is up */
    GET_EXTEND(FISHSPAWNPOINT);
    struct SPRITE *c = makeCheepCheep(s->box.x, s->box.y);
    c->SetVX(c, data->speed);

}


void updateFishSpawn(struct SPRITE *s)
{

    /* update cheep cheep spawn
     * wait till player hits activation point, then use a timer to throw fish until we're out of
     * fish to throw
     */

    GET_EXTEND(FISHSPAWNPOINT);

    if (player->box.x > data->activationPoint && s->box.right > camera.x) {

        /* we're activated, begin spawning fish */
        if (data->numberToSpawn) {
            if (s->GetTimeRemaining(s) == -1) {
                s->SetTimer(s, data->spawnTime, spawnFish);
                if (data->numberToSpawn > 0)
                    --data->numberToSpawn;
            }
        }

        updateSprite(s);
    }


}


void makeCheepCheepSpawn(float x, float y, float activationPoint, float speed, float spawnTime, int numberToSpawn)
{

    /* create spawnpoint for fish
     * this is an invisible object, so
     * no draw function!
     * note that if number to spawn is less than zero, it spawns forever
     */

    struct SPRITE *s = getNewFX();
    SPRITE_EXTEND(FISHSPAWNPOINT);
    data->activationPoint = activationPoint;
    data->spawnTime = spawnTime;
    data->numberToSpawn = numberToSpawn;
    data->speed = speed;
    s->solid = 0;
    s->id = ID_GENERIC;
    newHitbox(&s->box, x, y, 20, 16);
    s->collidable = false;
    s->update = updateFishSpawn;
    s->draw = NULL;
    s->SetVisible(s, false);

}


