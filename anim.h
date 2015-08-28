#ifndef ANIM_H
#define ANIM_H


/* max number of anims in whole library, and max number of frames per anim */
#define MAX_ANIM            1024
#define MAX_FRAME           32
#define MAX_STRIP           64

struct FRAME {

    /* a frame of animation is really just a rectangle that punches out a png bitmap for display
       might also contain sound and delay info */

    /* location and size of frame */
    float x;
    float y;
    float x2;
    float y2;
    float w;
    float h;

    /* delay, how many cycles to show this frame? */
    unsigned int delay;

    /* and any sound effects? -1 by default */
    int sound;

};


/* now, the anim library - access to graphics from here */
struct ANIM {

    /* index of frame in filmstrip */
    int index;

    /* name of animation */
    char *name;

    /* index of graphic in library */
    int graphicIndex;

    /* frame list, first the "filmstrip," and the individual rects this strip */
    struct FRAME frame[MAX_STRIP][MAX_FRAME];

};



#endif // ANIM_H

