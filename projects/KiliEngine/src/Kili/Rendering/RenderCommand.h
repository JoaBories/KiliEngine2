#pragma once

#include "Kili/Rendering/RHI/RendererApi.h"

namespace Kili
{
    class RenderCommand
    {
    private:
        static RendererApi* mApi;
        
    public:
        inline static GraphicApi getApi() { return RendererApi::getApi(); }
        
        // Draw
        inline static void draw(const std::shared_ptr<VertexArray>& vertexArray) { mApi->draw(vertexArray); }
        inline static void drawIndexed(const std::shared_ptr<VertexArray>& vertexArray) { mApi->drawIndexed(vertexArray); }
        
        // Clear
        inline static void clear(const Vector4& clearColor) { mApi->clear(clearColor); }
        
        // Utils
        inline static void setVsync(const bool enabled) { mApi->setVsync(enabled); }
        [[nodiscard]] inline static bool isVsync() { return mApi->isVsync(); }
        
        inline static void setMsaa(const int samples) { mApi->setMsaa(samples); }

        [[nodiscard]] inline static int getWindowFlag() { return mApi->getWindowFlag(); }
    };
}
