#pragma once

namespace GameUtil { 
    class GameClock
    {
    public:
        static GameClock* GetInstance();
        void Initialize ( void );
        DWORD timeCount;

        void GetTime ( LONGLONG* t );
        LONGLONG GetTimeElapsed ( void );

        ~GameClock(void);
    protected:
        GameClock(void);

    private:
        static GameClock* pInstance;
    }; // GameClock
}