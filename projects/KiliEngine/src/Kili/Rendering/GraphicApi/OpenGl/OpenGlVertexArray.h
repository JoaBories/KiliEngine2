#pragma once
#include "Kili/Rendering/RHI/VertexArray.h"

namespace Kili
{
    class OpenGlVertexBuffer : public VertexBuffer
    {
    private:
        uint32_t mId;
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
        uint32_t mId;
        uint32_t mIndexCount;
        
    public:
        OpenGlIndexBuffer(const uint32_t* indices, uint32_t count);
        ~OpenGlIndexBuffer() override;
        
        void use() const override;
        [[nodiscard]] uint32_t count() const override { return mIndexCount; }
    };
    
    class OpenGlVertexArray : public VertexArray
    {
    private:
        uint32_t mId;
        uint32_t mVertexCount;
        
        std::vector<std::shared_ptr<VertexBuffer>> mVertexBuffers;
        std::shared_ptr<IndexBuffer> mIndexBuffer;
        
    public:
        OpenGlVertexArray();
        ~OpenGlVertexArray() override = default;
        
        void use() const override;
        
        void addVertexBuffer(const std::shared_ptr<VertexBuffer>& vertexBuffer) override;
        void setIndexBuffer(const std::shared_ptr<IndexBuffer>& indexBuffer) override;

        void setVertexCount(const uint32_t count) override { mVertexCount = count; }
        [[nodiscard]] uint32_t getVertexCount() const override { return mVertexCount; }

        [[nodiscard]] const std::vector<std::shared_ptr<VertexBuffer>>& getVertexBuffers() const override { return mVertexBuffers; }
        [[nodiscard]] const std::shared_ptr<IndexBuffer>& getIndexBuffer() const override { return mIndexBuffer; }
    };
}