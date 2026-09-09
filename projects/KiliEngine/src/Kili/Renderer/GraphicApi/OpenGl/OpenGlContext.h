#pragma once
#include "Kili/Renderer/GraphicContext.h"

namespace Kili
{
    class OpenGlContext : public GraphicContext
    {
    private:
        SDL_Window* mWindowHandle;
        SDL_GLContext mContext;
        
    public:
        OpenGlContext(SDL_Window* windowHandle);
        
        void init() override;
        void close() override;
        
        void swapBuffers() override { SDL_GL_SwapWindow(mWindowHandle); }
        
        void setVsync(const bool enabled) override { SDL_GL_SetSwapInterval(enabled); }
        [[nodiscard]] bool isVsync() const override { int interval; SDL_GL_GetSwapInterval(&interval); return interval;  }
    };
}
