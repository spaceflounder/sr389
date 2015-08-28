#ifndef SPRITE_H
#define SPRITE_H

#include "allegro5/allegro.h"

#include "anim.h"
#include "hitbox.h"

#define MAX_SPRITES     512
#define MAX_FX          2048


/* sprite data extension interface, in case we need some floats or an extra struct or whatever */
#define SPRITE_EXTEND(x)        struct x *data; data = s->data = (struct x *)malloc(sizeof(struct x))
#define GET_EXTEND(x)           struct x *data; data = (struct x *)s->data


/* cell per sprite max */
#define MAX_CELLS       4

/* directions sprite can be touching, left right up down */
#define MAX_DIRECTIONS  4

/* collision sides */
#define LEFT            0
#define UP              1
#define RIGHT           2
#define DOWN            3
#define FORWARD         4
#define LOWERLEFT       5
#define LOWERRIGHT      6
#define UPPERLEFT       7
#define UPPERRIGHT      8


/* all sprites are on linked lists -
   also note that all sprites are essentially interfaces, function collections which can be overridden */
struct SPRITE
{

    /* important interface functions here - each includes an index number, in case there's
        more than one on the screen */
    void (*init)(struct SPRITE *);
    void (*update)(struct SPRITE *);
    void (*draw)(struct SPRITE *);
    void (*kill)(struct SPRITE *);
    void (*light)(struct SPRITE *);

    /* movement functions */
    float (*GetX)(struct SPRITE *s);
    float (*GetY)(struct SPRITE *s);
    void (*SetX)(struct SPRITE *s, float val);
    void (*SetY)(struct SPRITE *s, float val);
    float (*GetVX)(struct SPRITE *s);
    float (*GetVY)(struct SPRITE *s);
    void (*SetVX)(struct SPRITE *s, float val);
    void (*SetVY)(struct SPRITE *s, float val);
    float (*GetAX)(struct SPRITE *s);
    float (*GetAY)(struct SPRITE *s);
    void (*SetAX)(struct SPRITE *s, float val);
    void (*SetAY)(struct SPRITE *s, float val);
    float (*GetDragX)(struct SPRITE *s);
    float (*GetMaxSpeedX)(struct SPRITE *s);
    float (*GetDragY)(struct SPRITE *s);
    float (*GetMaxSpeedY)(struct SPRITE *s);
    void (*SetDragX)(struct SPRITE *s, float val);
    void (*SetMaxSpeedX)(struct SPRITE *s, float val);
    void (*SetDragY)(struct SPRITE *s, float val);
    void (*SetMaxSpeedY)(struct SPRITE *s, float val);

    /* collision detection */
    int (*collides)(struct SPRITE *s, struct SPRITE *other);

    /* animation/graphical effects */
    int (*GetAnim)(struct SPRITE *s);
    void (*SetAnim)(struct SPRITE *s, int val, int looping);
    float (*GetScaleX)(struct SPRITE *s);
    void (*SetScaleX)(struct SPRITE *s, float val);
    float (*GetScaleY)(struct SPRITE *s);
    void (*SetScaleY)(struct SPRITE *s, float val);
    float (*GetAngle)(struct SPRITE *s);
    void (*SetAngle)(struct SPRITE *s, float val);
    void (*SetTint)(struct SPRITE *s, float r, float g, float b, float a);

    /* sprite stats */
    unsigned int (*GetAlive)(struct SPRITE *s);
    void (*SetAlive)(struct SPRITE *s, unsigned int val);
    int (*GetHealth)(struct SPRITE *s);
    void (*SetHealth)(struct SPRITE *s, int val);
    int (*GetDamage)(struct SPRITE *s);
    void (*SetDamage)(struct SPRITE *s, int val);
    int (*GetVisible)(struct SPRITE *s);
    void (*SetVisible)(struct SPRITE *s, unsigned int val);

    /* the sprite hitbox */
    struct HITBOX box;

    /* past all the interface stuff, move on to the internals */
    float __internal__vx;
    float __internal__vy;
    float __internal__ax;
    float __internal__ay;
    float __internal__drag;
    float __internal__maxspeedx;
    float __internal__maxspeedy;
    unsigned int __internal__alive;
    int __internal__strip;
    int __internal__frame;
    int __internal_slowAnim;
    unsigned int __internal__frameDelay;
    struct ANIM __internal__anim;
    int __internal__health;
    int __internal__damage;
    ALLEGRO_COLOR __internal_tint;

    /* scale and rotate - seldom used, but good to have */
    float __internal__scaleX;
    float __internal__scaleY;
    float __internal__angle;

    // sort order
    unsigned int __internal__z;

    /* graphical stuff */
    unsigned int __internal__visible;
    int __internal__looping;

    /* tilemap stuff, in case we're on a map */
    unsigned int onTileMap;

    /* currently used hashmap cells */
    unsigned int cell[MAX_CELLS];

    /* is sprite solid? */
    unsigned int solid;

    /* is sprite collidable? */
    unsigned int collidable;

    /* is this a ground tile?
        2 is standard ground
        1 is half tile
        0 is no ground (default)
    */
    unsigned int groundTile;

    /* sprite id, for collions */
    unsigned int id;

    /* sprite direction */
    unsigned int direction;

    /* collision walls */
    unsigned int isTouching[MAX_DIRECTIONS];

    /* timer - each sprite contains one timer */
    int timeLeft;
    void (*SetTimer)(struct SPRITE *s, float secs, void (*f)(struct SPRITE *));
    int (*GetTimeRemaining)(struct SPRITE *s);
    void (*timerFunc)(struct SPRITE *);

    /* additional data for sprite held in here - this can vary from sprite to sprite */
    void *data;

};



/* public interface members for other parts of the engine to use */
void initSprite(struct SPRITE *s, unsigned int index);
void updateSprite(struct SPRITE *s);
void copySprite(struct SPRITE *dst, struct SPRITE *src);
void drawSprite(struct SPRITE *s, float x, float y);
void createSprite(struct SPRITE *s);

// sprite collision table lookup
extern void (*collsionTable[MAX_TABLE][MAX_TABLE])(struct SPRITE *s1, struct SPRITE *s2);

// sprite managment tools
int getRandom(int min, int max);
void SetVelocityBetweenHitboxes(struct SPRITE *s, struct HITBOX a, float speed);
void focusCamaraOn(struct SPRITE *s);
void followSprite(struct SPRITE *s);

#endif // SPRITE_H

