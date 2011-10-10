#pragma once

#define MAX_SPRITES 1024			// Max sprites to draw at any given time
#define NUM_POOL_SPRITES 2048		// Max sprites to keep in memory

namespace Sprites { 
	enum TYPE { 
		BASE,
		CHARACTER,
		NPC,
		TILE
	}; // Type
	
	class GameSprite : public D3DX10_SPRITE {
	public:
		TYPE kindOf;
		struct POINT {
			float x;
			float y; 
			float z;
		}; // POINT

		struct SIZE { 
			float height;
			float width;
		}; // SIZE

		struct ANIMATION {
			int startFrame;
			int numFrames;
			float animDuration;
		}; // ANIMATION
	
	private:
		int defaultStateFrameX;
		int defaultStateFrameY;
		LPCWSTR textureResourceName;	// Location where we can find the map file
		LPCWSTR name;					// The name of this particular sprite
		SIZE size;						// Size of the sprite in x/y measurements
		POINT pos;						// X/Y Position 
		ANIMATION animation;			// Animation information 
		float curFrameAnimate;			// Current frame in animation, we don't give direct access to this because well that would be dumb
		float moveX;					// Amount sprite can move in the x direction at a given time
		float moveY;					// Amount sprite can move in the y direction at a given time
		float displayRate;				// How often to display the animation 
		float skipFrames;				// Number of frames to skip based on duration of animation 
		float curSkip;					// How many frames have been currently skipped
		bool visible;					// Is sprite visible
		bool animateState;				// Can sprite animate
		bool flipSprite;				// Flip sprite on the horizontal 
		bool canInteract;				// Can this sprite interact with other sprites
        bool moveable;                  // Is this sprite able to move around
	public:
        GameSprite(LPCWSTR textureName,LPCWSTR name, float width, float height);
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
		void spriteSize(float width, float height);
		SIZE spriteSize();
		bool isVisible();
		void isVisible(bool visbility);
		bool canAnimate();
		void canAnimate(bool animate);
        bool canMove();
        void canMove(bool canMove);
		void nextFrame();
		void ResetSpriteAnim();
		void JumpToFramePos(int, int);		// TODO - Method stub
		void SetSpriteDefault(int, int);	// TODO - Method stub
		LPCWSTR Name();
		void Name(LPCWSTR name);
	}; // GameSprite

} // Sprites
/* eof */