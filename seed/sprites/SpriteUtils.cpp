#include "SpriteUtils.h"

using namespace Sprites;

/*
*	Translates the sprites X/Y position based on the input numbers 
*/
void ::SpriteUtil::TranslateSprites(float x, float y, GameSprite* sprites, int ignore) { 

	for(int i = 0; i < MAX_SPRITES; i++) {
		if (i == ignore) 
			continue;	// Skip this loop and continue on

		float sX = (sprites + i)->sprite.position.x += x;
		float sY = (sprites + i)->sprite.position.y += y;

        // Quick check of the sprite, did the x/y movement take it outside the visible bounds? if so we can clip the sprite
        (sprites + i)->sprite.isVisible = IsSpriteVisible(sprites);
    }
} // TranslateSprites


bool SpriteUtil::IsSpriteVisible(GameSprite* sprite) { 
    float top       = 0;
    float right     = 0;
    float bottom    = 0;
    float left      = 0;

    top = sprite->sprite.position.y;
    right = sprite->sprite.position.x + sprite->sprite.size.width;
    bottom = sprite->sprite.position.y + sprite->sprite.size.height;
    left = sprite->sprite.position.x;

    if (top > WINDOW_HEIGHT)
        return false;
    if (bottom < 0)
        return false;
    if (left > WINDOW_WIDTH)
        return false;
    if (right < 0)
        return false;

    return true;
}

/* eof */