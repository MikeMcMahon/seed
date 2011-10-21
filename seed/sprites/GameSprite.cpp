#include "GameSprite.h"
#include "../util/TextureHandler.h"

using namespace Sprites;

const struct Scale DefaultScale = { 1.0f, 1.0f };
const struct Color DefaultColor = Color( 1.0f, 1.0f, 1.0f, 1.0f );

Sprites::GameSprite::GameSprite(wchar_t* resource, wchar_t* name, float width, float height) { 
	this->Init();
#ifdef RENDER_ENG_DX
    ZeroMemory(&(this->dxSprite), sizeof(D3DX10_SPRITE));
#endif

    // Set the width and height
	this->Size ( height, width );
    this->Name ( name );
    this->Resource ( resource );

}// GameSprite
Sprites::GameSprite::~GameSprite() { 
} 
Sprites::GameSprite::GameSprite(void) { 
    this->Name ( L"" );
    this->Resource ( L"" );
    this->Size ( 0, 0 );
    this->Init ( );
}

/*********************************
** Init ()
**  Initializes a default gamesprite
*********************************/
void GameSprite::Init() { 
    this->scale = DefaultScale;
    this->color = DefaultColor;

    this->CanAnimate ( false );
    this->CanMove ( false );
    this->IsVisible ( false );

    this->TextureLoaded ( false );
	this->SpriteType ( Type::base );
}

void GameSprite::SpriteType(Type::type kindOf) { 
	this->kindOf = kindOf;
}

Type::type GameSprite::SpriteType() { return this->kindOf; }

bool GameSprite::CanAnimate() { return canAnimate; } 
void GameSprite::CanAnimate(bool animate) { this->canAnimate = animate; } 

void GameSprite::CanMove(bool canMove) { this->canMove = canMove; }
bool GameSprite::CanMove() { return this->canMove; }

void GameSprite::IsVisible(bool visible) { this->isVisible = visible; }
bool GameSprite::IsVisible() { return this->isVisible; };

void GameSprite::Name(wchar_t* name) { wcscpy_s ( this->name, name ); }
const wchar_t* GameSprite::Name() { return this->name; }
/* eof */