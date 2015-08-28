#ifndef MEDLIB_H
#define MEDLIB_H

#include <string.h>

#include "allegro5/allegro.h"
#include "allegro5/allegro_audio.h"


#define MAX_BMP     1024
#define MAX_SND     512

/* useful for string search algr */
#define strTest(str1, str2)          (strcmp(str1, str2) == 0)


struct BITMAP {
    ALLEGRO_BITMAP *data;
    char *name;
};
struct SAMPLE {
    ALLEGRO_SAMPLE *data;
    char *name;
};

extern struct BITMAP bmpLib[MAX_BMP];
extern struct SAMPLE sndLib[MAX_SND];


void initMediaLib(void);
void killMediaLib(void);
int addBmp(char *filename);
int searchForBmp(char *filename);
int addSnd(char *filename);
int searchForSnd(char *filename);


#endif // MEDLIB_H

