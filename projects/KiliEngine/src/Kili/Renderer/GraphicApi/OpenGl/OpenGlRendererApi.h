#pragma once
#include "Kili/Renderer/RHI/RendererApi.h"

namespace Kili
{
    class OpenGlRendererApi : public RendererApi
    {
    public:
        void clear(const Vector4& clearColor) override;
        
        void drawIndexed(const std::shared_ptr<VertexArray>& vertexArray) override;
    };
}