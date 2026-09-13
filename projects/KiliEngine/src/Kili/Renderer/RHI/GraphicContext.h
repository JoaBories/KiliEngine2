#pragma once

#include "SDL.h"

namespace Kili
{
    class GraphicContext
    {
    public:
        virtual ~GraphicContext() = default;
        
        virtual void init() = 0;
        virtual void close() = 0;
        virtual void swapBuffers() = 0;
        
        virtual void setVsync(bool enabled) = 0;
        [[nodiscard]] virtual bool isVsync() const = 0;
        
        static void setMsaa(int samples);
        
        static int getWindowFlag();
        static GraphicContext* create(SDL_Window* windowHandle);
    };
}