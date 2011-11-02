#include "GameClock.h"

using namespace GameUtil;

LONGLONG cacheTime;

GameClock* GameClock::pInstance = NULL;

GameClock* GameClock::GetInstance ( ) { 
    if (pInstance == NULL) { 
        pInstance = new GameClock();
    }
    return pInstance;
}


GameClock::GameClock(void) {
    this->Initialize ( );
}

void GameClock::GetTime ( LONGLONG * t ) { 
    // Use timeGetTime() if queryperformancecounter is not supported 
    if (!QueryPerformanceCounter( (LARGE_INTEGER *) t)) { 
        *t = timeGetTime();
    }

    cacheTime = *t;
}

LONGLONG GameClock::GetTimeElapsed ( void ) { 
    LONGLONG t; 
    
    // Use timeGetTime() if queryperformancecounter is not supported
    if (!QueryPerformanceCounter( (LARGE_INTEGER *) &t )) { 
        t = timeGetTime();
    }

    return (t - cacheTime);
}

void GameClock::Initialize ( void ) { 
    if ( !QueryPerformanceFrequency((LARGE_INTEGER *) &this->frequency) ) { 
		this->frequency = 1000; // 1000ms to one second 
	}
    this->timeCount = DWORD(this->frequency / TICKS_PER_SECOND);
}

GameClock::~GameClock(void)
{
}
