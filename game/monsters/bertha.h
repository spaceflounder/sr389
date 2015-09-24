/* AUTOMATICALLY GENERATED HEADER FOR bertha -- 9/14/2015 7:51:12 AM */

#include "sprite.h"

static const unsigned int berthaSwim=0;
static const unsigned int berthaJump=1;

static void attachAnim_Bertha(struct SPRITE *s)
{

    s->__internal__anim.graphicIndex = -1;
    s->__internal__anim.name = "bertha.png";
s->__internal__anim.index = 0;
    s->__internal__anim.frame[berthaSwim][0].x = 0; // animation:  swim
    s->__internal__anim.frame[berthaSwim][0].y = 0;
    s->__internal__anim.frame[berthaSwim][0].w = 123;
    s->__internal__anim.frame[berthaSwim][0].h = 120;
    s->__internal__anim.frame[berthaSwim][0].sound = -1;
    s->__internal__anim.frame[berthaSwim][0].delay = 1;
    s->__internal__anim.frame[berthaSwim][1].x = 0; // animation:  swim
    s->__internal__anim.frame[berthaSwim][1].y = 122;
    s->__internal__anim.frame[berthaSwim][1].w = 126;
    s->__internal__anim.frame[berthaSwim][1].h = 122;
    s->__internal__anim.frame[berthaSwim][1].sound = -1;
    s->__internal__anim.frame[berthaSwim][1].delay = 1;
    s->__internal__anim.frame[berthaSwim][2].x = 127; // animation:  swim
    s->__internal__anim.frame[berthaSwim][2].y = 128;
    s->__internal__anim.frame[berthaSwim][2].w = 125;
    s->__internal__anim.frame[berthaSwim][2].h = 121;
    s->__internal__anim.frame[berthaSwim][2].sound = -1;
    s->__internal__anim.frame[berthaSwim][2].delay = 1;
    s->__internal__anim.frame[berthaSwim][3].x = 129; // animation:  swim
    s->__internal__anim.frame[berthaSwim][3].y = 0;
    s->__internal__anim.frame[berthaSwim][3].w = 125;
    s->__internal__anim.frame[berthaSwim][3].h = 127;
    s->__internal__anim.frame[berthaSwim][3].sound = -1;
    s->__internal__anim.frame[berthaSwim][3].delay = 1;
    s->__internal__anim.frame[berthaSwim][4].x = 384; // animation:  swim
    s->__internal__anim.frame[berthaSwim][4].y = 0;
    s->__internal__anim.frame[berthaSwim][4].w = 128;
    s->__internal__anim.frame[berthaSwim][4].h = 122;
    s->__internal__anim.frame[berthaSwim][4].sound = -1;
    s->__internal__anim.frame[berthaSwim][4].delay = 1;
    s->__internal__anim.frame[berthaSwim][5].x = 255; // animation:  swim
    s->__internal__anim.frame[berthaSwim][5].y = 123;
    s->__internal__anim.frame[berthaSwim][5].w = 127;
    s->__internal__anim.frame[berthaSwim][5].h = 121;
    s->__internal__anim.frame[berthaSwim][5].sound = -1;
    s->__internal__anim.frame[berthaSwim][5].delay = 1;

    s->__internal__anim.frame[berthaSwim][6].sound = -255;

    s->__internal__anim.frame[berthaJump][0].x = 0; // animation:  jump
    s->__internal__anim.frame[berthaJump][0].y = 245;
    s->__internal__anim.frame[berthaJump][0].w = 125;
    s->__internal__anim.frame[berthaJump][0].h = 120;
    s->__internal__anim.frame[berthaJump][0].sound = -1;
    s->__internal__anim.frame[berthaJump][0].delay = 1;
    s->__internal__anim.frame[berthaJump][1].x = 255; // animation:  jump
    s->__internal__anim.frame[berthaJump][1].y = 0;
    s->__internal__anim.frame[berthaJump][1].w = 128;
    s->__internal__anim.frame[berthaJump][1].h = 122;
    s->__internal__anim.frame[berthaJump][1].sound = -1;
    s->__internal__anim.frame[berthaJump][1].delay = 1;
    s->__internal__anim.frame[berthaJump][2].x = 383; // animation:  jump
    s->__internal__anim.frame[berthaJump][2].y = 123;
    s->__internal__anim.frame[berthaJump][2].w = 127;
    s->__internal__anim.frame[berthaJump][2].h = 121;
    s->__internal__anim.frame[berthaJump][2].sound = -1;
    s->__internal__anim.frame[berthaJump][2].delay = 1;

    s->__internal__anim.frame[berthaJump][3].sound = -255;

}
