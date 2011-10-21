#pragma once
#include "GameSprite.h"
#include <map>

namespace Sprites { 
	class MainCharacter {
		GameSprite	inTown;
		GameSprite	inBattle;
		GameSprite	worldMap;

		FrameAnimation inTownAnims[25];
		FrameAnimation inBattleAnims[25];
		FrameAnimation worldMapAnims[25];

		// Resource name for their portrait image used in message boxes and the inventory screen
		wchar_t portrait[100];
	public:
		MainCharacter();
		~MainCharacter();

		void			Portrait(wchar_t[100]);
		const wchar_t*	Portrait();

		void TownSprite ( GameSprite );
		void BattleSprite ( GameSprite );
		void WorldSprite ( GameSprite );

		GameSprite TownSprite();
		GameSprite BattleSprite();
		GameSprite WorldSprite(); 



	}; // Character Sprite
}
/* eof */