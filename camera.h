#ifndef CAMERA_H
#define CAMERA_H

#include "sprite.h"

/* external for camera def - use this for draw functions */
extern struct HITBOX camera;

extern unsigned int preventCameraUp;
extern unsigned int preventCameraDown;
extern unsigned int preventCameraLeft;
extern unsigned int preventCameraRight;

extern float horizontalSideWidth;
extern float verticalSideHeight;

void initCamera(void);
void shakeCamera(float seconds);
void handleShakeyCam(void);
void setCameraBounds(const unsigned x, const unsigned y);


#endif // CAMERA_H

