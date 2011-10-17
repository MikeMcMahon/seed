#pragma once
#include "GameSprite.h"

namespace Sprites { 
	class SpriteUtil : public GameSprite { 
	public:
		static void TranslateSprites(float, float, GameSprite*, int);
        static bool IsSpriteVisible(GameSprite* sprite);

	}; // SpriteUtil
}// Sprites
/* eof */