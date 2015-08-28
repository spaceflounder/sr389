
/*
 *
 *
 *  media library retrival system for sr389
 *
 *
 *
 *
 *
 *
 */


#include <stdio.h>
#include "physfs.h"

#include "allegro5/allegro.h"
#include "allegro5/allegro_image.h"
#include "allegro5/allegro_acodec.h"
#include "allegro5/allegro_audio.h"

#include "medlib.h"



struct BITMAP bmpLib[MAX_BMP];
struct SAMPLE sndLib[MAX_SND];


void initMediaLib(void)
{

    /* prepare media library for first use */
    al_init_image_addon();
    int i;
    for (i = 0; i < MAX_BMP; ++i) {
        bmpLib[i].data = NULL;
        bmpLib[i].name = "";
    }
    for (i = 0; i < MAX_SND; ++i) {
        sndLib[i].data = NULL;
        sndLib[i].name = "";
    }


}



void killMediaLib(void)
{

    /* remove media from memory */

    int i;
    for (i = 0; i < MAX_BMP; ++i) {
        al_destroy_bitmap(bmpLib[i].data);
    }
    for (i = 0; i < MAX_SND; ++i) {
        al_destroy_sample(sndLib[i].data);
    }


}


int addBmp(char *filename)
{

    int i;
    for (i = 0; i < MAX_BMP; ++i) {
        if (!bmpLib[i].data) {
            bmpLib[i].data = al_load_bitmap(filename);
            if (!bmpLib[i].data)
                return false;
            bmpLib[i].name = filename;
            return true;
        }
    }

    printf("Not enough memory to add img file.");
    return false;

}


int addSnd(char *filename)
{

    int i;
    for (i = 0; i < MAX_SND; ++i) {
        if (!sndLib[i].data) {
            sndLib[i].data = al_load_sample(filename);
            sndLib[i].name = filename;
            return true;
        }
    }

    printf("Not enough memory to add sound file.");
    return false;

}



int searchForBmp(char *filename)
{

    int i;
    for (i = 0; i < MAX_BMP; ++i)
        if (strTest(bmpLib[i].name, filename))
            return i;

    // negative on fail
    return -1;
}


int searchForSnd(char *filename)
{

    int i;
    for (i = 0; i < MAX_SND; ++i)
        if (strTest(sndLib[i].name, filename))
            return i;

    // negative on fail
    return -1;
}



