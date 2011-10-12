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
const float _buffer = 5;

GameMenu::GameMenu(ID3D10Device* pD3DDevice, wchar_t* config)
{
    // TODO - Implement loading of the XML Files
	this->LoadConfig(config, pD3DDevice);
	// this->Init(pD3DDevice);
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
void GameMenu::LoadConfig(wchar_t* config, ID3D10Device* pD3DDevice) { 
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

				// Handle the menu frame sprite
				if (this->menuFrame.resource.compare(name) == 0) {
					this->GenerateSprite(this->menuFrame, texture.c_str(), *pD3DDevice);

				}
				
				// handle the menu options
				if (this->menuOptions.resource.compare(name) == 0) {
					// Offset the cursor to the left by 5 px padding + width of the cursor 
					this->menuOptions.x -= (this->menuOptions.width + 5.0f);
					this->GenerateSprite(this->menuOptions, texture.c_str(), *pD3DDevice);
				}

				// Cleanup the texture string
				texture = L"";
				this->status = Status::ok;
			}
			// Handle the menu options
			int size = this->menuChoices.size();
			RECT rc; 

			// Create a new font instance
			ID3DX10Font* pFont;
			x = this->menuOptions.x;
			y = this->menuOptions.y;
			InitFont(pD3DDevice, &pFont, this->menuChoices.at(0).height, 0, FW_NORMAL, ARIAL);
			for (int i = 0; i < size; i++) { 
				SetRectEmpty(&rc);
				FontRect(pFont, NULL, &rc, x, y, this->menuChoices[i].value.c_str());

				// Calculate the x/y for the next sprite, buffer of 5px
				y += _buffer + (rc.top - rc.bottom);
			}
			// Cleanup
			pFont->Release();
		} else { 
			// Invalid config file...duh
			this->status = Status::failed;
		}
	} else {
		// Probably something stupid happened
		this->status = Status::failed;
	}

	// Cleanup
	pD3DDevice->Release();
	delete document;
} // LoadConfig

void Gui::GameMenu::GenerateSprite(Gui::Menu menuPresets, const wchar_t* texture, ID3D10Device& pD3DDevice) { 
	Sprites::GameSprite* sprite = new Sprites::GameSprite();
	sprite->Name(menuPresets.resource);
	sprite->Texture(texture, &pD3DDevice);
	sprite->spriteSize((float)menuPresets.width, (float)menuPresets.height);
	sprite->animationDetail(0,0,0);
	sprite->canAnimate(false);
	sprite->isVisible(true);
	sprite->canMove(false);
	sprite->position((float)menuPresets.x,(float)menuPresets.y,0.5f);
	sprite->setMoveDistance(0,0);
	sprite->TexCoord.x = 0;
	sprite->TexCoord.y = 0;
	sprite->TexSize.x = 1.0f;
	sprite->TexSize.y = 1.0f;
	sprite->TextureIndex = 0;
	sprite->ColorModulate = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

	if (menuPresets.type == Type::background) 
		this->background = sprite;
	if (menuPresets.type == Type::cursor)
		this->cursor = sprite;

	ZeroMemory(&menuPresets, sizeof(menuPresets));
	pD3DDevice.Release();
} // GenerateSprite


bool Gui::GameMenu::LoadMenuFrameConfig(Xml::Node& menuFrameNode) { 
	// Create default structs
	this->menuFrame = MENU_FRAME_DEFUALT;
	this->menuOptions = MENU_OPTIONS_DEFAULT;

	this->menuFrame.x = (menuFrameNode.attribute[CONFIG_POS_X].exists) ? menuFrameNode.attribute[CONFIG_POS_X] : 0;
	this->menuFrame.y = (menuFrameNode.attribute[CONFIG_POS_X].exists) ? menuFrameNode.attribute[CONFIG_POS_Y] : 0;
	this->menuFrame.width = (menuFrameNode.attribute[CONFIG_WIDTH].isNumeric) ? menuFrameNode.attribute[CONFIG_WIDTH] : WINDOW_WIDTH;
	this->menuFrame.height = (menuFrameNode.attribute[CONFIG_HEIGHT].isNumeric) ? menuFrameNode.attribute[CONFIG_HEIGHT] : WINDOW_HEIGHT;
	this->menuFrame.resource = (menuFrameNode.attribute[CONFIG_MENU_FRAME_TEXTURE_RESOURCE].exists) ? (menuFrameNode.attribute[CONFIG_MENU_FRAME_TEXTURE_RESOURCE].bstr) : L"";

	// Get all of the menu choices
	Xml::Node options = menuFrameNode.child[CONFIG_MENU_OPTIONS];
	wchar_t* name = options.name;
	
	// Handle the cursor
	this->menuOptions.resource = (options.attribute[CONFIG_MENU_OPTION_CURSOR].exists) ? (options.attribute[CONFIG_MENU_OPTION_CURSOR].bstr) : L"";
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
int GameMenu::Sprites(Sprites::GameSprite *sprites) { 
    Sprites::GameSprite nSprites[MAX_SPRITES];

	// Assign the sprites in order 
	// Background
	// Cursor
	*sprites++ = (*this->background);
	*sprites++ = (*this->cursor);

	int size = this->menuOpts.size();
    for (int i = 0; i < size; i++) {
        *sprites++ = (this->menuOpts.at(i));
    }
	
	
    // Return the size
    return size += 2;
	return 0;
}

/*
** Deprecated ** 
Inits a game menu with statically set sprites
*/
void GameMenu::Init(ID3D10Device* pD3DDevice) {
    Sprites::GameSprite background;
    Sprites::GameSprite aButton; 
    
    // Load the texture resources for them
    ID3D10Texture2D* bgTexture = GameUtil::TextureHandler::GetTexture2DFromFile(L"../textures/main-menu-1024x768.png", pD3DDevice);
    ID3D10Texture2D* btnTexture = GameUtil::TextureHandler::GetTexture2DFromFile(L"../textures/a-button-32x32.png", pD3DDevice); 

    // Test the textures
    if (!(bgTexture && btnTexture))
        return;

    // Resource View
    ID3D10ShaderResourceView * bgRscView;
    ID3D10ShaderResourceView * btnRscView;
	GameUtil::TextureHandler::GetResourceViewFromTexture(bgTexture, &bgRscView, pD3DDevice);
    GameUtil::TextureHandler::GetResourceViewFromTexture(btnTexture, &btnRscView, pD3DDevice);

    // Release the textures
    bgTexture->Release();
    btnTexture->Release();

    // Create the sprites
    Sprites::GameSprite backgroundSprite;
    Sprites::GameSprite aButtonSprite;
	wchar_t* foo = L"background";
	backgroundSprite.Name(foo);
    backgroundSprite.curFrame(0);
    backgroundSprite.animationDetail(0,0,0);
    backgroundSprite.pTexture = bgRscView;
    backgroundSprite.TexCoord.x = 0;
    backgroundSprite.TexCoord.y = 0;
    backgroundSprite.TexSize.x = 1.0f;
    backgroundSprite.TexSize.y = 1.0f;
    backgroundSprite.TextureIndex = 0;
    backgroundSprite.ColorModulate = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	backgroundSprite.position(
		0,
		0,
		0.5f);
	backgroundSprite.isVisible(true);
	backgroundSprite.canAnimate(false);
	backgroundSprite.canMove(false);
    backgroundSprite.spriteSize(WINDOW_WIDTH, WINDOW_HEIGHT);

    aButtonSprite.curFrame(0);
    aButtonSprite.animationDetail(0,0,0);
    aButtonSprite.pTexture = btnRscView;
    aButtonSprite.TexCoord.x = 0;
    aButtonSprite.TexCoord.y = 0;
    aButtonSprite.TexSize.x = 1.0f;
    aButtonSprite.TexSize.y = 1.0f;
    aButtonSprite.TextureIndex = 0;
    aButtonSprite.ColorModulate = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	aButtonSprite.position(
		441,
		358,
		0.5f);
	aButtonSprite.isVisible(true);
	aButtonSprite.canAnimate(false);
	aButtonSprite.canMove(true);
    aButtonSprite.spriteSize(24,24);
    aButtonSprite.setMoveDistance(1,1);

    // add the sprites
    this->menuOpts.push_back(backgroundSprite);
	this->menuOpts.push_back(aButtonSprite);
} // Init
/* eof */