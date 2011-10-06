#ifndef __SPRITEUTIL_H_INCLUDE__
#define __SPRITEUTIL_H_INCLUDE__

#include "GameSprite.h"

namespace Sprites { 
	class SpriteUtil : public GameSprite { 
	public:
		static void TranslateSprites(float, float, GameSprite*, int);

	}; // SpriteUtil
}// Sprites

#endif
/* eof */