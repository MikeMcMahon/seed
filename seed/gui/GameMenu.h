#pragma once

#define RESOURCE_BUFFER 200

#include "../sprites/GameSprite.h"

namespace Gui { 

	struct Status { enum code { 
		ok,
		failed };};
	struct MenuStyle { enum style {
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
		wchar_t resource[RESOURCE_BUFFER];
	};
	struct MenuChoice {
		float height;
		wchar_t* value;
		bool isDefault;
	};
    class GameMenu
    {
    private:
		Menu menuFrame;
		Menu menuOptions;
		std::vector<MenuChoice> menuChoices;
        std::vector<Sprites::GameSprite> menuOpts;
		Sprites::GameSprite background;
		Sprites::GameSprite cursor;
		int menuChoiceHeight;
    public:
        GameMenu(wchar_t*);
        ~GameMenu(void);
        int Sprites(Sprites::GameSprite *);
		int HandleDownButton(Sprites::GameSprite *);
		int HandleUpButton(Sprites::GameSprite *);
		int HandleInteractButton(Sprites::GameSprite *);
		Status::code status;
    private:
        void Init();
		void LoadConfig(wchar_t*);
		bool LoadMenuFrameConfig(Xml::Node& menuFrame);
		void GenerateSprite(Menu menuOptions, const wchar_t* texture); 
		void GenerateFontSprite(MenuChoice menuChoice, const wchar_t* text); // TODO - Implement the fontsprite impl. 
    }; // GameMenu
}
/* eof */