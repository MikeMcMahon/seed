#include "StartMenu.h"

#include "../sprites/SpriteUtils.h"
#include "../util/TextureHandler.h"
#include "MenuConstants.h"
#include "../font/GameFonts.h"

using namespace Gui;

const float padding = 5;

StartMenu::StartMenu(void)
{
	this->background = Sprites::GameSprite(
		L"../textures/main-menu-1024x768.png", 
		L"background",
		(float)WINDOW_WIDTH, 
		(float)WINDOW_HEIGHT
		);
	this->background.sprite.canAnimate = false;
	this->background.sprite.isVisible = true;
	this->background.sprite.canMove = false;

	this->cursor = Sprites::GameSprite(
		L"../textures/cursor.png", 
		L"cursor",
		24.0f, 
		24.0f
		);
	this->cursor.sprite.canAnimate = false;
	this->cursor.sprite.isVisible = true;
	this->cursor.sprite.canMove = false;
	this->cursor.sprite.position.x = 441;
	this->cursor.sprite.position.y = 336;

	// Create the text sprites

}


StartMenu::~StartMenu(void)
{
    // Destroy the sprites
    int size = this->menuOpts.size();
    for (int i = 0; i < size; i++) { 
        delete &(this->menuOpts.at(i));
    }
}


/*
 Returns the number of sprites to draw
 sprites is the sprite array you wish to have filled with sprites
*/
int StartMenu::Sprites(Sprites::GameSprite* sprites) { 
	// Assign the sprites in order 
	// Background
	// Cursor
	*sprites++ = this->background;
	*sprites++ = this->cursor;

	int size = this->menuOpts.size();
    for (int i = 0; i < size; i++) {
        *sprites++ = (this->menuOpts.at(i));
    }
		
    // Return the size
    return size += 2;
	return 0;
}

/* eof */