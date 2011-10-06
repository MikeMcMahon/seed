#ifndef __XMLING_H_INCLUDE__
#define __XMLING_H_INCLUDE__

// TODO - is this the right way of loading sprites?  I don't think so, so I won't spend too much time here. 
// Think speed, is reading the sprites in via XML really the answer?  how much time does it cost...etc
#include <XmlHelper.h>
#include "../GameHeaders.h"
#include "../sprites/CharacterSprite.h"
#include "../sprites/MapSprite.h"
#include "../sprites/TileSprite.h"

namespace Util { 
	class XmlIngester { 
    private: 
        char* _defaultConfig;
    public:
        XmlIngester();
        ~XmlIngester();
        void GetTileSprite(char* spriteName, sprites::TileSprite* sprite);
        void GetMapSprite(char* spriteName, sprites::MapSprite* sprite);
        void GetCharacterSprite(char* spriteName, sprites::CharacterSprite* sprite);
	}
} // Util

#endif
/* eof */