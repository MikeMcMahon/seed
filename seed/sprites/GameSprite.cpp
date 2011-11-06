#include "GameSprite.h"

using namespace Sprites;

const Util::SWScale DefaultScale = { 1.0f, 1.0f };
const Util::SWColor DefaultColor = Util::SWColor( 1.0f, 1.0f, 1.0f, 1.0f );

Sprites::GameSprite::GameSprite(wchar_t* resource, wchar_t* name, float width, float height) { 
	this->Init();
#ifdef RENDER_ENG_DX
    ZeroMemory(&(this->dxSprite), sizeof(D3DX10_SPRITE));
#endif

	// Zero out the animations
	ZeroMemory(&(this->animations), sizeof(Animation) * MAX_ANIMTATIONS);
	
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
	this->savedAnimations = 0;
}

void GameSprite::SpriteType(Type::type kindOf) { 
	this->kindOf = kindOf;
}

/// SpriteType()
/// Returns the type of sprite this sprite is
Type::type GameSprite::SpriteType() { return this->kindOf; }


/// AddAnimation () 
/// Adds the given animation to the list of currently stored animations
/// Returns false if we've already stored as many animations as possible
bool GameSprite::AddAnimation ( wchar_t description[100], float duration, int numFrames, Util::SWCoordinates positionInSheet ) { 
	if (this->savedAnimations < MAX_ANIMTATIONS) { 
		Animation anim;
		wcscpy_s(anim.description, description);
		anim.duration = duration;
		anim.frameOnePosition = positionInSheet;
		anim.totalFrames = numFrames;
		
		this->animations[this->savedAnimations] = anim;
		
		// Increase the number of saved animations
		this->savedAnimations++;

		return true;
	}
	return false;
}

/// GetAnimation () 
/// Returns the animation with the given resource or a null animation
Animation GameSprite::GetAnimation ( wchar_t description[100] ) { 

	for (int i = 0; i < savedAnimations; i++) { 
		if (wcscmp(this->animations[i].description, description) == 0)
			return this->animations[i];
	}

	Animation anim;
	ZeroMemory(&anim, sizeof(Animation));
	return anim;
}

/// SetAnimation ()
/// Sets the given animation (based on the resource name in the supplied animation) 
/// To the given information in the struct
/// Returns false if it is unable match the given animation with one already stored
bool GameSprite::SetAnimation ( Animation animation ) { 
	for (int i = 0; i < savedAnimations; i++) { 
		if (wcscmp(this->animations[i].description, animation.description) == 0) {
			this->animations[i] = animation;
			return true;
		}
	}
	return false;
}

/// SyncPlayAnimation () 
/// Attempts to (if the sprite is already mid animating) start a new animation at the same frame
/// Location as the previous animation, if they have the same number of frames.  If not
/// then the animation will be played from the beginning
void GameSprite::SyncPlayAnimation ( wchar_t description[100] ) { 
	// Get the animation with the same name
	Animation anim = this->GetAnimation(description);

	if (wcslen(anim.description) > 0) { // we have a description 

		// TODO this doesn't really work the way the description says, yet.  Still need to impl that. 
		this->AnimationDetail ( anim.duration, anim.totalFrames );
	}	
}

/******************************
** CanAnimate ()
**
*******************************/
bool GameSprite::CanAnimate() { return canAnimate; } 
void GameSprite::CanAnimate(bool animate) { this->canAnimate = animate; } 

void GameSprite::CanMove(bool canMove) { this->canMove = canMove; }
bool GameSprite::CanMove() { return this->canMove; }

void GameSprite::IsVisible(bool visible) { this->isVisible = visible; }
bool GameSprite::IsVisible() { return this->isVisible; };

void GameSprite::Name(wchar_t* name) { wcscpy_s ( this->name, name ); }
const wchar_t* GameSprite::Name() { return this->name; }
/* eof */