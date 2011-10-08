#pragma once

#include "../main/GameHeaders.h"
#include "../sprites/GameSprite.h"
#include "../util/XmlIngester.h"

namespace Gui { 
    class GameMainMenu
    {
    private:
        std::vector<Sprites::GameSprite> gameSprites;
        std::vector<ID3D10ShaderResourceView*> textureResourceViews;

    public:
        GameMainMenu(ID3D10Device*);
        ~GameMainMenu(void);
        int Sprites(Sprites::GameSprite *); 
    private:
        void Init(ID3D10Device*);
    }; // GameMenu
}
/* eof */