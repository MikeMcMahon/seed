#pragma once
#include "GameSprite.h"

namespace Sprites { 
	class SpriteUtil : public GameSprite { 
	public:
		static void TranslateSprites(float, float, GameSprite*, int);

	}; // SpriteUtil
}// Sprites
/* eof */