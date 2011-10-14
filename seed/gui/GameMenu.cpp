#include "GameMenu.h"

#include "../sprites/SpriteUtils.h"
#include "../util/TextureHandler.h"
#include "MenuConstants.h"
#include "../font/GameFonts.h"

using namespace Gui;

// Defaults
const struct Menu MENU_FRAME_DEFUALT = { MenuStyle::unused, Type::background, 0, 0, 0, 0, L"" };
const struct Menu MENU_OPTIONS_DEFAULT = { MenuStyle::relative, Type::cursor, 24, 24, 0, 0, L"" };
const struct MenuChoice MENU_CHOICE_DEFAULT = { SZ_NORMAL, L"", false };
const float buffer = 5;

GameMenu::GameMenu(wchar_t* config)
{
    // TODO - Implement loading of the XML Files
	this->LoadConfig(config);
}


GameMenu::~GameMenu(void)
{
    // Destroy the sprites
    int size = this->menuOpts.size();
    for (int i = 0; i < size; i++) { 
        delete &(this->menuOpts.at(i));
    }
}

/*
 Loads the config specified when this menu was created
*/
void GameMenu::LoadConfig(wchar_t* config) { 
	_bstr_t configFile(config);
	Xml::Document* document = new Xml::Document(configFile);

	// if the document opened fine then lets do this if not whoopsie
	Xml::Status::code docStatus = document->status;
	if (docStatus == Xml::Status::ok) { 
		this->status = Status::ok;
		// Get the root node and it's children 
		Xml::Node rootNode = document->rootNode;

		Xml::Node textureResources = rootNode.find(CONFIG_TEXTURE_RESOURCE_ROOT, NULL, NULL);
		Xml::Node menuFrame = rootNode.find(CONFIG_MENU_FRAME, NULL, NULL);
		if (!this->LoadMenuFrameConfig(menuFrame)) { 
			// Something happened trying to read the MenuFrameConfig.  
			this->status = Status::failed;
			return;
		}
		if (textureResources.status == Xml::Status::ok && menuFrame.status == Xml::Status::ok) {
			// Handle the texture resources 
			long nodeCount = textureResources.child.count;
			if (nodeCount == 0) { this->status = Status::failed; return; }
			
			// TODO - stick to using std::wstring from wchar_t* and _bstr_t when possible, they create pointers we don't want to use in this context! 
			std::wstring name = L"";
			std::wstring image = L"";
			int height = 0;
			int width = 0;
			int x = 0;
			int y = 0;
			std::wstring textureDir = L"../textures/";
			std::wstring texture = L"";
			Sprites::GameSprite sprite;
			for (long i = 0; i < nodeCount; i++) { 
				name = textureResources.child[i].attribute[CONFIG_TEXTURE_RESOURCE_NAME].bstr;

				// Create a sprite from this information
				// Get the texture resource
				image = textureResources.child[i].attribute[CONFIG_TEXTURE_RESOURCE_IMAGE].bstr;
				texture.append(textureDir);
				texture.append(image);

				// TODO - Implement BOOST String Algs to compare the strings
				// Handle the menu frame sprite
				if (name.compare(this->menuFrame.resource) == 0) {
					this->GenerateSprite(this->menuFrame, texture.c_str());

				}
				
				// handle the menu options
				if (name.compare(this->menuOptions.resource) == 0) {
					// Offset the cursor to the left by 5 px padding + width of the cursor 
					this->menuOptions.x -= (this->menuOptions.width + 5.0f);
					this->GenerateSprite(this->menuOptions, texture.c_str());
				}

				// Cleanup the texture string
				texture = L"";
				this->status = Status::ok;
			}
			// Handle the menu options
			int size = this->menuChoices.size();
			RECT rc; 

			// Create a new font instance
			// ID3DX10Font* pFont = NULL;
			x = this->menuOptions.x;
			y = this->menuOptions.y;
			for (int i = 0; i < size; i++) { 
				SetRectEmpty(&rc);
				//FontRect(pFont, NULL, &rc, x, y, this->menuChoices[i].value);

				// Calculate the x/y for the next sprite, buffer of 5px
				y += buffer + (rc.top - rc.bottom);
			}
			// Cleanup
			//if (pFont) { 
			//	pFont->Release();
			//}
		} else { 
			// Invalid config file...duh
			this->status = Status::failed;
		}
	} else {
		// Probably something stupid happened
		this->status = Status::failed;
	}

	// Cleanup
	document = NULL;
	delete document;
} // LoadConfig

void Gui::GameMenu::GenerateSprite(Gui::Menu menuPresets, const wchar_t* texture) { 
	Sprites::GameSprite sprite(texture, menuPresets.resource,(float)menuPresets.width, (float)menuPresets.height);
	sprite.animationDetail(0,0,0);
	sprite.sprite.canAnimate = (false);
	sprite.sprite.isVisible = (true);
	sprite.sprite.canMove = (false);
	sprite.sprite.position.x = menuPresets.x;
	sprite.sprite.position.y = menuPresets.y;
	sprite.sprite.moveDistance.up = 0;
	sprite.sprite.moveDistance.down= 0;
	sprite.sprite.moveDistance.left = 0;
	sprite.sprite.moveDistance.right = 0;

	if (menuPresets.type == Type::background) 
		this->background = sprite;
	if (menuPresets.type == Type::cursor)
		this->cursor = sprite;
} // GenerateSprite


bool Gui::GameMenu::LoadMenuFrameConfig(Xml::Node& menuFrameNode) { 
	// Create default structs
	this->menuFrame = MENU_FRAME_DEFUALT;
	this->menuOptions = MENU_OPTIONS_DEFAULT;

	this->menuFrame.x = (menuFrameNode.attribute[CONFIG_POS_X].exists) ? menuFrameNode.attribute[CONFIG_POS_X] : 0;
	this->menuFrame.y = (menuFrameNode.attribute[CONFIG_POS_X].exists) ? menuFrameNode.attribute[CONFIG_POS_Y] : 0;
	this->menuFrame.width = (menuFrameNode.attribute[CONFIG_WIDTH].isNumeric) ? menuFrameNode.attribute[CONFIG_WIDTH] : WINDOW_WIDTH;
	this->menuFrame.height = (menuFrameNode.attribute[CONFIG_HEIGHT].isNumeric) ? menuFrameNode.attribute[CONFIG_HEIGHT] : WINDOW_HEIGHT;
	wchar_t* tmp = (menuFrameNode.attribute[CONFIG_MENU_FRAME_TEXTURE_RESOURCE].exists) ? (menuFrameNode.attribute[CONFIG_MENU_FRAME_TEXTURE_RESOURCE].x_getBstr()) : L"";
	wcscpy_s(this->menuFrame.resource, tmp);

	// Get all of the menu choices
	Xml::Node options = menuFrameNode.child[CONFIG_MENU_OPTIONS];
	wchar_t* name = options.name;
	
	// Handle the cursor
	tmp = (options.attribute[CONFIG_MENU_OPTION_CURSOR].exists) ? (options.attribute[CONFIG_MENU_OPTION_CURSOR].bstr) : L"";
	wcscpy_s(this->menuOptions.resource, tmp);
	this->menuOptions.x = (options.attribute[CONFIG_POS_X].exists) ? (options.attribute[CONFIG_POS_X]) : 0;
	this->menuOptions.y = (options.attribute[CONFIG_POS_Y].exists) ? (options.attribute[CONFIG_POS_Y]) : 0;
	int fontHeight = options.attribute["font-height"].exists ? options.attribute["font-height"] : 20;

	long count = options.child.count;
	MenuChoice choice = MENU_CHOICE_DEFAULT;
	for (long i = 0; i < count; i++) { 
		choice.height = fontHeight;
		choice.isDefault = options.child[i].attribute["default"];
		choice.value = options.child[i].attribute["value"].bstr;
		this->menuChoices.push_back(choice);
	}

	return true;
} // LoadMenuFrameConfig

/*
 Returns the number of sprites to draw
 sprites is the sprite array you wish to have filled with sprites
*/
int GameMenu::Sprites(Sprites::GameSprite* sprites) { 
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