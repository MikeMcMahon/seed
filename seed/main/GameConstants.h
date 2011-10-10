#pragma once

// Balls to the walls SON!
#define WIN32_LEAN_AND_MEAN

// Required for rendering stuff on time
const int TICKS_PER_SECOND = 60;
const float SKIP_TICKS = 1000.0f / (float)TICKS_PER_SECOND;
const int MAX_FRAMESKIP = 5;

#define WINDOW_WIDTH 1024
#define WINDOW_HEIGHT 768
#define CLASS_NAME LPCWSTR("SEED")

#if _DEBUG
    #define DIRECTORY_PREFIX "../"
#else 
    #define DIRECTORY_PREFIX "./"
#endif