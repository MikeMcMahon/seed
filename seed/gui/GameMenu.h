#pragma once

#include "../main/GameHeaders.h"
#include "../sprites/GameSprite.h"
#include "../util/XmlIngester.h"

namespace Gui { 
	struct Status { enum code { 
		ok,
		failed };};
    class GameMenu
    {
    private:
        std::vector<Sprites::GameSprite> gameSprites;
        std::vector<ID3D10ShaderResourceView*> textureResourceViews;

    public:
        GameMenu(ID3D10Device*, wchar_t*);
        ~GameMenu(void);
        int Sprites(Sprites::GameSprite *);
		int HandleDownButton(Sprites::GameSprite *);
		int HandleUpButton(Sprites::GameSprite *);
		int HandleInteractButton(Sprites::GameSprite *);
		Status::code status;
    private:
        void Init(ID3D10Device*);
		void LoadConfig(wchar_t*);
    }; // GameMenu
}
/* eof */