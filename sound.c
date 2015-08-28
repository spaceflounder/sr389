

/*
 *   sound.c
 *
 *   Sound subsystem for SR389 engine
 *
 */


/* standard c and allegro includes */
#include <stdio.h>
#include <string.h>
#include "allegro5/allegro.h"
#include "allegro5/allegro_audio.h"
#include "allegro5/allegro_acodec.h"

#include "medlib.h"
#include "sound.h"


/* global music container - if music is playing, it's here */
ALLEGRO_AUDIO_STREAM *music;

/* voice for music output */
ALLEGRO_VOICE *voice;

/* allegro sound mixer */
ALLEGRO_MIXER *mixer;


/* functions - used to call to this library from other parts of engine */
unsigned int setupSound(void)
{

    /* set up sound library for first use, and init allegro soundsystem */
    music = NULL;
    voice = NULL;
    mixer = NULL;
    if (!al_install_audio()) {

        /* fail if audio does not load for some reason */
        return 0;
    }
    if (!al_init_acodec_addon()) {

        /* fail if audio does not load for some reason */
        return 0;
    }
    if (!al_reserve_samples(8)) {

        /* fail if audio does not load for some reason */
        return 0;

    }
    mixer = al_create_mixer(44100, ALLEGRO_AUDIO_DEPTH_FLOAT32, ALLEGRO_CHANNEL_CONF_2);
    voice = al_create_voice(44100, ALLEGRO_AUDIO_DEPTH_INT16, ALLEGRO_CHANNEL_CONF_2);
    al_attach_mixer_to_voice(mixer, voice);
    return true;

}




void playSound(const unsigned int index)
{

    /* play sound by index number from library, standard volume */
    al_play_sample(sndLib[index].data, 1.0, 0.0, 1.0, ALLEGRO_PLAYMODE_ONCE, NULL);

}


void playSoundByName(char *filename)
{

    /* play sound by filename instead of index */
    playSound(searchForSnd(filename));

}


void playMusic(const char *filename)
{

    /* play music in background, on loop - unpause if music is already playing */
    if (isMusicPaused())
    {
        unPauseMusic();
        return;
    }

    /* music not playing, start over from beginning */
    ALLEGRO_PLAYMODE loop = ALLEGRO_PLAYMODE_LOOP;
    al_stop_samples();
    if (music != NULL)
    {
      al_drain_audio_stream(music);
      al_destroy_audio_stream(music);
    }
    music = al_load_audio_stream(filename, 4, 2048);
    al_set_audio_stream_playmode(music, loop);
    al_attach_audio_stream_to_mixer(music, mixer);

}


void playMusicOnce(const char *filename)
{

    /* play music only once in background, terminating old music */

    ALLEGRO_PLAYMODE loop = ALLEGRO_PLAYMODE_ONCE;
    al_stop_samples();
    if (music != NULL)
    {
      al_drain_audio_stream(music);
      al_destroy_audio_stream(music);
    }
    music = al_load_audio_stream(filename, 4, 2048);
    al_set_audio_stream_playmode(music, loop);
    al_attach_audio_stream_to_mixer(music, mixer);

}


void pauseMusic(void)
{

    /* pause game music */
    if (music != NULL)
    {
        al_set_audio_stream_playing(music, false);
    }

}


int isMusicPaused(void)
{

    /* return true if music is paused */
    if (music != NULL)
    {
        return !(al_get_audio_stream_playing(music));
    }
    return false;

}


void unPauseMusic(void)
{

    /* unpause game music */
    if (music != NULL)
    {
        al_set_audio_stream_playing(music, true);
    }

}


void killSound(void)
{

    /* terminate all sound and music playing in background */
    al_stop_samples();
    if (music != NULL)
    {
      al_drain_audio_stream(music);
      al_destroy_audio_stream(music);
      music = NULL;
    }

}




void shutdownSound(void)
{

    /* shutdown sound system when done */
    al_stop_samples();
    if (music != NULL)
    {
        al_destroy_audio_stream(music);
    }
    al_destroy_mixer(mixer);
    al_destroy_voice(voice);
    al_uninstall_audio();

}



