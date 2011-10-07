#pragma once
#include "GameSprite.h"

namespace Sprites { 
	struct MapSprite : public GameSprite {
		MapSprite();
		std::vector<std::vector<float>> * deadZones;		// Areas of the map we cannot traverse. 
	}; // MapSprite
} // Sprites
/* eof */