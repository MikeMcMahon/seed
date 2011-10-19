#include "SpriteUtils.h"

using namespace Sprites;

/*
*	Translates the sprites X/Y position based on the input numbers 
*/
void ::SpriteUtil::TranslateSprites(float x, float y, GameSprite* sprites, int ignore) { 

	for(int i = 0; i < MAX_SPRITES; i++) {
		if (i == ignore) 
			continue;	// Skip this loop and continue on

        float sX = sprites[i].Position().x + x;
		float sY = sprites[i].Position().y + y;
        sprites[i].Position(sX, sY, 0);

        // Quick check of the sprite, did the x/y movement take it outside the visible bounds? if so we can clip the sprite
        sprites[i].IsVisible( IsSpriteVisible(sprites) );
    }
} // TranslateSprites


bool SpriteUtil::IsSpriteVisible(GameSprite* sprite) { 
    float top       = 0;
    float right     = 0;
    float bottom    = 0;
    float left      = 0;

    top = sprite->Position().y;
    right = sprite->Position().x + sprite->Size().width;
    bottom = sprite->Position().y + sprite->Size().height;
    left = sprite->Position().x;

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