#ifndef __MAPSPRITE_H_INCLUDE__
#define __MAPSPRITE_H_INCLUDE__

#include "GameSprite.h"

namespace sprites { 
	struct MapSprite : public GameSprite {
		MapSprite();
		std::vector<std::vector<float>> * deadZones;		// Areas of the map we cannot traverse. 
	};
}

#endif