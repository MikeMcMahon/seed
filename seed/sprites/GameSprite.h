#pragma once

#include "../sprites/base/ISprite.h"
#include "../sprites/animations/FrameAnimation.h" 
#include "../sprites/animations/Animation.h"
#include "../sprites/base/SpriteSheet.h"

namespace Sprites {
	class GameSprite : public ISprite, public FrameAnimation, public SpriteSheet {
	private: 
		static const int MAX_ANIMTATIONS = 100;
        bool canAnimate;
        bool isVisible;
        bool canMove;
    	void Init();
		int savedAnimations;
		Animation animations[GameSprite::MAX_ANIMTATIONS];
	public:
        Util::SWColor color;
		Util::SWScale scale;

#ifdef RENDER_ENG_DX
        D3DX10_SPRITE   dxSprite;
#elif defined(RENDER_ENG_GL)
        // No support for OpenGL Yet...or ever, who knows :) 
#endif
        GameSprite();
        GameSprite(wchar_t* resource, wchar_t* name, float width, float height);
		~GameSprite();

		bool AddAnimation ( wchar_t[100], float duration, int numFrames, Util::SWCoordinates );
		Animation GetAnimation ( wchar_t[100] );
		bool SetAnimation ( Animation );
		void SyncPlayAnimation ( wchar_t description[100] );

		void SpriteType( Type::type kindOf );
		Type::type SpriteType();

		bool CanAnimate();
		void CanAnimate(bool animate);

        void Name(wchar_t* name);
        const wchar_t* Name();

        void CanMove(bool canMove);
        bool CanMove();

        void IsVisible(bool visible);
        bool IsVisible();
	}; // GameSprite
} // Sprites
/* eof */