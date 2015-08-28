
/*
 *
 * VIDEO.C
 *
 * Handle video subsystem for brinstar editor
 * Note - this is mostly the hardware side of things
 *
 */

#include <stdio.h>
#include <math.h>

#include <allegro5/allegro.h>
#include <allegro5/allegro_ttf.h>
#include <allegro5/allegro_font.h>

#include "font.h"
#include "state.h"
#include "video.h"


// hardware interface to display
ALLEGRO_DISPLAY *display;

// scaled buffer will function as our target to draw to
ALLEGRO_BITMAP *buffer;

// lightmap, used for stages with lighting
ALLEGRO_BITMAP *lightMap = NULL;

// screen width and height
const unsigned int screenWidth = 424;
const unsigned int screenHeight = 240;


/* the color black */
ALLEGRO_COLOR black;


/*
 * main video system struct
 */
struct VIDEODEVICE video;


/*
 * number of microseconds since last update
 */
double game_time;
double old_time;
double FPS;
int frames_done;
double elapsed(void)
{

    //return (double)frames_done;
    return (game_time - old_time);

}



/*
 * video init function - return false on fail
 */
int videoInit(void) {


    /* get max res from current video hardware and set window to that size */
    display = NULL;
    buffer = NULL;
    frames_done = 0;
    ALLEGRO_DISPLAY_MODE	disp_data;
    //al_get_display_mode(al_get_num_display_modes() - 1, &disp_data);
    al_get_display_mode(0, &disp_data);
    al_set_new_display_flags(ALLEGRO_FULLSCREEN_WINDOW + ALLEGRO_OPENGL);
    //al_set_new_display_flags(ALLEGRO_WINDOWED);
    //al_set_new_display_flags(ALLEGRO_FULLSCREEN + ALLEGRO_OPENGL_3_0);
    display = al_create_display( disp_data.width , disp_data.height );
    buffer = al_create_bitmap( screenWidth , screenHeight );
    if (!display) {
        return 0;
    }
    video.windowWidth = al_get_display_width(display);
    video.windowHeight = al_get_display_height(display);

    // calculate scaling factor for video blit operations later
    float sx = ((float)video.windowWidth / (float)screenWidth);
    float sy = ((float)video.windowHeight / (float)screenHeight);
    float scale;
    if (sx < sy)
        scale = sx;
    else
        scale = sy;

    // calculate how much video buffer should be scaled
    video.scaleW = screenWidth * scale;
    video.scaleH = screenHeight * scale;
    video.scaleX = (video.windowWidth - video.scaleW) * 0.50;
    video.scaleY = (video.windowHeight - video.scaleH) * 0.50;

    /* and create and store color black */
    black = al_map_rgb(0, 0, 0);

    /* finish success! */
    return 1;

}


void setToBackBuffer(void) {
    al_set_target_bitmap(buffer);
}


void preDrawCycle(void) {

    /* video stuff to do prior to drawing background, tiles, sprites etc... */

    al_set_target_bitmap(buffer);
    al_clear_to_color(black);

}


void postDrawCycle(void) {

    /* after drawing background, tiles, sprites, finish draw cycle */
    print(NULL, 10, 10, "%f", FPS);
    al_set_target_backbuffer(display);
    al_clear_to_color(al_map_rgb(0, 0, 0));
    al_draw_scaled_bitmap(buffer, 0, 0, screenWidth, screenHeight, video.scaleX, video.scaleY, video.scaleW, video.scaleH, 0);
    al_flip_display();

    /* update sprite movement time and fps */
    game_time = al_get_time();
    if (game_time - old_time >= 1.0) {
        FPS = frames_done / (game_time - old_time);
        frames_done = 0;
        old_time = game_time;
    }
    frames_done++;

}


void lockDisplay(void)
{

    /*
     * lockdown the video display, for special effects
     *
     */

    al_lock_bitmap(buffer, ALLEGRO_PIXEL_FORMAT_ANY, ALLEGRO_LOCK_WRITEONLY);

}


void unlockDisplay(void)
{

    /*
     * done with special effects, unlock display
     *
     */

    al_unlock_bitmap(buffer);

}


int videoKill(void) {

    /* exit video system so we dont mess up memory */
    if (display != NULL)
        al_destroy_display(display);
    return 0;

}



