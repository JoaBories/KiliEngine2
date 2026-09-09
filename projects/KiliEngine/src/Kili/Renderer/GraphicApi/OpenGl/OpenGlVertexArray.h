#pragma once
#include "Kili/Renderer/VertexArray.h"

namespace Kili
{
    class OpenGlVertexBuffer : public VertexBuffer
    {
    private:
        unsigned int mId;
        
    public:
        OpenGlVertexBuffer(const float* vertices, unsigned long size);
        ~OpenGlVertexBuffer() override;
        
        void use() const override;
    };
    
    class OpenGlIndexBuffer : public IndexBuffer
    {
    private:
        unsigned int mId;
        unsigned long mIndiceCount;
        
    public:
        OpenGlIndexBuffer(const unsigned long* indices, unsigned long count);
        ~OpenGlIndexBuffer() override;
        
        void use() const override;
        [[nodiscard]] unsigned long count() const override { return mIndiceCount; }
    };
    
    class OpenGlVertexArray : public VertexArray
    {
    public:
        virtual ~OpenGlVertexArray();
    
    };
}