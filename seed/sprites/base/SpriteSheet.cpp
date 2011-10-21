#include "SpriteSheet.h"

using namespace Sprites;

SpriteSheet::SpriteSheet(void)
{
}
SpriteSheet::~SpriteSheet(void)
{
}

SpriteSheet::SpriteSheet ( wchar_t resource[100] ) { 
	this->Resource ( resource );
} 

void SpriteSheet::Resource( wchar_t resource[100] ) { 
	wcscpy_s ( this->resource, resource );
}

const wchar_t* SpriteSheet::Resource () { 
	return this->resource;
}

void SpriteSheet::SheetSize ( Size size ) { 
	this->sheetSize = size;
}

Size SpriteSheet::SheetSize ( void ) { 
	return this->sheetSize;
}

void SpriteSheet::FrameDimensions ( int wide, int tall ) { 
	this->frameDimensions.width = (float)wide;
	this->frameDimensions.height = (float)tall;
}

Size SpriteSheet::FrameDimensions ( void ) { 
	return this->frameDimensions;
}

void SpriteSheet::FrameWidth ( int width ) { 
	this->frameWidth = width;
}
int  SpriteSheet::FrameWidth ( void ) { 
	return this->frameWidth;
}