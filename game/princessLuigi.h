/* AUTOMATICALLY GENERATED HEADER FOR princessLuigi -- 9/23/2015 7:45:03 PM */

#include "sprite.h"

static const unsigned int princessScared=0;
static const unsigned int luigiWalk=1;
static const unsigned int princessJump=2;
static const unsigned int princessWalk=3;
static const unsigned int princessStand=4;
static const unsigned int princessKneel=5;
static const unsigned int luigiJump=6;

static void attachAnim_PrincessLuigi(struct SPRITE *s) 
{

	s->__internal__anim.graphicIndex = -1;
    s->__internal__anim.name = "princessLuigi.png";
s->__internal__anim.index = 0;
	s->__internal__anim.frame[princessScared][0].x = 106; // animation:  princessScared 
	s->__internal__anim.frame[princessScared][0].y = 0;
	s->__internal__anim.frame[princessScared][0].w = 24;
	s->__internal__anim.frame[princessScared][0].h = 38;
	s->__internal__anim.frame[princessScared][0].sound = -1;
	s->__internal__anim.frame[princessScared][0].delay = 1;
	s->__internal__anim.frame[princessScared][0].x = 131; // animation:  princessScared 
	s->__internal__anim.frame[princessScared][0].y = 0;
	s->__internal__anim.frame[princessScared][0].w = 24;
	s->__internal__anim.frame[princessScared][0].h = 38;
	s->__internal__anim.frame[princessScared][0].sound = -1;
	s->__internal__anim.frame[princessScared][0].delay = 1;
	s->__internal__anim.frame[princessScared][1].x = 27; // animation:  princessScared 
	s->__internal__anim.frame[princessScared][1].y = 0;
	s->__internal__anim.frame[princessScared][1].w = 26;
	s->__internal__anim.frame[princessScared][1].h = 38;
	s->__internal__anim.frame[princessScared][1].sound = -1;
	s->__internal__anim.frame[princessScared][1].delay = 1;
	s->__internal__anim.frame[princessScared][2].x = 54; // animation:  princessScared 
	s->__internal__anim.frame[princessScared][2].y = 0;
	s->__internal__anim.frame[princessScared][2].w = 26;
	s->__internal__anim.frame[princessScared][2].h = 37;
	s->__internal__anim.frame[princessScared][2].sound = -1;
	s->__internal__anim.frame[princessScared][2].delay = 1;
	
	s->__internal__anim.frame[princessScared][4].sound = -255;

	s->__internal__anim.frame[luigiWalk][0].x = 42; // animation:  luigiWalk 
	s->__internal__anim.frame[luigiWalk][0].y = 76;
	s->__internal__anim.frame[luigiWalk][0].w = 16;
	s->__internal__anim.frame[luigiWalk][0].h = 34;
	s->__internal__anim.frame[luigiWalk][0].sound = -1;
	s->__internal__anim.frame[luigiWalk][0].delay = 1;
	s->__internal__anim.frame[luigiWalk][1].x = 147; // animation:  luigiWalk 
	s->__internal__anim.frame[luigiWalk][1].y = 76;
	s->__internal__anim.frame[luigiWalk][1].w = 16;
	s->__internal__anim.frame[luigiWalk][1].h = 34;
	s->__internal__anim.frame[luigiWalk][1].sound = -1;
	s->__internal__anim.frame[luigiWalk][1].delay = 1;
	s->__internal__anim.frame[luigiWalk][2].x = 236; // animation:  luigiWalk 
	s->__internal__anim.frame[luigiWalk][2].y = 74;
	s->__internal__anim.frame[luigiWalk][2].w = 19;
	s->__internal__anim.frame[luigiWalk][2].h = 32;
	s->__internal__anim.frame[luigiWalk][2].sound = -1;
	s->__internal__anim.frame[luigiWalk][2].delay = 1;
	s->__internal__anim.frame[luigiWalk][3].x = 176; // animation:  luigiWalk 
	s->__internal__anim.frame[luigiWalk][3].y = 74;
	s->__internal__anim.frame[luigiWalk][3].w = 19;
	s->__internal__anim.frame[luigiWalk][3].h = 33;
	s->__internal__anim.frame[luigiWalk][3].sound = -1;
	s->__internal__anim.frame[luigiWalk][3].delay = 1;
	s->__internal__anim.frame[luigiWalk][4].x = 113; // animation:  luigiWalk 
	s->__internal__anim.frame[luigiWalk][4].y = 76;
	s->__internal__anim.frame[luigiWalk][4].w = 16;
	s->__internal__anim.frame[luigiWalk][4].h = 34;
	s->__internal__anim.frame[luigiWalk][4].sound = -1;
	s->__internal__anim.frame[luigiWalk][4].delay = 1;
	s->__internal__anim.frame[luigiWalk][5].x = 75; // animation:  luigiWalk 
	s->__internal__anim.frame[luigiWalk][5].y = 40;
	s->__internal__anim.frame[luigiWalk][5].w = 19;
	s->__internal__anim.frame[luigiWalk][5].h = 34;
	s->__internal__anim.frame[luigiWalk][5].sound = -1;
	s->__internal__anim.frame[luigiWalk][5].delay = 1;
	s->__internal__anim.frame[luigiWalk][6].x = 176; // animation:  luigiWalk 
	s->__internal__anim.frame[luigiWalk][6].y = 39;
	s->__internal__anim.frame[luigiWalk][6].w = 21;
	s->__internal__anim.frame[luigiWalk][6].h = 34;
	s->__internal__anim.frame[luigiWalk][6].sound = -1;
	s->__internal__anim.frame[luigiWalk][6].delay = 1;
	s->__internal__anim.frame[luigiWalk][7].x = 81; // animation:  luigiWalk 
	s->__internal__anim.frame[luigiWalk][7].y = 0;
	s->__internal__anim.frame[luigiWalk][7].w = 24;
	s->__internal__anim.frame[luigiWalk][7].h = 39;
	s->__internal__anim.frame[luigiWalk][7].sound = -1;
	s->__internal__anim.frame[luigiWalk][7].delay = 1;
	
	s->__internal__anim.frame[luigiWalk][8].sound = -255;

	s->__internal__anim.frame[princessJump][0].x = 21; // animation:  princessJump 
	s->__internal__anim.frame[princessJump][0].y = 39;
	s->__internal__anim.frame[princessJump][0].w = 20;
	s->__internal__anim.frame[princessJump][0].h = 37;
	s->__internal__anim.frame[princessJump][0].sound = -1;
	s->__internal__anim.frame[princessJump][0].delay = 1;
	s->__internal__anim.frame[princessJump][1].x = 106; // animation:  princessJump 
	s->__internal__anim.frame[princessJump][1].y = 39;
	s->__internal__anim.frame[princessJump][1].w = 21;
	s->__internal__anim.frame[princessJump][1].h = 35;
	s->__internal__anim.frame[princessJump][1].sound = -1;
	s->__internal__anim.frame[princessJump][1].delay = 1;
	s->__internal__anim.frame[princessJump][2].x = 180; // animation:  princessJump 
	s->__internal__anim.frame[princessJump][2].y = 0;
	s->__internal__anim.frame[princessJump][2].w = 21;
	s->__internal__anim.frame[princessJump][2].h = 38;
	s->__internal__anim.frame[princessJump][2].sound = -1;
	s->__internal__anim.frame[princessJump][2].delay = 1;
	s->__internal__anim.frame[princessJump][3].x = 223; // animation:  princessJump 
	s->__internal__anim.frame[princessJump][3].y = 39;
	s->__internal__anim.frame[princessJump][3].w = 21;
	s->__internal__anim.frame[princessJump][3].h = 34;
	s->__internal__anim.frame[princessJump][3].sound = -1;
	s->__internal__anim.frame[princessJump][3].delay = 1;
	s->__internal__anim.frame[princessJump][4].x = 156; // animation:  princessJump 
	s->__internal__anim.frame[princessJump][4].y = 0;
	s->__internal__anim.frame[princessJump][4].w = 23;
	s->__internal__anim.frame[princessJump][4].h = 35;
	s->__internal__anim.frame[princessJump][4].sound = -1;
	s->__internal__anim.frame[princessJump][4].delay = 1;
	
	s->__internal__anim.frame[princessJump][5].sound = -255;

	s->__internal__anim.frame[princessWalk][0].x = 202; // animation:  princessWalk 
	s->__internal__anim.frame[princessWalk][0].y = 0;
	s->__internal__anim.frame[princessWalk][0].w = 20;
	s->__internal__anim.frame[princessWalk][0].h = 39;
	s->__internal__anim.frame[princessWalk][0].sound = -1;
	s->__internal__anim.frame[princessWalk][0].delay = 1;
	s->__internal__anim.frame[princessWalk][1].x = 54; // animation:  princessWalk 
	s->__internal__anim.frame[princessWalk][1].y = 38;
	s->__internal__anim.frame[princessWalk][1].w = 20;
	s->__internal__anim.frame[princessWalk][1].h = 37;
	s->__internal__anim.frame[princessWalk][1].sound = -1;
	s->__internal__anim.frame[princessWalk][1].delay = 1;
	s->__internal__anim.frame[princessWalk][2].x = 0; // animation:  princessWalk 
	s->__internal__anim.frame[princessWalk][2].y = 38;
	s->__internal__anim.frame[princessWalk][2].w = 20;
	s->__internal__anim.frame[princessWalk][2].h = 37;
	s->__internal__anim.frame[princessWalk][2].sound = -1;
	s->__internal__anim.frame[princessWalk][2].delay = 1;
	s->__internal__anim.frame[princessWalk][3].x = 128; // animation:  princessWalk 
	s->__internal__anim.frame[princessWalk][3].y = 39;
	s->__internal__anim.frame[princessWalk][3].w = 20;
	s->__internal__anim.frame[princessWalk][3].h = 36;
	s->__internal__anim.frame[princessWalk][3].sound = -1;
	s->__internal__anim.frame[princessWalk][3].delay = 1;
	
	s->__internal__anim.frame[princessWalk][4].sound = -255;

	s->__internal__anim.frame[princessStand][0].x = 223; // animation:  princessStand 
	s->__internal__anim.frame[princessStand][0].y = 0;
	s->__internal__anim.frame[princessStand][0].w = 20;
	s->__internal__anim.frame[princessStand][0].h = 38;
	s->__internal__anim.frame[princessStand][0].sound = -1;
	s->__internal__anim.frame[princessStand][0].delay = 1;
	
	s->__internal__anim.frame[princessStand][1].sound = -255;

	s->__internal__anim.frame[princessKneel][0].x = 156; // animation:  princessKneel 
	s->__internal__anim.frame[princessKneel][0].y = 36;
	s->__internal__anim.frame[princessKneel][0].w = 19;
	s->__internal__anim.frame[princessKneel][0].h = 39;
	s->__internal__anim.frame[princessKneel][0].sound = -1;
	s->__internal__anim.frame[princessKneel][0].delay = 1;
	s->__internal__anim.frame[princessKneel][1].x = 217; // animation:  princessKneel 
	s->__internal__anim.frame[princessKneel][1].y = 74;
	s->__internal__anim.frame[princessKneel][1].w = 18;
	s->__internal__anim.frame[princessKneel][1].h = 34;
	s->__internal__anim.frame[princessKneel][1].sound = -1;
	s->__internal__anim.frame[princessKneel][1].delay = 1;
	s->__internal__anim.frame[princessKneel][2].x = 0; // animation:  princessKneel 
	s->__internal__anim.frame[princessKneel][2].y = 76;
	s->__internal__anim.frame[princessKneel][2].w = 18;
	s->__internal__anim.frame[princessKneel][2].h = 32;
	s->__internal__anim.frame[princessKneel][2].sound = -1;
	s->__internal__anim.frame[princessKneel][2].delay = 1;
	
	s->__internal__anim.frame[princessKneel][3].sound = -255;

	s->__internal__anim.frame[luigiJump][0].x = 196; // animation:  luigiJump 
	s->__internal__anim.frame[luigiJump][0].y = 76;
	s->__internal__anim.frame[luigiJump][0].w = 16;
	s->__internal__anim.frame[luigiJump][0].h = 34;
	s->__internal__anim.frame[luigiJump][0].sound = -1;
	s->__internal__anim.frame[luigiJump][0].delay = 1;
	s->__internal__anim.frame[luigiJump][1].x = 0; // animation:  luigiJump 
	s->__internal__anim.frame[luigiJump][1].y = 0;
	s->__internal__anim.frame[luigiJump][1].w = 16;
	s->__internal__anim.frame[luigiJump][1].h = 33;
	s->__internal__anim.frame[luigiJump][1].sound = -1;
	s->__internal__anim.frame[luigiJump][1].delay = 1;
	s->__internal__anim.frame[luigiJump][2].x = 75; // animation:  luigiJump 
	s->__internal__anim.frame[luigiJump][2].y = 75;
	s->__internal__anim.frame[luigiJump][2].w = 19;
	s->__internal__anim.frame[luigiJump][2].h = 32;
	s->__internal__anim.frame[luigiJump][2].sound = -1;
	s->__internal__anim.frame[luigiJump][2].delay = 1;
	s->__internal__anim.frame[luigiJump][3].x = 198; // animation:  luigiJump 
	s->__internal__anim.frame[luigiJump][3].y = 40;
	s->__internal__anim.frame[luigiJump][3].w = 18;
	s->__internal__anim.frame[luigiJump][3].h = 35;
	s->__internal__anim.frame[luigiJump][3].sound = -1;
	s->__internal__anim.frame[luigiJump][3].delay = 1;
	s->__internal__anim.frame[luigiJump][4].x = 130; // animation:  luigiJump 
	s->__internal__anim.frame[luigiJump][4].y = 76;
	s->__internal__anim.frame[luigiJump][4].w = 16;
	s->__internal__anim.frame[luigiJump][4].h = 34;
	s->__internal__anim.frame[luigiJump][4].sound = -1;
	s->__internal__anim.frame[luigiJump][4].delay = 1;
	s->__internal__anim.frame[luigiJump][5].x = 19; // animation:  luigiJump 
	s->__internal__anim.frame[luigiJump][5].y = 77;
	s->__internal__anim.frame[luigiJump][5].w = 16;
	s->__internal__anim.frame[luigiJump][5].h = 33;
	s->__internal__anim.frame[luigiJump][5].sound = -1;
	s->__internal__anim.frame[luigiJump][5].delay = 1;
	s->__internal__anim.frame[luigiJump][6].x = 95; // animation:  luigiJump 
	s->__internal__anim.frame[luigiJump][6].y = 75;
	s->__internal__anim.frame[luigiJump][6].w = 17;
	s->__internal__anim.frame[luigiJump][6].h = 34;
	s->__internal__anim.frame[luigiJump][6].sound = -1;
	s->__internal__anim.frame[luigiJump][6].delay = 1;
	
	s->__internal__anim.frame[luigiJump][7].sound = -255;

}

