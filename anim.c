/*
 *
 *
 *
 *      Animation library for SR389
 *
 *
 *
 *
 *
 *
 */

#include <stdio.h>
#include <string.h>

#include "allegro5/allegro.h"
#include "anim.h"


/* total number of animations in our whole game -- all the sprites share this one resource */
struct ANIM anim[MAX_ANIM];


int searchAnims(char *name)
{

    /* return index of NAME in animation array - negative on fail */
    int i;
    for (i = 0; i < MAX_ANIM; ++i)
        if (strTest(anim[i].name, ==, name))
            return i;
    return -1;

}


