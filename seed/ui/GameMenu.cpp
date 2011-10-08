#include "GameMenu.h"
#include "../util/XmlIngester.h"
#include "../sprites/SpriteUtils.h"
#include "../util/TextureHandler.h"


using namespace Ui;

GameMenu::GameMenu(ID3D10Device* pD3DDevice)
{
    // Util::XmlIngester xmlIngester;
    // xmlIngester.Load(L"../ui/GameMenu.xml");

    // TODO - Implement loading of the XML Files
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
    aButtonSprite.spriteSize(24,24);
    aButtonSprite.setMoveDistance(0,0);

    // add the sprites
    this->gameSprites.push_back(backgroundSprite);
    this->gameSprites.push_back(aButtonSprite);
} // Init
/* eof */