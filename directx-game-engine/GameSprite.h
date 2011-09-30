#ifndef __GAMEHEADERS_H_INCLUDE__
#define __GAMEHEADERS_H_INCLUDE__

#include "GameHeaders.h"

#define MAX_SPRITES 1024			// Max sprites to draw at any given time
#define NUM_POOL_SPRITES 2048		// Max sprites to keep in memory

class GameSprite : public D3DX10_SPRITE {
private:
	struct POINT {
		float x;
		float y; 
	};

	struct SIZE { 
		float height;
		float width;
	};
	struct ANIMATION {
		int startFrame;
		int numFrames;
		float animDuration;
	};

	int defaultStateFrameX;
	int defaultStateFrameY;
	char * textureResourceName;		// Location where we can find the map fileE {
	SIZE size;						// Size of the sprite in x/y measurements
	POINT pos;						// X/Y Position 
	ANIMATION animation;			// Animation information 
	float curFrameAnimate;			// Current frame in animation, we don't give direct access to this because well that would be dumb
	float moveX;					// Amount sprite can move in the x direction at a given time
	float moveY;					// Amount sprite can move in the y direction at a given time
	float displayRate;				// How often to display the animation 
	float skipFrames;				// Number of frames to skip based on duration of animation 
	BOOL visible;					// Is sprite visible
	BOOL animateState;				// Can sprite animate
	BOOL flipSprite;				// Flip sprite on the horizontal 
	BOOL canInteract;				// Can this sprite interact with other sprites

public:
	void animationDetail(int startFrame, int numFrames, float animDuration) { ZeroMemory(&animation, sizeof(ANIMATION)); animation.animDuration = animDuration; animation.numFrames = numFrames; animation.startFrame = startFrame;}
	ANIMATION animationDetail() { return animation; } 
	float curFrame() { return curFrameAnimate; }
	void curFrame(float newFrame) { curFrameAnimate = newFrame; }
	void incrementFrame() { curFrameAnimate++; } 
	void position(float x, float y) { ZeroMemory(&pos, sizeof(POINT)); pos.x = x; pos.y = y; };
	POINT position() { return pos; }
	void setMoveDistance( float x, float y ) { moveX = x; moveY = y; }
	float getMoveX() { return moveX; }
	float getMoveY() { return moveY; }
	void spriteSize(float height, float width) { ZeroMemory(&size, sizeof(SIZE)); size.height = height; size.width = width; }
	SIZE spriteSize() { return size; } 
	BOOL isVisible() { return visible; }
	void isVisible(BOOL visbility) { visible = visbility; }
	BOOL canAnimate() { return animateState; }
	void canAnimate(BOOL animate) { animateState = animate; }

	void nextFrame();
	void ResetSpriteAnim();
	void JumpToFramePos(int, int);
	void SetSpriteDefault(int, int);
};

////////////////////// ENDIF for Header Protection //////////////////////
#endif