#include "GameSprite.h"

using namespace sprites;

sprites::GameSprite::GameSprite() { 
	this->kindOf = ::BASE;
}

sprites::GameSprite::~GameSprite() { 

}
void sprites::GameSprite::animationDetail(int startFrame, int numFrames, float animDuration) { 
	ZeroMemory(&animation, sizeof(ANIMATION)); 
	this->animation.animDuration = animDuration; 
	this->animation.numFrames = numFrames; 
	this->animation.startFrame = startFrame;

	// Determine the number of frames to skip
	this->skipFrames = ( TICKS_PER_SECOND * animDuration ) / (float) numFrames;
	this->curSkip = 0; }

sprites::GameSprite::ANIMATION sprites::GameSprite::animationDetail() { 
	return this->animation; } 

float sprites::GameSprite::curFrame() { 
	return this->curFrameAnimate; }

void sprites::GameSprite::curFrame(float newFrame) { 
	this->curFrameAnimate = newFrame; }

void sprites::GameSprite::incrementFrame() { 
	if (this->curSkip <= this->skipFrames && this->curSkip == 0) { 
		this->curFrameAnimate++; 
	}
	if (this->curSkip >= this->skipFrames) {
		this->curSkip = 0;
		return;
	}
	curSkip++; }

void sprites::GameSprite::position(float x, float y, float z) { 
	ZeroMemory(&pos, sizeof(POINT)); 
	this->pos.x = x; 
	this->pos.y = y; 
	this->pos.z = z; }

sprites::GameSprite::POINT sprites::GameSprite::position() { 
	return this->pos; }

void sprites::GameSprite::setMoveDistance( float x, float y ) { this->moveX = x; this->moveY = y; }

float sprites::GameSprite::getMoveX() { 
	return this->moveX; }

float sprites::GameSprite::getMoveY() { 
	return this->moveY; }

void sprites::GameSprite::spriteSize(float height, float width) { 
	ZeroMemory(&this->size, sizeof(SIZE)); 
	this->size.height = height; 
	this->size.width = width; }

sprites::GameSprite::SIZE sprites::GameSprite::spriteSize() { 
	return this->size; } 

BOOL sprites::GameSprite::isVisible() { 
	return this->visible; }

void sprites::GameSprite::isVisible(BOOL visbility) { 
	this->visible = visbility; }

BOOL sprites::GameSprite::canAnimate() { 
	return this->animateState; }

void sprites::GameSprite::canAnimate(BOOL animate) { 
	this->animateState = animate; }