#pragma once
#include "Kili/Renderer/BufferLayout.h"

namespace Kili
{    
    /** 
     * Vertex buffer, used to store vertices data on the gpu.
     * Mostly used in the vertex array class.
    **/
    class VertexBuffer
    {
    protected:
        BufferLayout mLayout = {};
        
    public:
        virtual ~VertexBuffer() = default;
        
        virtual void use() const = 0;
        
        void setLayout(const BufferLayout& layout) { mLayout = layout; }
        [[nodiscard]] const BufferLayout& getLayout() const { return mLayout; }
        
        static VertexBuffer* create(const float* vertices, Uint32 size);
    };
    
    /**
     * Index buffer, used to store index data on the gpu.
     * Mostly used in the vertex array class.
    **/
    class IndexBuffer
    {
    public:
        virtual ~IndexBuffer() = default;
        
        virtual void use() const = 0;
        [[nodiscard]] virtual Uint32 count() const = 0;
        
        static IndexBuffer* create(const Uint32* indices, Uint32 count);
    };
    
    /** 
     * Vertex array, abstract Vertex and Index buffer and add a layout to vertex.
     * Represent a mesh for the gpu.
     * 
     * standard layout : 1. position 3f / 2. normal 3f / 3. texture coordinate 2f
    **/
    class VertexArray
    {
    public:
        virtual ~VertexArray();
    
    };
}