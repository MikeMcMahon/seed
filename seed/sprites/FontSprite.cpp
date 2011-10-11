#include "FontSprite.h"


FontSprite::FontSprite(void)
{
	this->canAnimate(false);
	this->animationDetail(0,0,0);
	this->canMove(false);
	this->isVisible(true);
	this->kindOf = Sprites::font;
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