#include "GameSprite.h"
#include "../util/TextureHandler.h"

using namespace Sprites;

Sprites::GameSprite::GameSprite(LPCWSTR textureName, std::wstring name, float width, float height, ID3D10Device* pD3DDevice) { 
    this->position(0,0,0);
    this->canAnimate(false);
    this->isVisible(false);
    this->kindOf = ::base;

    // Set the width and height
    this->spriteSize(width, height);
    this->textureResourceName = textureName;
	this->name = name;

	// Load up the texture 
	this->LoadTexture(pD3DDevice);

}// GameSprite

Sprites::GameSprite::GameSprite() {
	this->position(0,0,0);
	this->canAnimate(false);
	this->isVisible(false);
	this->kindOf = ::base;
} // GameSprite

Sprites::GameSprite::~GameSprite() { 
	//this->pTexture->Release();
} 

void Sprites::GameSprite::Texture(LPCWSTR texture, ID3D10Device* pD3DDevice ) { 
	this->textureResourceName = texture;
	this->LoadTexture(pD3DDevice);
}

void Sprites::GameSprite::LoadTexture(ID3D10Device* pD3DDevice) { 
	ID3D10Texture2D* texture = GameUtil::TextureHandler::GetTexture2DFromFile(this->textureResourceName.c_str(),pD3DDevice);
	try { 
		if (texture) { 
			GameUtil::TextureHandler::GetResourceViewFromTexture(texture,&this->pTexture, pD3DDevice);
			texture->Release();	
		}
	} catch (...) { 
		// TODO - we should set some flag on the sprite that's it not usable
		this->isVisible(false);
		this->canAnimate(false);
		this->canMove(false);
	}
}


/*
* Get the name of the sprite
*/
LPCWSTR Sprites::GameSprite::Name() { 
	return this->name.c_str();
} 

/*
* Sets the name of the sprite
*/
void Sprites::GameSprite::Name( std::wstring name ) { 
	this->name = name;
}

void Sprites::GameSprite::animationDetail(int startFrame, int numFrames, float animDuration) { 
	ZeroMemory(&animation, sizeof(ANIMATION)); 
	this->animation.animDuration = animDuration; 
	this->animation.numFrames = numFrames; 
	this->animation.startFrame = startFrame;

	// Determine the number of frames to skip
	this->skipFrames = ( TICKS_PER_SECOND * animDuration ) / (float) numFrames;
	this->curSkip = 0; 
} // animationDetail

Sprites::GameSprite::ANIMATION Sprites::GameSprite::animationDetail() { 
	return this->animation; 
} 

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

void Sprites::GameSprite::position(float x, float y, float z) { 
	ZeroMemory(&pos, sizeof(POINT)); 
	this->pos.x = x; 
	this->pos.y = y; 
	this->pos.z = z; 
} // position

Sprites::GameSprite::POINT Sprites::GameSprite::position() { 
	return this->pos; 
} 

void Sprites::GameSprite::setMoveDistance( float x, float y ) { 
	this->moveX = x; this->moveY = y; 
} 

float Sprites::GameSprite::getMoveX() { 
	return this->moveX; 
}

float Sprites::GameSprite::getMoveY() { 
	return this->moveY; 
}

void Sprites::GameSprite::spriteSize(float width, float height) { 
	ZeroMemory(&this->size, sizeof(SIZE)); 
	this->size.height = height; 
	this->size.width = width; 
} // spriteSize

Sprites::GameSprite::SIZE Sprites::GameSprite::spriteSize() { 
	return this->size; 
} 

bool Sprites::GameSprite::isVisible() { 
	return this->visible; 
}

void Sprites::GameSprite::isVisible(bool visbility) { 
	this->visible = visbility; 
}

bool Sprites::GameSprite::canAnimate() { 
	return this->animateState; 
}

void Sprites::GameSprite::canAnimate(bool animate) { 
	this->animateState = animate; 
}

bool Sprites::GameSprite::canMove() { 
    return this->moveable;
}

void Sprites::GameSprite::canMove(bool canMove) { 
    this->moveable = canMove;
}
/* eof */