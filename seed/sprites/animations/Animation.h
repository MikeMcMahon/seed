#pragma once

#include "..\base\Position.h"

namespace Sprites { 
    struct Animation { 
        float duration; 
        int totalFrames;
        Position positionInSpriteSheet;
    };
}