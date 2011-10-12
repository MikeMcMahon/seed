#pragma once

#include "GameSprite.h"

namespace Sprites { 
	class FontSprite :
		public Sprites::GameSprite
	{
	private:
		std::wstring message;
		D3DXCOLOR color;
		D3DXCOLOR hiColor;
		D3DXCOLOR loColor;
		bool selected;
	public:
		FontSprite(void);
		~FontSprite(void);
		void Message(LPCWSTR message);
		void FontColor(D3DXCOLOR color);
		D3DXCOLOR FontColor(); 

		// TODO - implement the selected functionality 
		bool isSelected(); 
		void isSelected(bool selected);
		LPCWSTR Message();
	};
}
/* eof */
