#pragma once
#include "Kili/Renderer/VertexArray.h"

namespace Kili
{
    class OpenGlVertexBuffer : public VertexBuffer
    {
    private:
        Uint32 mId;
        
    public:
        OpenGlVertexBuffer(const float* vertices, Uint32 size);
        ~OpenGlVertexBuffer() override;
        
        void use() const override;
    };
    
    class OpenGlIndexBuffer : public IndexBuffer
    {
    private:
        Uint32 mId;
        Uint32 mIndexCount;
        
    public:
        OpenGlIndexBuffer(const Uint32* indices, Uint32 count);
        ~OpenGlIndexBuffer() override;
        
        void use() const override;
        [[nodiscard]] Uint32 count() const override { return mIndexCount; }
    };
    
    class OpenGlVertexArray : public VertexArray
    {
    public:
        virtual ~OpenGlVertexArray();
    
    };
}