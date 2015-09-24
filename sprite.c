
/*
 *
 *
 *
 *
 *
 *      SPRITE.C
 *
 *
 *      Handle sprites for SR389
 *
 *
 *
 */


#include <stdio.h>
#include <math.h>

#include "allegro5/allegro.h"
#include "allegro5/allegro_primitives.h"

#include "draw.h"
#include "hitbox.h"
#include "medlib.h"
#include "video.h"
#include "camera.h"
#include "sprite.h"
#include "sound.h"


/* sprite movement calculator */
float calculateVelocity(float Velocity, float Acceleration, float Drag, float Max)
{
    if (Acceleration != 0)
        Velocity = Velocity + (Acceleration * 0.6);
    else if (Drag != 0)
    {
        float drag = Drag * 0.6;
        if (Velocity - drag > 0)
            Velocity = Velocity - drag;
        else if (Velocity + drag < 0)
            Velocity += drag;
        else
            Velocity = 0;
    }
    if ((Velocity != 0) && (Max != 10000))
    {
        if (Velocity > Max)
            Velocity = Max;
        else if (Velocity < -Max)
            Velocity = -Max;
    }
    return Velocity;
}


/* sprite interface defaults */
static float GetX(struct SPRITE *s)
{
    return s->box.x;
}
static float GetY(struct SPRITE *s)
{
    return s->box.y;
}
static float GetAX(struct SPRITE *s)
{
    return s->__internal__ax;
}
static float GetAY(struct SPRITE *s)
{
    return s->__internal__ay;
}
static float GetVX(struct SPRITE *s)
{
    return s->__internal__vx;
}
static float GetVY(struct SPRITE *s)
{
    return s->__internal__vy;
}
static void SetX(struct SPRITE *s, float val)
{
    s->box.x = val;
    updateHitbox(&s->box);
}
static void SetY(struct SPRITE *s, float val)
{
    s->box.y = val;
    updateHitbox(&s->box);
}
static void SetVX(struct SPRITE *s, float val)
{
    s->__internal__vx = val;
}
static void SetVY(struct SPRITE *s, float val)
{
    s->__internal__vy = val;
}
static void SetAX(struct SPRITE *s, float val)
{
    s->__internal__ax = val;
}
static void SetAY(struct SPRITE *s, float val)
{
    s->__internal__ay = val;
}
static float GetMaxSpeedX(struct SPRITE *s)
{
    return s->__internal__maxspeedx;
}
static void SetMaxSpeedX(struct SPRITE *s, float val)
{
    s->__internal__maxspeedx = val;
}
static float GetDragX(struct SPRITE *s)
{
    return s->__internal__drag;
}
static void SetDragX(struct SPRITE *s, float val)
{
    s->__internal__drag = val;
}
static float GetMaxSpeedY(struct SPRITE *s)
{
    return s->__internal__maxspeedy;
}
static void SetMaxSpeedY(struct SPRITE *s, float val)
{
    s->__internal__maxspeedy = val;
}
static float GetDragY(struct SPRITE *s)
{
    return s->__internal__drag;
}
static void SetDragY(struct SPRITE *s, float val)
{
    s->__internal__drag = val;
}
static int GetAnim(struct SPRITE *s) {

    /* return playing animation, if any
     * -1 on non-playing sprite
     */
    return s->__internal__strip;

}
static void SetAnim(struct SPRITE *s, int index, int looping)
{

    /* play animation in library, resetting current sprite animation data */

    if (GetAnim(s) != index) {

        /* good, animation is not already playing, we can change it */
        s->__internal__anim.index = 0;
        s->__internal__strip = index;
        s->__internal__frame = 0;
        s->__internal__frameDelay = 0;
        s->__internal__looping = looping;

    }

}
static float GetScaleX(struct SPRITE *s)
{
    return s->__internal__scaleX;
}
static float GetScaleY(struct SPRITE *s)
{
    return s->__internal__scaleY;
}
static void SetScaleX(struct SPRITE *s, float val)
{
    s->__internal__scaleX = val;
}
static void SetScaleY(struct SPRITE *s, float val)
{
    s->__internal__scaleY = val;
}
unsigned int GetAlive(struct SPRITE *s)
{
    return s->__internal__alive;
}
static void SetAlive(struct SPRITE *s, unsigned int val)
{
    s->__internal__alive = val;
}
static float GetAngle(struct SPRITE *s)
{
    return s->__internal__angle;
}
static void SetAngle(struct SPRITE *s, float val)
{
    s->__internal__angle = val;
}
int GetHealth(struct SPRITE *s)
{
    return s->__internal__health;
}
static void SetHealth(struct SPRITE *s, int val)
{
    s->__internal__health = val;
}
int GetVisible(struct SPRITE *s)
{
    return s->__internal__visible;
}
static void SetVisible(struct SPRITE *s, unsigned int val)
{
    s->__internal__visible = val;
}
int GetDamage(struct SPRITE *s)
{
    return s->__internal__damage;
}
static void SetDamage(struct SPRITE *s, int val)
{
    s->__internal__damage = val;
}
static void SetTint(struct SPRITE *s, float r, float g, float b, float a)
{
    s->__internal_tint = al_map_rgba_f(r, g, b, a);
}
static int GetTimeRemaining(struct SPRITE *s)
{
    return s->timeLeft;
}
static void SetSpriteTimer(struct SPRITE *s, float secs, void (*f)(struct SPRITE *))
{
    /* set timer for this sprite */
    s->timeLeft = floorf(secs * 60);
    s->timerFunc = f;
}
static int Collides(struct SPRITE *s, struct SPRITE *other)
{

    /* basic collision detect, return TRUE if collides with other sprite */
    return checkCollide(s->box, other->box);

}
static void Draw(struct SPRITE *s)
{

    // pipe into standard draw routine, compensating for camera use
    drawSprite(s, s->box.centerX, s->box.bottom);

}

void updateSprite(struct SPRITE *s)
{

    /* do sprite update, default implementation */
    /* keep sprite from moving when touching walls */
    if (s->solid) {
        if (s->isTouching[LEFT]) {
            --s->isTouching[LEFT];
        }
        if (s->isTouching[RIGHT]) {
            --s->isTouching[RIGHT];
        }
        if (s->isTouching[UP]) {
            --s->isTouching[UP];
        }
        if (s->isTouching[DOWN]) {
            --s->isTouching[DOWN];
        }
    }

    /* move sprite, standard physics */
    s->SetVX(s, calculateVelocity(s->GetVX(s), s->GetAX(s), s->GetDragX(s), s->GetMaxSpeedX(s)));
    s->SetVY(s, calculateVelocity(s->GetVY(s), s->GetAY(s), s->GetDragY(s), s->GetMaxSpeedY(s)));
    s->SetX(s, s->GetX(s) + s->GetVX(s));
    s->SetY(s, s->GetY(s) + s->GetVY(s));
    updateHitbox(&s->box);

    /* sprite timer execution */
    if (s) {
        if (s->timeLeft > 0) {
            --s->timeLeft;
        } else if (s->timeLeft == 0) {
            s->timeLeft = -1;
            if (s->timerFunc)
                s->timerFunc(s);
        }
    }

}
void killSprite(struct SPRITE *s)
{

    /* kill sprite - just turns off alive flag by default */
    if (s->GetAlive(s)) {
        s->SetAlive(s, false);
    }

}

void drawSprite(struct SPRITE *s, float x, float y)
{

    /* draw sprite, animate if it's got more than one frame */
    if (!s)
        return;

    // don't bother if we're not even visible
    if (!s->__internal__visible)
        return;

    // figure out if we know our graphic index
    if (s->__internal__anim.graphicIndex == -1)
        s->__internal__anim.graphicIndex = searchForBmp(s->__internal__anim.name);

    // check for basic sprite, non-animated
    if (s->__internal__anim.index == -1) {

        /* this is a basic sprite with no animation, so just display it */
        float w = al_get_bitmap_width(bmpLib[s->__internal__anim.graphicIndex].data) * s->GetScaleX(s);
        float h = al_get_bitmap_height(bmpLib[s->__internal__anim.graphicIndex].data) * s->GetScaleY(s);
        al_draw_tinted_scaled_rotated_bitmap(bmpLib[s->__internal__anim.graphicIndex].data,
           s->__internal_tint, 0, 0, x - (w / 2) - floorf(camera.x), y - h - floorf(camera.y),
                s->GetScaleX(s), s->GetScaleY(s), s->GetAngle(s), s->flipped);

    }
    else {

        /* otherwise, this is a fancier sprite - animate it */
        struct FRAME f = s->__internal__anim.frame[s->GetAnim(s)][s->__internal__anim.index];
        if (f.sound == -255) {

            // we've run out of frames, go back to zero
            if (s->__internal__looping) {
                f = s->__internal__anim.frame[s->GetAnim(s)][0];
                s->__internal__anim.index = 0;
            }
            else {
                --s->__internal__anim.index;
                s->__internal__frameDelay = 0;
                f = s->__internal__anim.frame[s->GetAnim(s)][s->__internal__anim.index];
            }

        }
        else {

            /* otherwise increment frame, if we've waited out the delay */
            ++s->__internal__frameDelay;
            if (s->__internal__frameDelay > (f.delay * s->__internal_slowAnim)) {
                ++s->__internal__anim.index;
                s->__internal__frameDelay = 0;

                // play frame sound if we're allow by the playFrameSounds variable
                if (playFrameSounds) {
                    if (f.sound > -1) {
                        playSound(f.sound);
                    }
                }

            }

        }

        /* finally, display retrieved frame */
        al_draw_tinted_scaled_rotated_bitmap_region(bmpLib[s->__internal__anim.graphicIndex].data,
           f.x, f.y, f.w, f.h,
           s->__internal_tint,
           0, 0, (x - (f.w / 2)) - floorf(camera.x),
                (y - f.h) - floorf(camera.y), s->GetScaleX(s), s->GetScaleY(s),
           s->GetAngle(s), s->flipped);
        //al_draw_rectangle(s->box.x - floorf(camera.x), s->box.y - floorf(camera.y), s->box.right - floorf(camera.x), s->box.bottom - floorf(camera.y), al_map_rgb(0, 255, 0), 1);

    }

}


/* done with interface!! */




int getRandom(int min, int max)
{

    /* get random number between two integers */
    return (( rand() % max ) + min);

}


void SetVelocityBetweenHitboxes(struct SPRITE *s, struct HITBOX a, float speed)
{

    /* calculate angle between a and b */
    float rads = atan2(s->box.centerY - a.centerY, a.centerX - s->box.centerX);

    /* now speed is set to the velocity between two sprites */
    s->SetVY(s, -sin(rads) * speed);
    s->SetVX(s, cos(rads) * speed);

}



void createSprite(struct SPRITE *s)
{

    /* set up new sprite - note that init is called AFTER sprite is actually put into memory */

    int i;
    int c;

    // first set up interface
    s->GetX = GetX;
    s->GetY = GetY;
    s->GetAX = GetAX;
    s->GetAY = GetAY;
    s->GetVX = GetVX;
    s->GetVY = GetVY;
    s->SetX = SetX;
    s->SetY = SetY;
    s->SetAX = SetAX;
    s->SetAY = SetAY;
    s->SetVX = SetVX;
    s->SetVY = SetVY;
    s->GetDragY = GetDragY;
    s->GetMaxSpeedY = GetMaxSpeedY;
    s->GetDragX = GetDragX;
    s->GetMaxSpeedX = GetMaxSpeedX;
    s->SetDragY = SetDragY;
    s->SetMaxSpeedY = SetMaxSpeedY;
    s->SetDragX = SetDragX;
    s->SetMaxSpeedX = SetMaxSpeedX;
    s->GetAnim = GetAnim;
    s->SetAnim = SetAnim;
    s->GetAlive = GetAlive;
    s->SetAlive = SetAlive;
    s->GetHealth = GetHealth;
    s->SetHealth = SetHealth;
    s->GetDamage = GetDamage;
    s->SetDamage = SetDamage;
    s->GetAngle = GetAngle;
    s->SetAngle = SetAngle;
    s->GetScaleX = GetScaleX;
    s->GetScaleY = GetScaleY;
    s->SetScaleX = SetScaleX;
    s->SetScaleY = SetScaleY;
    s->update = updateSprite;
    s->draw = Draw;
    s->kill = killSprite;
    s->collides = Collides;
    s->SetTint = SetTint;
    s->GetVisible = GetVisible;
    s->SetVisible =SetVisible;

    // rarely used scale and rotate
    s->__internal__scaleX = 1;
    s->__internal__scaleY = 1;
    s->__internal__angle = 0;

    // clear internals - note that anim is blank by setting it to -1
    s->__internal__z = false;
    s->__internal__alive = true;
    s->__internal__ax = 0;
    s->__internal__ay = 0;
    s->__internal__vx = 0;
    s->__internal__vy = 0;
    s->__internal__drag = 0;
    s->__internal__frame = 0;
    s->__internal__frameDelay = 0;
    s->__internal__maxspeedx = 10000;
    s->__internal__maxspeedy = 10000;
    s->__internal__anim.index = -1;
    s->__internal__strip = -1;
    s->__internal_tint = al_map_rgba(255, 255, 255, 255);
    s->__internal__visible = true;
    s->__internal__looping = false;
    s->__internal_slowAnim = 1;
    s->flipped = 0;

    // collision d
    s->groundTile = false;
    s->solid = false;
    s->collidable = false;
    for (i = 0; i < MAX_DIRECTIONS; ++i) {
        s->isTouching[i] = 0;
    }
    for (c = 0; c < MAX_CELLS; ++c) {
        s->cell[c] = 255;
    }

    // timer system
    s->GetTimeRemaining = GetTimeRemaining;
    s->timeLeft = -1;
    s->timerFunc = NULL;
    s->SetTimer = SetSpriteTimer;

    // set hitbox - nothing here yet, just an empty box
    newHitbox(&s->box, 0, 0, 1, 1);

    // same for data store
    if (s->data)
        free(s->data);
    s->data = NULL;

    // no lighting routines yet, so null here for now
    s->light = NULL;

    // no init yet, so null for now
    s->init = NULL;

    // alive by default
    s->SetAlive(s, true);

}





