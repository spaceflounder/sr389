#ifndef STATE_H
#define STATE_H

#include "control.h"
#include "tile.h"

extern void (*collsionTable[MAX_TABLE][MAX_TABLE])(struct SPRITE *s1, struct SPRITE *s2);

/* the safe-run macro -- only does the function if it is not NULL */
#define SAFERUN(x)      if (x) x


struct STATE {

    /* state startup */
    void (*init)(void);

    /* state update and draw */
    void (*update)(void);
    void (*draw)(void);

    /* state lighting - usually for game stages */
    void (*light)(void);

    /* state user input module */
    void (*control)(struct CONTROLLER *controller);

    /* state close */
    void (*kill)(void);

    /* and the next state */
    void (*nextState)(void);

    /* state paused */
    unsigned int paused;
    void (*pause)(struct CONTROLLER *controller);

    /* is state running? */
    unsigned int active;

    /* terminate signal - ends game this instant if not false */
    unsigned int terminate;

    ALLEGRO_COLOR backColor;

};


// current running state
extern struct STATE state;

/* state sprite layers */
extern int bgIndex;
extern struct SPRITE sprites[MAX_SPRITES];


// function interface for state system
void setBackgroundImage(char *name);
void initBuffers(void);
void shutdownState(void);
void defaultStateControl(struct CONTROLLER *controller);
void updateSprites(void);
void updateFX(void);
void updateState(void);
void drawLightingMask(ALLEGRO_COLOR c);
void drawStateLighting(void);
void drawLight(void);
void drawState(void);
void drawStateFront(void);
void drawStateBack(void);
void nextState(void *(gotoFunc));
struct SPRITE *getNewSprite(void);
struct SPRITE *getNewFX(void);
void runState(ALLEGRO_TIMER *timer);
void fadeIn();
void fadeOut();
void newState(void *(startFunc), void *(controlFunc), void *(pauseFunc), void *(lightFunc),
              void *(killFunc), void *(updateFunc), void *(drawFunc));
unsigned int commonCell(struct SPRITE *s1, struct SPRITE *s2);


#endif // TILELIB_H
