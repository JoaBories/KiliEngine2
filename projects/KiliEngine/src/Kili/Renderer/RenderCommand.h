#pragma once

#include "Kili/Renderer/RHI/RendererApi.h"

namespace Kili
{
    class RenderCommand
    {
    private:
        static RendererApi* mApi;
        
    public:
        inline static void drawIndexed(const std::shared_ptr<VertexArray>& vertexArray)
        {
            mApi->drawIndexed(vertexArray);
        }
        
        inline static void clear(const Vector4& clearColor)
        {
            mApi->clear(clearColor);
        }
    };
}
