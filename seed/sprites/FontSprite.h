#pragma once

#include "GameSprite.h"

class FontSprite :
	public Sprites::GameSprite
{
private:
	std::wstring message;
public:
	FontSprite(void);
	~FontSprite(void);
	void Message(LPCWSTR message);
	LPCWSTR Message();

};

