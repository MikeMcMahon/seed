#pragma once

#define MOVE_DIR_U   L"MOVE_DIR_U"
#define MOVE_DIR_UL  L"MOVE_DIR_UL"
#define MOVE_DIR_UR  L"MOVE_DIR_UR"
#define MOVE_DIR_D   L"MOVE_DIR_D"
#define MOVE_DIR_DL  L"MOVE_DIR_DL"
#define MOVE_DIR_DR  L"MOVE_DIR_DR"
#define MOVE_DIR_L   L"MOVE_DIR_L"
#define MOVE_DIR_R   L"MOVE_DIR_R"

#include "SWCoordinates.h"

namespace Sprites { 
	struct Animation { 
		wchar_t description[100];
        float duration; 
        int totalFrames;
        Util::SWCoordinates frameOnePosition;
    };
}