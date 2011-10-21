#pragma once

#include "..\sprites\base\ISprite.h"
#include "..\sprites\animations\FrameAnimation.h" 
#include "..\sprites\base\Scale.h"
#include "..\sprites\base\Color.h"
#include "..\sprites\base\SpriteSheet.h"

namespace Sprites {
	class GameSprite : public ISprite, public FrameAnimation, public SpriteSheet {
	private: 
        bool canAnimate;
        bool isVisible;
        bool canMove;
    	void Init();
	public:
        Color color;
        Scale scale;

#ifdef RENDER_ENG_DX
        D3DX10_SPRITE   dxSprite;
#elif defined(RENDER_ENG_GL)
        // No support for OpenGL Yet...or ever, who knows :) 
#endif
        GameSprite();
        GameSprite(wchar_t* resource, wchar_t* name, float width, float height);
		~GameSprite();
		
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