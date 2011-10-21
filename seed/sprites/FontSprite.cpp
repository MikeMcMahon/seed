#include "FontSprite.h"

using namespace Sprites;

const struct FontSprite::Color DEFAULT	= { 0.0f, 0.0f, 0.0f, 1.0f };
const struct FontSprite::Color DISABLED	= { 0.5f, 0.5f, 0.5f, 1.0f };
const struct FontSprite::Color HILIGHT	= { 1.0f, 0.0f, 0.0f, 0.0f };

FontSprite::FontSprite(void)
{
	this->SpriteType ( Type::font );
}


FontSprite::~FontSprite(void)
{
}

FontSprite::FontSprite(LPCWSTR message) { 
    //this->kindOf = Type::font;
	this->fontColor = DEFAULT;
	this->fontColorDisabled = DISABLED;
	this->fontColorHi = HILIGHT;
	wcscpy_s ( this->message, message );
	this->selected = false;
}