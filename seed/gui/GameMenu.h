#pragma once

#include "../sprites/GameSprite.h"

namespace Gui { 
	struct Status { enum code { 
		ok,
		failed };};
	struct MenuStyle {enum style {
		absolute,
		relative,
		unused};};
	struct Type { enum type { 
		background,
		cursor
		};};
	struct Menu { 
		MenuStyle::style display;
		Type::type type;
		float height;
		float width;
		float x;
		float y;
		std::wstring resource;
	};
	struct MenuChoice { 
		std::wstring value;
		bool isDefault;
	};
    class GameMenu
    {
    private:
		Menu menuFrame;
		Menu menuOptions;
		std::vector<MenuChoice> menuChoices;
        std::vector<Sprites::GameSprite> menuOpts;
		Sprites::GameSprite* background;
		Sprites::GameSprite* cursor;
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
		bool LoadMenuFrameConfig(Xml::Node& menuFrame);
		void GenerateSprite(Menu menuOptions, const wchar_t* texture, ID3D10Device* pD3DDevice); 
    }; // GameMenu
}
/* eof */