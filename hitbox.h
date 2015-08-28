#ifndef HITBOXLIB_H
#define HITBOXLIB_H


// max number of collision detection check objects
#define MAX_TABLE       64

/* hitbox header for collidable objects */
struct HITBOX
{

    /* the main four values */
    float x;
    float y;
    float width;
    float height;

    /* the following derive from the main four */
    float top;
    float bottom;
    float left;
    float right;

    /* flags for axis checks */
    unsigned int check[4];

    float centerX;
    float centerY;

};

/* support functions for hitboxes */
void newHitbox(struct HITBOX *h, float x, float y, float width, float height);
void resetCollisionTable();
int checkCollide(struct HITBOX h1, struct HITBOX h2);
int checkOverlap(float x1, float y1, float w1, float h1, float x2, float y2, float w2, float h2);
void resizeHitbox(struct HITBOX *h, float width, float height);
void updateHitbox(struct HITBOX *h);

#endif // HITBOXLIB_H
