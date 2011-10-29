#pragma once

#include "../base/Size.h"

namespace Sprites { 
	class SpriteSheet
	{
	private:
		Size	sheetSize;
		int		frameWidth;
		Size	frameDimensions;
		wchar_t	resource[100];
	public:
		SpriteSheet(void);
		SpriteSheet ( wchar_t[100] );
		~SpriteSheet(void);

		void SheetSize ( Size size );
		Size SheetSize ( void );

		void FrameDimensions ( int wide, int tall );
		Size FrameDimensions ( void );

		void FrameWidth ( int );
		int  FrameWidth ( void );

		void Resource ( wchar_t[100] ); 
		const wchar_t* Resource ( void );
	};
}
/* eof */