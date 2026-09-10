#include "klpch.h"
#include "VertexArray.h"

#include "Kili/Renderer/Renderer.h"
#include "Kili/Renderer/GraphicApi/OpenGl/OpenGlVertexArray.h"

#include "Kili/Core/Logger/Log.h"

//ADDAPI
Kili::VertexBuffer* Kili::VertexBuffer::create(const float* vertices, const Uint32 size)
{
    switch (Renderer::getApi())
    {
        case GraphicApi::OpenGl : return new OpenGlVertexBuffer(vertices, size); break;
    }
    
    LOG_WARNING("Unknown GraphicApi : " + Renderer::getApiName());
    return nullptr;
}
Kili::IndexBuffer* Kili::IndexBuffer::create(const Uint32* indices, const Uint32 count)
{
    switch (Renderer::getApi())
    {
        case GraphicApi::OpenGl : return new OpenGlIndexBuffer(indices, count); break;
    }
    
    LOG_WARNING("Unknown GraphicApi : " + Renderer::getApiName());
    return nullptr;
}