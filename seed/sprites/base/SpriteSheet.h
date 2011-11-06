#pragma once

namespace Sprites { 
	class SpriteSheet
	{
	private:
		Util::SWSizeI	sheetSize;
		int				frameWidth;
		Util::SWSizeI	frameDimensions;
		wchar_t	resource[100];
	public:
		SpriteSheet(void);
		SpriteSheet ( wchar_t[100] );
		~SpriteSheet(void);

		void SheetSize ( Util::SWSizeI size );
		Util::SWSizeI SheetSize ( void );

		void FrameDimensions ( int wide, int tall );
		Util::SWSizeI FrameDimensions ( void );

		void FrameWidth ( int );
		int  FrameWidth ( void );

		void Resource ( wchar_t[100] ); 
		const wchar_t* Resource ( void );
	};
}
/* eof */