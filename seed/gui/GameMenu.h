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
		std::wstring resource;
	};
	struct MenuOptions {
		MenuStyle::style display;
		float height;
		float width;
		float x;
		float y;
		std::wstring cursor;
	};
	struct MenuChoice { 
		std::wstring value;
		bool isDefault;
	};
    class GameMenu
    {
    private:
		MenuFrame menuFrame;
		MenuOptions menuOptions;
		std::vector<MenuChoice> menuChoices;
        std::vector<Sprites::GameSprite> menuOpts;
		Sprites::GameSprite background;
		Sprites::GameSprite cursor;
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