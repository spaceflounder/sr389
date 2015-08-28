
/*
 *
 *
 *      MAIN.C
 *      Start execution module for SR389 engine
 *
 *
 *
 *
 */


#include <stdio.h>
#include "allegro5/allegro.h"
#include "allegro5/allegro_primitives.h"
#include "allegro5/allegro_physfs.h"
#include <physfs.h>

#include "hitbox.h"

#include "video.h"
#include "sound.h"
#include "state.h"
#include "font.h"
#include "medlib.h"
#include "sound.h"

#include "camera.h"

#include "game/game.h"


/* name of datapack file */
#define DATAPACKNAME        "data.zip"

#define STARTUP(x) if (!x) { videoKill(); PHYSFS_deinit(); fprintf(stderr, "\n   Engine startup fail\n"); return EXIT_FAILURE; }


static unsigned int init_datafile(char *argv[])
{

    /* load main game datafile (usually a zip) into memory */
    if (!PHYSFS_init(argv[0])) {
        fprintf(stderr, "Could not init PhysFS\n");
        return false;
    }
    PHYSFS_addToSearchPath(DATAPACKNAME, 1);
    al_set_standard_file_interface();
    al_set_physfs_file_interface();
    return true;

}




int main(int argc __attribute__((unused)), char *argv[])
{

    /* init allegro library */
    ALLEGRO_TIMER *timer = NULL;
    al_init();

    /* prepare random number generator */
    srand(time(NULL));

    /* activate all engine subsystems using the startup macro */
    resetCollisionTable();
    STARTUP(videoInit())
    STARTUP(init_datafile(argv))
    STARTUP(al_install_keyboard())
    STARTUP(fontInit())
    STARTUP(setupSound())
    timer = al_create_timer(1.0 / 60);
    al_start_timer(timer);
    initMediaLib();
    initBuffers();

    /* prepare game */
    startGame();

    /* begin game loop */
    while(!state.terminate) {
        runState(timer);
    }

    /* finish, return control to os */
    al_destroy_timer(timer);
    shutdownState();
    shutdownGame();
    videoKill();
    shutdownSound();
    al_uninstall_system();
    PHYSFS_deinit();

    /* no problems, exit false */
    return EXIT_SUCCESS;

}

