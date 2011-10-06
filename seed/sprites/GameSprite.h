#ifndef __GAMEHEADERS_H_INCLUDE__
#define __GAMEHEADERS_H_INCLUDE__

#include "../main/GameHeaders.h"

#define MAX_SPRITES 1024			// Max sprites to draw at any given time
#define NUM_POOL_SPRITES 2048		// Max sprites to keep in memory

namespace sprites { 
	enum TYPE { 
		BASE,
		CHARACTER,
		NPC,
		TILE};
	class GameSprite : public D3DX10_SPRITE {
	public:
		TYPE kindOf;
		struct POINT {
			float x;
			float y; 
			float z;
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
	private:
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
		float curSkip;					// How many frames have been currently skipped
		BOOL visible;					// Is sprite visible
		BOOL animateState;				// Can sprite animate
		BOOL flipSprite;				// Flip sprite on the horizontal 
		BOOL canInteract;				// Can this sprite interact with other sprites
	public:
		GameSprite();
		~GameSprite();
		void animationDetail(int startFrame, int numFrames, float animDuration);
		ANIMATION animationDetail();
		float curFrame();
		void curFrame(float newFrame);
		void incrementFrame();
		void position(float x, float y, float z);
		POINT position();
		void setMoveDistance( float x, float y );
		float getMoveX();
		float getMoveY();
		void spriteSize(float height, float width);
		SIZE spriteSize();
		BOOL isVisible();
		void isVisible(BOOL visbility);
		BOOL canAnimate();
		void canAnimate(BOOL animate);

		void nextFrame();
		void ResetSpriteAnim();
		void JumpToFramePos(int, int);
		void SetSpriteDefault(int, int);
	};

}
////////////////////// ENDIF for Header Protection //////////////////////
#endif