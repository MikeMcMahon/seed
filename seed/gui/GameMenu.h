#pragma once

#include "../sprites/GameSprite.h"

namespace Gui { 
	struct Status { enum code { 
		ok,
		failed };};
	struct MenuStyle {enum style {
			absolute,
			relative };};
	struct MenuFrame { 
		float height;
		float width;
		float x;
		float y;
		wchar_t* resource;
	};
	struct MenuOptions {
		MenuStyle::style display;
		float height;
		float width;
		float x;
		float y;
		wchar_t* cursor;
	};
    class GameMenu
    {
    private:
		MenuFrame menuFrame;
		MenuOptions menuOptions;
        std::vector<Sprites::GameSprite> menuOpts;
		Sprites::GameSprite background;
		Sprites::GameSprite cursor;
		std::wstring bgResource;
		std::wstring crsrResource;
    public:
        GameMenu(ID3D10Device*, wchar_t*);
        ~GameMenu(void);
        int Sprites(Sprites::GameSprite *);
		int HandleDownButton(Sprites::GameSprite *);
		int HandleUpButton(Sprites::GameSprite *);
		int HandleInteractButton(Sprites::GameSprite *);
		Status::code status;
    private:
        void Init(ID3D10Device*);
		void LoadConfig(wchar_t*,ID3D10Device*);
		void GenerateSprite();
		bool LoadMenuFrameConfig(Xml::Node& menuFrame);
    }; // GameMenu
}
/* eof */