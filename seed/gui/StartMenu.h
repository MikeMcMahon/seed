#pragma once

#define RESOURCE_BUFFER 200

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
		Sprites::GameSprite background;
		Sprites::GameSprite cursor;
		std::vector<Sprites::GameSprite> menuOpts; 
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