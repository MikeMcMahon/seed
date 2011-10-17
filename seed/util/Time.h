#pragma once

namespace GameUtil { 
    class Time { 
    public:
        static float GetMilis() { 
            LARGE_INTEGER t, f;
	        QueryPerformanceCounter(&t);
	        QueryPerformanceFrequency(&f);

	        // Return in Miliseconds
	        return ((float)t.QuadPart / (float)f.QuadPart) * 1000.0f;
        }
    };
}
/* eof */