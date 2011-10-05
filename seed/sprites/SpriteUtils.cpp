#include "SpriteUtils.h"

using namespace sprites;

/*
*	Translates the sprites X/Y position based on the input numbers 
*/
void ::SpriteUtil::TranslateSprites(float x, float y, GameSprite* gameSprites, int ignore) { 

	for(int i = 0; i < MAX_SPRITES; i++) {
		if (i == ignore) 
			continue;	// Skip this loop and continue on

		float sX = (gameSprites + i)->position().x + x;
		float sY = (gameSprites + i)->position().y + y;
		float sZ = (gameSprites + i)->position().z;	// Unchanged

		(gameSprites + i)->position(sX, sY, sZ);
	}
} 

/* eof */