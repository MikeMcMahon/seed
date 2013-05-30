#pragma once

namespace Timers { 
    class SWGameClock
    {
    public:
        static SWGameClock* GetInstance();
        void Initialize ( void );
        DWORD timeCount;

        void GetTime ( LONGLONG* t );
        LONGLONG GetTimeElapsed ( void );
        LONGLONG frequency; 

        ~SWGameClock(void);
    protected:
        SWGameClock(void);

    private:
        static SWGameClock* pInstance;
    }; // SWGameClock
} // Timers