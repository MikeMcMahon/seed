#pragma once
#include "Sprite.h"

namespace Sprites {
	class GameSprite {
	private: 
		float curSkip;
		float curFrameAnimate;
		float skipFrames;
		void Init();
	public:
		GameSprite();
        GameSprite(const wchar_t* resource, const wchar_t* name, float width, float height);
		~GameSprite();
		Sprite			sprite;
		void			animationDetail(int startFrame, int numFrames, float animDuration);
		float			curFrame();
		void			curFrame(float newFrame);
		void			incrementFrame();
		void			nextFrame();
		void			ResetSpriteAnim();
	}; // GameSprite
} // Sprites
/* eof */