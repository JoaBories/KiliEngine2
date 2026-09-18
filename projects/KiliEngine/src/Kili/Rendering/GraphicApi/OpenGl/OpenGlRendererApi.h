#pragma once
#include "Kili/Rendering/RHI/RendererApi.h"

namespace Kili
{
    class OpenGlRendererApi : public RendererApi
    {
    public:
        void clear(const Vector4& clearColor) override;
        
        void draw(const std::shared_ptr<VertexArray>& vertexArray) override;
        void drawIndexed(const std::shared_ptr<VertexArray>& vertexArray) override;
        
        void setVsync(const bool enabled) override { SDL_GL_SetSwapInterval(enabled); }
        [[nodiscard]] bool isVsync() const override { int interval; SDL_GL_GetSwapInterval(&interval); return interval;  }
        
        void setMsaa(int samples) const override;
        
        [[nodiscard]] int getWindowFlag() const override { return SDL_WINDOW_OPENGL; }
    };
}