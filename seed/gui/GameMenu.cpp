#include "GameMenu.h"

#include "../sprites/SpriteUtils.h"
#include "../util/TextureHandler.h"
#include "MenuConstants.h"

using namespace Gui;

// Defaults
const struct MenuFrame MENU_FRAME_DEFUALT = { 0, 0, 0, 0, L"" };
const struct MenuOptions MENU_OPTIONS_DEFAULT = { MenuStyle::absolute, 24, 24, 0, 0, L"" };
const struct MenuChoice MENU_CHOICE_DEFAULT = { L"", false };

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
	Xml::Document document(configFile);

	// if the document opened fine then lets do this if not whoopsie
	Xml::Status::code docStatus = document.status;
	if (docStatus == Xml::Status::ok) { 
		this->status = Status::ok;
		// Get the root node and it's children 
		Xml::Node rootNode = document.rootNode;

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
				image = textureResources.child[i].attribute[CONFIG_TEXTURE_RESOURCE_IMAGE].bstr;

				// Check the height width they can be strings or nbrs
				height = (textureResources.child[i].attribute[CONFIG_HEIGHT].isNumeric) ? textureResources.child[i].attribute[CONFIG_HEIGHT] : WINDOW_HEIGHT;
				width = (textureResources.child[i].attribute[CONFIG_WIDTH].isNumeric) ? textureResources.child[i].attribute[CONFIG_WIDTH] : WINDOW_WIDTH;
				y = textureResources.child[i].attribute[CONFIG_POS_Y];
				x = textureResources.child[i].attribute[CONFIG_POS_X];

				// Create a sprite from this information
				// Get the texture resource
				texture.append(textureDir);
				texture.append(image);
				// sprite = new Sprites::GameSprite(texture.c_str(),name.c_str(),(float)width,(float)height, pD3DDevice);
				sprite.Name(name);
				sprite.Texture(texture.c_str(), pD3DDevice);
				sprite.spriteSize((float)width, (float)height);
				sprite.animationDetail(0,0,0);
				sprite.canAnimate(false);
				sprite.isVisible(true);
				sprite.canMove(false);
				sprite.position((float)x,(float)y,0.5f);
				sprite.setMoveDistance(0,0);
				sprite.TexCoord.x = 0;
				sprite.TexCoord.y = 0;
				sprite.TexSize.x = 1.0f;
				sprite.TexSize.y = 1.0f;
				sprite.TextureIndex = 0;
				sprite.ColorModulate = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
				
				this->menuOpts.push_back(sprite);
				texture = L"";
				this->status = Status::ok;
			}
			name = L"This is a test";
			texture = L"this is another test";
			// Handle the menu frame
			nodeCount = menuFrame.child.count;
			if (nodeCount == 0) { this->status = Status::failed; return; }
		} else { 
			// Invalid config file...duh
			this->status = Status::failed;
		}
	} else {
		// Probably something stupid happened
		this->status = Status::failed;
	}

	// Cleanup
	delete &document;
} // LoadConfig

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
	this->menuOptions.cursor = (options.attribute[CONFIG_MENU_OPTION_CURSOR].exists) ? (options.attribute[CONFIG_MENU_OPTION_CURSOR].bstr) : L"";

	long count = options.child.count;
	MenuChoice choice = MENU_CHOICE_DEFAULT;
	for (long i = 0; i < count; i++) { 
		choice.isDefault = options.child[i].attribute["default"];
		choice.value = options.child[i].attribute["value"].bstr;
		this->menuChoices.push_back(choice);
	}

	// Do our magic here


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
	// Text Options
	// Cursor

    // Should assign the sprites we've created
    int size = this->menuOpts.size();
    for (int i = 0; i < size; i++) {
        *sprites++ = (this->menuOpts.at(i));
    }

    // Assign the new sprites

    // Return the size
    return this->menuOpts.size();
}


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