#include "klpch.h"
#include "VertexArray.h"

#include "Kili/Rendering/Renderer.h"
#include "Kili/Rendering/GraphicApi/OpenGl/OpenGlVertexArray.h"

#include "Kili/Core/Logger/Log.h"

//ADDAPI
Kili::VertexBuffer* Kili::VertexBuffer::create(const float* vertices, const uint32_t size)
{
    switch (Renderer::getApi())
    {
        case GraphicApi::OpenGl : return new OpenGlVertexBuffer(vertices, size); break;
    }
    
    LOG_WARNING("Unknown GraphicApi : " + Renderer::getApiName());
    return nullptr;
}

Kili::IndexBuffer* Kili::IndexBuffer::create(const uint32_t* indices, const uint32_t count)
{
    switch (Renderer::getApi())
    {
        case GraphicApi::OpenGl : return new OpenGlIndexBuffer(indices, count); break;
    }
    
    LOG_WARNING("Unknown GraphicApi : " + Renderer::getApiName());
    return nullptr;
}

Kili::VertexArray* Kili::VertexArray::create()
{
    switch (Renderer::getApi())
    {
        case GraphicApi::OpenGl : return new OpenGlVertexArray(); break;
    }
    
    LOG_WARNING("Unknown GraphicApi : " + Renderer::getApiName());
    return nullptr;
}

