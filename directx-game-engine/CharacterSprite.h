#ifndef __CHARACTER_H_INCLUDE__
#define __CHARACTER_H_INCLUDE__

#include "GameSprite.h"

class CharacterSprite : public GameSprite {
	CharacterSprite();	// Default constructor
	~CharacterSprite();	// Default destructor 
	void ResetSpriteAnim();
	void JumpToFramePos(int, int);
	void SetSpriteDefault(int, int);
private:
	int defaultStateFrameX;
	int defaultStateFrameY;
};

#endif