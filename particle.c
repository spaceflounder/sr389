
/*
 *
 *
 *
 *
 *
 *      PARTICLE.C
 *
 *
 *      Automated particle creation system for SR389
 *      These aren't anything special - they're just basic particles
 *
 *
 *
 */

#include <stdio.h>

#include "allegro5/allegro.h"
#include "sprite.h"
#include "state.h"

#include "particle.h"


struct EMITTER emitter[MAX_EMITTERS];



void createEmitter(struct EMITTER *e)
{

    // create new emitter
    e->executeEmitterFunction = NULL;
    e->number = 0;
    e->__internal__duration = 0;
    e->__internal__duration_ticks = 0;
    e->__internal__frequency = 0;
    e->__internal__frequency_timer = 0;
    e->x = 0;
    e->y = 0;

}


void resetEmitters(void)
{

    // called on engine startup, and between states. preps emitters for first use
    int i;
    for (i = 0; i < MAX_EMITTERS; ++i) {
        createEmitter(&emitter[i]);
    }

}


void updateEmitter(struct EMITTER *e)
{

    // update individual emitter
    int count;
    if (e->executeEmitterFunction) {
        if (++e->__internal__frequency_timer > e->__internal__frequency) {
            e->__internal__frequency_timer = 0;
            for (count = 0; count < e->number; ++count) {
                e->executeEmitterFunction(e->x, e->y);
            }
        }
        if (++e->__internal__duration_ticks > e->__internal__duration) {
            e->executeEmitterFunction = NULL;
        }
    }

}


void updateEmitters(void)
{

    // update emitters each state
    int i;
    for (i = 0; i < MAX_EMITTERS; ++i) {
        updateEmitter(&emitter[i]);
    }

}


struct EMITTER *getNewEmitter(float x, float y, float duration, float frequency, int number, void (*executeEmitterFunction)(float x, float y))
{

    /* make new particle emitter - null if we can't get one */
    struct EMITTER *e;
    int i;
    for (i = 0; i < MAX_EMITTERS; ++i) {
        if (!emitter[i].executeEmitterFunction) {
            e = &emitter[i];
            createEmitter(e);
            e->x = x;
            e->y = y;
            e->__internal__duration = (duration * 60);
            e->__internal__frequency = (frequency * 60);
            e->number = number;
            e->executeEmitterFunction = executeEmitterFunction;
            return e;
        }
    }
    return NULL;

}


static ALLEGRO_COLOR blendColor(ALLEGRO_COLOR c2, ALLEGRO_COLOR c1, float trans)
{

    // blend two colors on a particle
    ALLEGRO_COLOR result;
    float r;
    float g;
    float b;
    float a;
    float r2;
    float g2;
    float b2;
    float a2;
    al_unmap_rgba_f(c1, &r, &g, &b, &a);
    al_unmap_rgba_f(c2, &r2, &g2, &b2, &a2);
    result = al_map_rgba_f(
             (r * trans) + (r2 * (1 - trans)),
             (g * trans) + (g2 * (1 - trans)),
             (b * trans) + (b2 * (1 - trans)),
             (a * trans) + (a2 * (1 - trans))
    );
    return result;

}



void updateParticle(struct SPRITE *s)
{

    /* update particles, regardless of whether onscreen or not */
    struct PARTICLE *data = (struct PARTICLE *)s->data;
    data->colorTrans = data->colorTrans + data->rate;
    if (data->colorTrans > 1) {
        data->colorTrans = 0;
        ++data->stage;
    }
    if (data->stage == 3) {
        s->__internal__alive = false;
        return;
    }
    data->size = data->size + data->scaleFactor;
    s->SetScaleX(s, data->size);
    s->SetScaleY(s, data->size);
    s->SetAngle(s, s->GetAngle(s) + data->angle);
    s->__internal_tint = blendColor(data->c[data->stage], data->c[data->stage + 1], data->colorTrans);
    updateSprite(s);

}


struct SPRITE *getNewParticle(float x, float y, float vx, float vy, float rate, float rotateSpeed, float scaleFactor, char *name,
                              ALLEGRO_COLOR c1, ALLEGRO_COLOR c2, ALLEGRO_COLOR c3)
{

    /* create new particle from fx layer */
    struct SPRITE *s = getNewFX();
    if (s != NULL) {
        struct PARTICLE *data = (struct PARTICLE *)s->data;
        data = s->data = (struct PARTICLE *)malloc(sizeof(struct PARTICLE));
        s->__internal__anim.graphicIndex = searchForBmp(name);
        newHitbox(&s->box, x, y, 5, 5);
        s->SetVX(s, vx);
        s->SetVY(s, vy);
        s->update = updateParticle;
        data->rate = rate;
        data->size = 1;
        data->scaleFactor = scaleFactor;
        data->angle = rotateSpeed;
        data->stage = 0;
        data->colorTrans = 0;
        s->__internal_tint = c1;
        data->c[0] = c1;
        data->c[1] = c2;
        data->c[2] = c3;
        data->c[3] = al_map_rgba_f(0, 0, 0, 0);
        return s;
    } else {
        exit(1);
        return NULL;
    }


}

