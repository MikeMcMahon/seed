#include "FontSprite.h"

using namespace Sprites;

FontSprite::FontSprite(void)
{
	this->sprite.canAnimate = (false);
	this->animationDetail(0,0,0);
	this->sprite.canMove =(false);
	this->sprite.isVisible =(true);
	this->sprite.kindOf = Type::font;
}


FontSprite::~FontSprite(void)
{
}

LPCWSTR FontSprite::Message() { 
	return this->message.c_str();
}

void FontSprite::Message(LPCWSTR message) { 
	this->message = message;
}

void FontSprite::FontColor(D3DXCOLOR color) { 
	this->color = color;
}