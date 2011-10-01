#ifndef __BUILDINGSPRITE_H_INCLUDE__
#define __BUILDINGSPRITE_H_INCLUDE__

#include "GameSprite.h"

struct BuildingSprite : public GameSprite {
	BuildingSprite();
	float  doorLocation[4];
};

#endif