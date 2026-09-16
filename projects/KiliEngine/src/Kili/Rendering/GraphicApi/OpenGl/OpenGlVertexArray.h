#pragma once
#include "Kili/Rendering/RHI/VertexArray.h"

namespace Kili
{
    class OpenGlVertexBuffer : public VertexBuffer
    {
    private:
        Uint32 mId;
        BufferLayout mLayout = {};
        
    public:
        OpenGlVertexBuffer(const float* vertices, Uint32 size);
        ~OpenGlVertexBuffer() override;
        
        void use() const override;
        
        void setLayout(const BufferLayout& layout) override { mLayout = layout; }
        [[nodiscard]] const BufferLayout& getLayout() const override { return mLayout; }
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
    private:
        Uint32 mId;
        
        std::vector<std::shared_ptr<VertexBuffer>> mVertexBuffers;
        std::shared_ptr<IndexBuffer> mIndexBuffer;
        
    public:
        OpenGlVertexArray();
        ~OpenGlVertexArray() override = default;
        
        void use() const override;
        
        void addVertexBuffer(const std::shared_ptr<VertexBuffer>& vertexBuffer) override;
        void setIndexBuffer(const std::shared_ptr<IndexBuffer>& indexBuffer) override;

        [[nodiscard]] const std::vector<std::shared_ptr<VertexBuffer>>& getVertexBuffers() const override { return mVertexBuffers; }
        [[nodiscard]] const std::shared_ptr<IndexBuffer>& getIndexBuffer() const override { return mIndexBuffer; }
    };
}