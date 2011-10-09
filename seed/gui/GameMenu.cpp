#include "GameMenu.h"
#include <XmlHelper.h>
#include "../sprites/SpriteUtils.h"
#include "../util/TextureHandler.h"
#include "MenuConstants.h"

using namespace Gui;

GameMenu::GameMenu(ID3D10Device* pD3DDevice, wchar_t* config)
{
    // Util::XmlIngester xmlIngester;
    // xmlIngester.Load(L"../Gui/GameMenu.xml");

    // TODO - Implement loading of the XML Files
	this->LoadConfig(config);
    this->Init(pD3DDevice);
}


GameMenu::~GameMenu(void)
{
    // Destroy our sprites and other things
    int size = this->textureResourceViews.size();
    for (int i = 0; i < size; i++) { 
        // Release the resource
        this->textureResourceViews.at(i)->Release();
    }

    // Destroy the sprites
    size = this->gameSprites.size();
    for (int i = 0; i < size; i++) { 
        delete &(this->gameSprites.at(i));
    }
}

/*
 Loads the config specified when this menu was created
*/
void GameMenu::LoadConfig(wchar_t* config) { 
	_bstr_t configFile(config);
	Xml::Document document(configFile);

	// if the document opened fine then lets do this if not whoopsie
	Xml::Status::code docStatus = document.status;
	if (docStatus == Xml::Status::ok) { 
		this->status = Status::ok;

		_bstr_t root = document.rootNode.name;
		if (wcscmp(root,CONFIG_MENU_ROOT) == 0) { 
			// Get the root node and it's children 
			Xml::Node rootNode = document.rootNode;

			Xml::Node textureResources = rootNode.find(CONFIG_TEXTURE_RESOURCE_ROOT, NULL, NULL);
			Xml::Node menuFrame = rootNode.find(CONFIG_MENU_FRAME, NULL, NULL);
			
			if (textureResources.status == Xml::Status::ok && menuFrame.status == Xml::Status::ok) {

				// Handle the texture resources 
				long nodeCount = textureResources.child.count;
				if (nodeCount == 0) { this->status = Status::failed; return; }
				for (long i = 0; i < nodeCount; i++) { 
					_bstr_t name = textureResources.child[i].attribute["name"];
					_bstr_t image = textureResources.child[i].attribute["image"];

					// Check the height width they can be strings or nbrs
					int height = 0;
					int width = 0; 
					height = (textureResources.child[i].attribute["height"].isNumeric) ? textureResources.child[i].attribute["height"] : -1;
					width = (textureResources.child[i].attribute["width"].isNumeric) ? textureResources.child[i].attribute["width"] : -1;

					int y = textureResources.child[i].attribute["x"];
					int x = textureResources.child[i].attribute["y"];
					// Create a sprite from this information
				}

				// Handle the menu frame
				nodeCount = menuFrame.child.count;
				if (nodeCount == 0) { this->status = Status::failed; return; }
			} else { 
				// Required nodes missing
				this->status = Status::failed;
			}
		} else { 
			// Invalid config file...duh
			this->status = Status::failed;
		}
	} else {
		// Probably something stupid happened
		this->status = Status::failed;
	}
}

/*
 Returns the number of sprites to draw
 sprites is the sprite array you wish to have filled with sprites
*/
int GameMenu::Sprites(Sprites::GameSprite *sprites) { 
    Sprites::GameSprite nSprites[MAX_SPRITES];
    
    // Should assign the sprites we've created
    int size = this->gameSprites.size();
    for (int i = 0; i < size; i++) {
        *sprites++ = (this->gameSprites.at(i));
    }

    // Assign the new sprites

    // Return the size
    return this->gameSprites.size();
}


void GameMenu::Init(ID3D10Device* pD3DDevice) {
    Sprites::GameSprite background;
    Sprites::GameSprite aButton; 
    
    // Load the texture resources for them
    ID3D10Texture2D* bgTexture = GameUtil::TextureHandler::GetTexture2DFromFile("../textures/main-menu-1024x768.png", pD3DDevice);
    ID3D10Texture2D* btnTexture = GameUtil::TextureHandler::GetTexture2DFromFile("../textures/a-button-32x32.png", pD3DDevice); 

    // Test the textures
    if (!(bgTexture && btnTexture))
        return;

    // Resource View
    ID3D10ShaderResourceView * bgRscView;
    ID3D10ShaderResourceView * btnRscView;
	GameUtil::TextureHandler::GetResourceViewFromTexture(bgTexture, &bgRscView, pD3DDevice);
    GameUtil::TextureHandler::GetResourceViewFromTexture(btnTexture, &btnRscView, pD3DDevice);

    // Save
    this->textureResourceViews.push_back(bgRscView);
    this->textureResourceViews.push_back(btnRscView);

    // Release the textures
    bgTexture->Release();
    btnTexture->Release();

    // Create the sprites
    Sprites::GameSprite backgroundSprite;
    Sprites::GameSprite aButtonSprite;

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
	backgroundSprite.isVisible(TRUE);
	backgroundSprite.canAnimate(FALSE);
	backgroundSprite.canMove(FALSE);
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
	aButtonSprite.isVisible(TRUE);
	aButtonSprite.canAnimate(FALSE);
	aButtonSprite.canMove(TRUE);
    aButtonSprite.spriteSize(24,24);
    aButtonSprite.setMoveDistance(1,1);

    // add the sprites
    this->gameSprites.push_back(backgroundSprite);
	this->gameSprites.push_back(aButtonSprite);
} // Init
/* eof */