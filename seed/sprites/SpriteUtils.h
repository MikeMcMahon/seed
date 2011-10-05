#ifndef __SPRITEUTIL_H_INCLUDE__
#define __SPRITEUTIL_H_INCLUDE__

#include "GameSprite.h"

namespace sprites { 
	class SpriteUtil : public GameSprite { 
	public:
		static void TranslateSprites(float, float, GameSprite*, int);

	}; // util 
}

#endif // __SPRITEUTIL_H_INCLUDE__
/* eof */