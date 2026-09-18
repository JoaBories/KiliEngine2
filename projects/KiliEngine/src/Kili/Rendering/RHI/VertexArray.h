#pragma once
#include "Kili/Rendering/BufferLayout.h"

namespace Kili
{    
    /** 
     * Vertex buffer, used to store vertices data on the gpu.
     * Mostly used in the vertex array class.
    **/
    class VertexBuffer
    {
    public:
        virtual ~VertexBuffer() = default;
        
        virtual void use() const = 0;
        
        virtual void setLayout(const BufferLayout& layout) = 0;
        [[nodiscard]] virtual const BufferLayout& getLayout() const = 0;
        
        static VertexBuffer* create(const float* vertices, uint32_t size);
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
        [[nodiscard]] virtual uint32_t count() const = 0;
        
        static IndexBuffer* create(const uint32_t* indices, uint32_t count);
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
        virtual ~VertexArray() = default;
        
        virtual void use() const = 0;
        
        virtual void addVertexBuffer(const std::shared_ptr<VertexBuffer>& vertexBuffer) = 0;
        virtual void setIndexBuffer(const std::shared_ptr<IndexBuffer>& indexBuffer) = 0;

        /** Used for draw mesh without index buffers **/
        virtual void setVertexCount(uint32_t count) = 0;
        /** Used for draw mesh without index buffers **/
        [[nodiscard]] virtual uint32_t getVertexCount() const = 0;

        [[nodiscard]] virtual const std::vector<std::shared_ptr<VertexBuffer>>& getVertexBuffers() const = 0;
        [[nodiscard]] virtual const std::shared_ptr<IndexBuffer>& getIndexBuffer() const = 0;
        
        static VertexArray* create();
    
    };
}