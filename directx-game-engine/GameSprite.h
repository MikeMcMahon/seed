#ifndef __GAMEHEADERS_H_INCLUDE__
#define __GAMEHEADERS_H_INCLUDE__

#include "GameHeaders.h"

#define MAX_SPRITES 1024			// Max sprites to draw at any given time
#define NUM_POOL_SPRITES 2048		// Max sprites to keep in memory

class GameSprite : public D3DX10_SPRITE {
private:
	int defaultStateFrameX;
	int defaultStateFrameY;

public:
	char * textureResourceName;		// Location where we can find the map fileE {
	float width;					// Width of sprite
	float height;					// Height of sprite
	float posX;						// Sprite X position in the world
	float posY;						// Sprite Y position in the world
	float moveX;					// Amount sprite can move in the x direction at a given time
	float moveY;					// Amount sprite can move in the y direction at a given time
	float curFrame;					// Current frame being animated
	float numFrames;				// Number of frames total to animate
	BOOL visible;					// Is sprite visible
	BOOL canAnimate;				// Can sprite animate
	BOOL flipSprite;				// Flip sprite on the horizontal 
	BOOL canInteract;				// Can this sprite interact with other sprites

	void ResetSpriteAnim();
	void JumpToFramePos(int, int);
	void SetSpriteDefault(int, int);
};

////////////////////// ENDIF for Header Protection //////////////////////
#endif