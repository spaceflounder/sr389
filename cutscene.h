#ifndef CUTSCENE_H
#define CUTSCENE_H

// cutscene header for SR389

void startCustomCutscene(void);
void endCustomCutscene(void);
unsigned int refreshCutscene(void);
void moveSpriteCutscene(struct SPRITE *s, unsigned int animIndex, unsigned int loopAnim, float x, float y, float speed);
void moveSpriteCutsceneDirection(struct SPRITE *s, unsigned int animIndex, unsigned int loopAnim, unsigned int direction, float distance, float speed);


#endif // CUTSCENE_H

