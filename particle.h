#ifndef PARTICLE_H
#define PARTICLE_H

/* header for particle engine - for SR389 */

#include "allegro5/allegro.h"

#define MAX_EMITTERS                128

struct PARTICLE {

    // particle datacore
    float size;
    float rate;
    float colorTrans;
    float angle;
    float scaleFactor;
    unsigned int stage;
    ALLEGRO_COLOR c[4];

};



struct EMITTER
{

    void (*executeEmitterFunction)(float x, float y);
    float x;
    float y;
    int number;

    int __internal__duration;
    int __internal__duration_ticks;
    int __internal__frequency;
    int __internal__frequency_timer;

};


extern struct EMITTER emitter[MAX_EMITTERS];


void updateParticle(struct SPRITE *s);
void updateEmitters(void);
void updateEmitter(struct EMITTER *e);
void resetEmitters(void);
struct SPRITE *getNewParticle(float x, float y, float vx, float vy, float rate, float rotateSpeed, float scaleFactor, char *name,
                              ALLEGRO_COLOR c1, ALLEGRO_COLOR c2, ALLEGRO_COLOR c3);
struct EMITTER *getNewEmitter(float x, float y, float rate, float frequency, int number, void (*executeEmitterFunction)(float x, float y));
void createEmitter(struct EMITTER *e);
#endif // PARTICLE_H

