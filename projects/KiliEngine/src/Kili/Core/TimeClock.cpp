#include "klpch.h"
#include "TimeClock.h"

#include "Kili/Core/Logger/Log.h"

Uint64 Kili::TimeClock::mFrameStart = 0;
        
Uint64 Kili::TimeClock::mFrameTime = 0;
Uint64 Kili::TimeClock::mLastFrameStart = 0;

Uint64 Kili::TimeClock::mSdlFrequency = 0;
Uint32 Kili::TimeClock::mMaxFps = 0;
Uint64 Kili::TimeClock::mTicksPerFrame = 0;
 
Uint64 Kili::TimeClock::mTime = 0;
Uint32 Kili::TimeClock::mFrameCount = 0;
 
float Kili::TimeClock::mMaxDeltaTime = 0.0f;
float Kili::TimeClock::mDeltaTime = 0.0f;
 
bool Kili::TimeClock::mLogging = false;
float Kili::TimeClock::mLogInterval = 0.0f;
double Kili::TimeClock::mLastLog = 0.0f;

void Kili::TimeClock::init(const unsigned int maxFps, const float maxDeltaTime)
{
    mSdlFrequency = SDL_GetPerformanceFrequency();
    mMaxFps = maxFps;
    mMaxDeltaTime = maxDeltaTime;
    mLastFrameStart = SDL_GetPerformanceCounter();
    mFrameStart = mLastFrameStart;
    if (mMaxFps) mTicksPerFrame = mSdlFrequency / mMaxFps;
}

void Kili::TimeClock::computeTime()
{
    // Set frame timers.
    mFrameStart = SDL_GetPerformanceCounter();
    mFrameTime = mFrameStart - mLastFrameStart;
    mLastFrameStart = mFrameStart;
    
    // Compute Delta time.
    mDeltaTime = Klm::Min(static_cast<float>(mFrameTime) / static_cast<float>(mSdlFrequency), mMaxDeltaTime);
    
    // Update time and frame count.
    mTime += mFrameTime;
    mFrameCount++;
    
    // LogFps if needed
    if (mLogging)
    {
        if (time() > mLastLog + mLogInterval)
        {
            LOG_INFO("Avg : " + std::to_string(1 / avgFrameTime()) + " | Current : " + std::to_string(1 / deltaTime()) + " | FrameTime : " + std::to_string(deltaTime() * 1000));
            mLastLog = time();
        }
    }
}

void Kili::TimeClock::delayTime()
{
    if (mMaxFps == 0) return;

    if (const unsigned long long elapsed = SDL_GetPerformanceCounter() - mFrameStart; elapsed < mTicksPerFrame)
    {
        SDL_DelayPrecise((mTicksPerFrame - elapsed) * 1000000000 / mSdlFrequency);
        // How many ticks remaining for this frame 
        // times 1,000,000,000 for conversion from t/s to t/ns
        // divided by Sdl frequency to convert from t/ns to ns.
    }
}