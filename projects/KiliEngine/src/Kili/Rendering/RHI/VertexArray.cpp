#include "klpch.h"
#include "VertexArray.h"

#include "Kili/Rendering/Renderer.h"
#include "Kili/Rendering/GraphicApi/OpenGl/OpenGlVertexArray.h"

#include "Kili/Core/Logger/Log.h"

//ADDAPI
namespace Kili
{
    std::unique_ptr<VertexBuffer> VertexBuffer::create(const float* vertices, const uint32_t size)
    {
        switch (Renderer::getApi())
        {
            case GraphicApi::OpenGl : return std::make_unique<OpenGlVertexBuffer>(vertices, size); break;
        }
    
        LOG_WARNING("Unknown GraphicApi : " + Renderer::getApiName());
        return nullptr;
    }

    std::unique_ptr<IndexBuffer> IndexBuffer::create(const uint32_t* indices, const uint32_t count)
    {
        switch (Renderer::getApi())
        {
            case GraphicApi::OpenGl : return std::make_unique<OpenGlIndexBuffer>(indices, count); break;
        }
    
        LOG_WARNING("Unknown GraphicApi : " + Renderer::getApiName());
        return nullptr;
    }

    std::unique_ptr<VertexArray> VertexArray::create()
    {
        switch (Renderer::getApi())
        {
            case GraphicApi::OpenGl : return std::make_unique<OpenGlVertexArray>(); break;
        }
    
        LOG_WARNING("Unknown GraphicApi : " + Renderer::getApiName());
        return nullptr;
    }
}

