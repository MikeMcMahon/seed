#pragma once

#include "../main/GameHeaders.h"
#include "../sprites/GameSprite.h"
#include "../util/XmlIngester.h"

namespace Ui { 
    class GameMenu
    {
    private:
        std::vector<Sprites::GameSprite> gameSprites;
        std::vector<ID3D10ShaderResourceView*> textureResourceViews;

    public:
        GameMenu(ID3D10Device*);
        ~GameMenu(void);
        int Sprites(Sprites::GameSprite *); 
    private:
        void Init(ID3D10Device*);
    }; // GameMenu
}
/* eof */