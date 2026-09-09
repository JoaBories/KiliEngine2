#pragma once

namespace Kili
{
    class VertexBuffer
    {
    public:
        virtual ~VertexBuffer() = default;
        
        virtual void use() const = 0;
        
        static VertexBuffer* create(const float* vertices, long size);
    };
    
    class IndexBuffer
    {
    public:
        virtual ~IndexBuffer() = default;
        
        virtual void use() const = 0;
        [[nodiscard]] virtual unsigned long count() const = 0;
        
        static IndexBuffer* create(const unsigned long* indices, unsigned long count);
    };
    
    class VertexArray
    {
    public:
        virtual ~VertexArray();
    
    };
}