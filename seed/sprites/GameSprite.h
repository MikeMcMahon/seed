#pragma once
#include "..\sprites\Sprite.h"

namespace Sprites {
	class GameSprite {
	private: 

		float curSkip;
		float curFrameAnimate;
		float skipFrames;
		void Init();
	public:
#ifdef RENDER_ENG_DX
        D3DX10_SPRITE   dxSprite;
		operator D3DX10_SPRITE();	// TODO implement this in some form, do we need it?  Right now just does a color conversion, almost laughable
#elif defined(RENDER_ENG_GL)
        // No support for OpenGL Yet...or ever, who knows :) 
#endif
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