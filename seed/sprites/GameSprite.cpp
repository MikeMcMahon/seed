#include "GameSprite.h"
#include "../util/TextureHandler.h"

using namespace Sprites;

const struct Scale DefaultScale = { 1.0f, 1.0f };
const struct Color DefaultColor = { 1.0f, 1.0f, 1.0f, 1.0f };

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

void GameSprite::Init() { 
    this->scale = DefaultScale;
    this->color = DefaultColor;

    this->CanAnimate ( false );
    this->CanMove ( false );
    this->IsVisible ( false );

    this->kindOf = Type::base;
    this->TextureLoaded ( false );
}

/* eof */