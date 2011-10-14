#include "FontSprite.h"

using namespace Sprites;

const struct FontSprite::Color DEFAULT	= { 0.0f, 0.0f, 0.0f, 1.0f };
const struct FontSprite::Color DISABLED	= { 0.5f, 0.5f, 0.5f, 1.0f };
const struct FontSprite::Color HILIGHT	= { 1.0f, 0.0f, 0.0f, 0.0f };

FontSprite::FontSprite(void)
{
}


FontSprite::~FontSprite(void)
{
}

FontSprite::FontSprite(LPCSTR message) { 
	this->sprite.kindOf = Type::font;
	this->fontColor = DEFAULT;
	this->fontColorDisabled = DISABLED;
	this->fontColorHi = HILIGHT;
	this->message = message;
	this->selected = false;
}