#ifndef __NPCSPRITE_H_INCLUDE__
#define __NPCSPRITE_H_INCLUDE__

#include "CharacterSprite.h"

namespace sprites { 
	struct NpcSprite : public CharacterSprite {
		char * walkPattern;				// Basic walking pattern, e.g LLRLUD would walk the NPC left, left, Right, Up, Down...the pattern would then be reversed DULRLL
	};
}

#endif