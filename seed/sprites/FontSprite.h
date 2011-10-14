#pragma once

#include "GameSprite.h"

namespace Sprites { 
	class FontSprite :
		public Sprites::GameSprite
	{
	public:
		struct Color { 
			float r;
			float g;
			float b;
			float a;
		};

		FontSprite(void);
		FontSprite(LPCSTR message);
		~FontSprite(void);

		std::string message;
		Color fontColor;
		Color fontColorDisabled;
		Color fontColorHi;
		Color fontSize;
		bool selected;
	};
}
/* eof */
