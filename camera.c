
/*
 *
 *
 *      Central camera source for sr389
 *
 *
 *
 *
 *
 *
 */

#include <stdio.h>
#include <math.h>
#include "allegro5/allegro.h"

#include "video.h"

#include "camera.h"




/* common camara */
struct HITBOX camera;
static struct HITBOX lower;
static struct HITBOX left;
static struct HITBOX right;
static struct HITBOX upper;

/* stage and camera hitboxes bounds */
static float boundx;
static float boundy;
float horizontalSideWidth;
float verticalSideHeight;


/* do we prevent movement in any given direction? turn these
 * on or off
 */
unsigned int preventCameraUp;
unsigned int preventCameraDown;
unsigned int preventCameraLeft;
unsigned int preventCameraRight;


/* shake camera timer and location */
static unsigned int shakeyCamTimer = 0;
static float orgShakeCamX;
static float orgShakeCamY;


void initCamera(void)
{

    /* create new camera for BRINSTAR stage use */
    camera.x = 0;
    camera.y = 0;
    camera.width = screenWidth + 1;
    camera.height = screenHeight + 1;
    horizontalSideWidth = (camera.width / 2.6);
    verticalSideHeight = (camera.height / 2.6);
    preventCameraDown = false;
    preventCameraUp = false;
    preventCameraLeft = false;
    preventCameraRight = false;
    updateHitbox(&camera);
    shakeyCamTimer = 0;

}


void handleShakeyCam(void)
{

    /* if camera is shaking, move it all over place randomly */
    if (shakeyCamTimer) {
        --shakeyCamTimer;
        float moveCameraX = ((float)rand()/(float)(RAND_MAX)) * 16;
        float moveCameraY = ((float)rand()/(float)(RAND_MAX)) * 16;
        moveCameraX = moveCameraX - 8;
        moveCameraY = moveCameraY - 8;
        camera.x = camera.x + moveCameraX;
        camera.y = camera.y + moveCameraY;
        if (shakeyCamTimer == 0) {
            camera.x = orgShakeCamX;
            camera.y = orgShakeCamY;
        }
    }

}


void shakeCamera(float seconds)
{

    /* shake camera for n number of seconds */
    orgShakeCamX = camera.x;
    orgShakeCamY = camera.y;
    shakeyCamTimer = floorf(seconds * 60);

}



void setCameraBounds(const unsigned x, const unsigned  y)
{

    /* lock camera so that it stays within x and y */
    boundx = (float)x - 16;
    boundy = (float)y - 16;

}


void focusCamaraOn(struct SPRITE *s)
{


    /* if sprite is not in frame, refocuse immeadiatly */
    if (!checkCollide(camera, s->box)) {
        camera.x = (s->box.centerX) - horizontalSideWidth;
        camera.y = (s->box.centerY - (verticalSideHeight));
        updateHitbox(&camera);
        newHitbox(&upper, camera.left, camera.y, camera.width, verticalSideHeight);
        newHitbox(&lower, camera.left, camera.y + camera.height - verticalSideHeight, camera.width, verticalSideHeight);
        newHitbox(&left, camera.left, camera.y - camera.height, horizontalSideWidth, camera.height * 3);
        newHitbox(&right, camera.right - horizontalSideWidth, camera.y - camera.height, horizontalSideWidth, camera.height * 3);

    }


}


/* camera update - follow sprite passed below */
void followSprite(struct SPRITE *s)
{

    /* calculate deadzone */
    updateHitbox(&camera);
    newHitbox(&upper, camera.left, camera.y, camera.width, verticalSideHeight);
    newHitbox(&lower, camera.left, camera.y + camera.height - verticalSideHeight, camera.width, verticalSideHeight);
    newHitbox(&left, camera.left, camera.y - camera.height, horizontalSideWidth, camera.height * 3);
    newHitbox(&right, camera.right - horizontalSideWidth, camera.y - camera.height, horizontalSideWidth, camera.height * 3);

    /* fix camera in case sprite goes outside of dead zone */
    if (!checkCollide(s->box, upper) && !preventCameraDown) {
        camera.y = camera.y + fabsf(s->GetVY(s));
        if (fabsf(s->GetVY(s)) < 0.1)
            camera.y = camera.y + s->GetMaxSpeedY(s);
    }
    if (!checkCollide(s->box, lower) && !preventCameraUp) {
        camera.y = camera.y - fabsf(s->GetVY(s));
        if (fabsf(s->GetVY(s)) < 0.1)
            camera.y = camera.y - s->GetMaxSpeedY(s);
    }
    if (!checkCollide(s->box, left) && !preventCameraRight) {
        camera.x = camera.x + fabsf(s->GetVX(s));
        if (!s->GetVX(s))
            camera.x = camera.x + s->GetMaxSpeedX(s);
    }
    if (!checkCollide(s->box, right) && !preventCameraLeft) {
        camera.x = camera.x - fabsf(s->GetVX(s));
        if (!s->GetVX(s))
            camera.x = camera.x - s->GetMaxSpeedX(s);
    }
    updateHitbox(&camera);

    /* clip camera to level bounds */
    if (camera.x < 0) {
        camera.x = 0;
    }
    if (camera.y < 0) {
        camera.y = 0;
    }
    if (camera.x + camera.width > boundx) {
        camera.x = boundx - camera.width;
    }
    if (camera.y + camera.height > boundy) {
        camera.y = boundy - camera.height;
    }
    updateHitbox(&camera);

}



