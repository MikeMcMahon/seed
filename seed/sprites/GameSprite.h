#pragma once

#include "..\sprites\base\ISprite.h"
#include "..\sprites\animations\FrameAnimation.h" 
#include "..\sprites\base\Scale.h"
#include "..\sprites\base\Color.h"

namespace Sprites {
	class GameSprite : public ISprite, public FrameAnimation {
	private: 
        bool canAnimate;
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
	}; // GameSprite
} // Sprites
/* eof */