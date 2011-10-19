#include "GameSprite.h"
#include "../util/TextureHandler.h"

using namespace Sprites;

void GameSprite::Init() { 
	this->sprite = DefaultSprite;
}

Sprites::GameSprite::GameSprite() { 
	this->Init();
}

Sprites::GameSprite::GameSprite(const wchar_t* resource, const wchar_t* name, float width, float height) { 
	this->Init();
#ifdef RENDER_ENG_DX
    ZeroMemory(&(this->dxSprite), sizeof(D3DX10_SPRITE));
#endif
	ZeroMemory(&(this->sprite.position), sizeof(Position));

    this->sprite.canAnimate = (false);
    this->sprite.isVisible = (false);
	this->sprite.kindOf = Type::base;

    // Set the width and height
	this->sprite.size.height = height;
	this->sprite.size.width = width;
    wcscpy_s ( this->sprite.resource, resource );
	wcscpy_s ( this->sprite.name, name );

}// GameSprite

Sprites::GameSprite::~GameSprite() { 
} 

Sprites::GameSprite::operator D3DX10_SPRITE() { 
	D3DX10_SPRITE sprite;
	sprite.ColorModulate = this->sprite.color;
	return sprite;
}

void Sprites::GameSprite::animationDetail(int startFrame, int numFrames, float animDuration) { 
	this->sprite.animation.curFrame = 1; // Always start on the first frame
	this->sprite.animation.animDuration = animDuration; 
	this->sprite.animation.numFrames = numFrames; 
	this->sprite.animation.startFrame = startFrame;

	// Determine the number of frames to skip
	this->skipFrames = ( TICKS_PER_SECOND * animDuration ) / (float) numFrames;
	this->curSkip = 0; 
} // animationDetail

float Sprites::GameSprite::curFrame() { 
	return this->curFrameAnimate; 
} 

void Sprites::GameSprite::curFrame(float newFrame) { 
	this->curFrameAnimate = newFrame; 
} 

void Sprites::GameSprite::incrementFrame() { 
	if (this->curSkip <= this->skipFrames && this->curSkip == 0) { 
		this->curFrameAnimate++; 
	}
	if (this->curSkip >= this->skipFrames) {
		this->curSkip = 0;
		return;
	}
	curSkip++; 
}// incrementFrame
/* eof */