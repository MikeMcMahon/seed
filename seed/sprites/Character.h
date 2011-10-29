#pragma once

#include "../sprites/GameSprite.h"

namespace Sprites { 
	class Character :
		public Sprites::GameSprite {

	private:
		wchar_t name[100];


	public:
		Character();
		~Character();

		void			Portrait(wchar_t[100]);
		const wchar_t*	Portrait();

	}; // Character Sprite
}
/* eof */