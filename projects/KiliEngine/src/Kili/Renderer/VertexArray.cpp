#include "klpch.h"
#include "VertexArray.h"

#include "GraphicApi/OpenGl/OpenGlVertexArray.h"

Kili::VertexBuffer* Kili::VertexBuffer::create(const float* vertices, const long size)
{
    switch (GRAPHIC_API)
    {
        case GraphicApi::OpenGl : return new OpenGlVertexBuffer(vertices, size); break;
        default: return nullptr; break;
    }
}
Kili::IndexBuffer* Kili::IndexBuffer::create(const unsigned long* indices, const unsigned long count)
{
    switch (GRAPHIC_API)
    {
        case GraphicApi::OpenGl : return new OpenGlIndexBuffer(indices, count); break;
        default: return nullptr; break;
    }
}