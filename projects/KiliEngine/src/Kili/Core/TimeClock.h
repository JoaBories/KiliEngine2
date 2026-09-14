#pragma once

// Apparently the app is locked at 5 millions fps with unlimited fps. I don't if it comes from windows, Sdl3, or my code.
// Not a big problem as it is quite hard to reach with actual code in the loop, I reached 5m with only polling Sdl3 events.

namespace Kili
{
    class TimeClock
    {
        friend class Engine; // So only Engine can access Clocking methods

    private:
        static Uint64 mFrameStart; /* Tick from Sdl clock */
        
        static Uint64 mFrameTime;
        static Uint64 mLastFrameStart;
        
        static Uint64 mSdlFrequency; /* From Sdl clock frequency. Usually return 10,000,000 on Windows so 10 tick is 1 micro seconds. */
        static Uint32 mMaxFps;
        static Uint64 mTicksPerFrame; /* Number of tick for each frame to pass. Only used if fps are capped and vsync off. */
        
        static Uint64 mTime; /* Time elapsed since app start. */
        static Uint32 mFrameCount; /* Number of frame since app start */
        
        static float mMaxDeltaTime;
        static float mDeltaTime;
        
        static bool mLogging;
        static float mLogInterval;
        static double mLastLog;

        static void init(unsigned int maxFps = 60, float maxDeltaTime = 1.0f);

        static void computeTime();
        static void delayTime();
        
    public:
        // Rule of zero
        TimeClock(const TimeClock&) = delete;
        TimeClock& operator=(const TimeClock&) = delete;
        TimeClock(TimeClock&& pOther) noexcept = delete;
        TimeClock& operator=(TimeClock&& pOther) noexcept = delete;
        
        [[nodiscard]] static Uint32 getMaxFps() { return mMaxFps; }
        static void setMaxFps(const Uint32 maxFps) { mMaxFps = maxFps; }
        
        [[nodiscard]] static float getMaxDeltaTime() { return mMaxDeltaTime; }
        static void setMaxDeltaTime(const float maxDeltaTime) { mMaxDeltaTime = maxDeltaTime; }

        [[nodiscard]] static bool getLogging() { return mLogging; }
        static void setLogging(const bool logging) { mLogging = logging; }

        [[nodiscard]] static float getLoggingInterval() { return mLogInterval; }
        static void setLoggingInterval(const float interval) { mLogInterval = interval; }
        
        static double time() { return static_cast<double>(mTime) / static_cast<double>(mSdlFrequency); } /* Return elapsed since app start */
        static Uint32 frameCount() { return mFrameCount; } /* Return frame count since app start */
        static float deltaTime() { return mDeltaTime; } /* Delta time in second */
        
        static float avgFrameTime() { return static_cast<float>(mTime) / static_cast<float>(mSdlFrequency) / static_cast<float>(mFrameCount); } /* Average frame time in second */
    };
}