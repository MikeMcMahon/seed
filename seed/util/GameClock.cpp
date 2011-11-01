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
    QueryPerformanceCounter( (LARGE_INTEGER *) t);
    cacheTime = *t;
}

LONGLONG GameClock::GetTimeElapsed ( void ) { 
    LONGLONG t; 
    QueryPerformanceCounter( (LARGE_INTEGER *) &t );
    return (t - cacheTime);
}

void GameClock::Initialize ( void ) { 
    LONGLONG perfCnt;
    QueryPerformanceFrequency((LARGE_INTEGER *) &perfCnt);

    this->timeCount = DWORD(perfCnt / TICKS_PER_SECOND);
}

GameClock::~GameClock(void)
{
}
