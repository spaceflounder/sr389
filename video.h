
/*
 *
 * video subsytem header file
 *
 */


#ifndef VIDEO_H
#define VIDEO_H

#include "allegro5/allegro.h"

#define TARGET_FPS      60

// screen widht and height
extern const unsigned int screenWidth;
extern const unsigned int screenHeight;


/* video system defin */
struct VIDEODEVICE {
    int windowWidth;
    int windowHeight;
    int scaleW;
    int scaleH;
    int scaleX;
    int scaleY;
};


/* fps tracker values/ */
extern double FPS;
extern int frames_done;
double elapsed(void);


/* and functions */
int videoInit(void);
int videoKill(void);

void setToBackBuffer(void);
void preDrawCycle(void);
void postDrawCycle(void);

void lockDisplay(void);
void unlockDisplay(void);


#endif // VIDEO_H

