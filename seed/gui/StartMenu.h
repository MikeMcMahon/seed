#pragma once

#define RESOURCE_BUFFER 200

#include "../sprites/GameSprite.h"
#include "../sprites/FontSprite.h"

namespace Gui { 

	struct MenuStyle { enum style {
		absolute,
		relative,
		unused};};
	struct Type { enum type { 
		background,
		cursor
		};};
   class StartMenu
    {
    private:
        std::vector<Sprites::FontSprite> menuOpts;
		Sprites::GameSprite background;
		Sprites::GameSprite cursor;
		int menuChoiceHeight;
    public:
        StartMenu(void);
        ~StartMenu(void);
        int Sprites(Sprites::GameSprite *);
		int HandleDownButton(Sprites::GameSprite *);
		int HandleUpButton(Sprites::GameSprite *);
		int HandleInteractButton(Sprites::GameSprite *);
    }; // StartMenu
}
/* eof */