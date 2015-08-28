#ifndef SOUND_H
#define SOUND_H

/* sound system interface header for sr389 */



/*
 *   sound.c
 *
 *   Sound subsystem for SR389 engine
 *
 */

// global boolean int - when on, play sounds from animation frames
unsigned int playFrameSounds;


unsigned int setupSound(void);
void playSound(const unsigned int index);
void playSoundByName(char *filename);
void playMusic(const char *filename);
void playMusicOnce(const char *filename);
void pauseMusic(void);
int isMusicPaused(void);
void unPauseMusic(void);
void killSound(void);
void shutdownSound(void);



#endif // SOUND_H

