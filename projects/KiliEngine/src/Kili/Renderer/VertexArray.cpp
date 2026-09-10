#include "klpch.h"
#include "VertexArray.h"

#include "Kili/Renderer/Renderer.h"
#include "Kili/Renderer/GraphicApi/OpenGl/OpenGlVertexArray.h"

#include "Kili/Core/Logger/Log.h"

Kili::VertexBuffer* Kili::VertexBuffer::create(const float* vertices, const long size)
{
    switch (Renderer::getApi())
    {
        case GraphicApi::OpenGl : return new OpenGlVertexBuffer(vertices, size); break;
        case GraphicApi::None: return nullptr; break;
    }
    
    LOG_WARNING("Unknown GraphicApi : " + Renderer::getApiName());
    return nullptr;
}
Kili::IndexBuffer* Kili::IndexBuffer::create(const unsigned long* indices, const unsigned long count)
{
    switch (Renderer::getApi())
    {
        case GraphicApi::OpenGl : return new OpenGlIndexBuffer(indices, count); break;
        case GraphicApi::None: return nullptr; break;
    }
    
    LOG_WARNING("Unknown GraphicApi : " + Renderer::getApiName());
    return nullptr;
}