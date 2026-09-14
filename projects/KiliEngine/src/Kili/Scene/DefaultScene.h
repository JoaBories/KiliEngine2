#pragma once

#include "Scene.h"

namespace Kili
{
    class DefaultScene : public Scene
    {
    private:
        std::shared_ptr<VertexArray> mVertexArray; // Temp
        std::shared_ptr<Shader> mShaderProgram; // Temp
        
    protected:
        void onClose() override
        {
            mShaderProgram->unload();
            mVertexArray.reset();
        }
        
        void load() override
        {
            // Temp ===========================
            mVertexArray.reset(VertexArray::create());

            float vertices[4*7] = {
                -0.5f, -0.5f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f,
                 0.5f, -0.5f, 0.0f, 0.0f, 1.0f, 0.0f, 1.0f,
                 0.5f,  0.5f, 0.0f, 0.0f, 0.0f, 1.0f, 1.0f,
                -0.5f,  0.5f, 0.0f, 1.0f, 1.0f, 0.0f, 1.0f,
            };
        
            Uint32 indices[6] = {
                0, 1, 2,
                0, 2, 3
            };
        
            std::shared_ptr<VertexBuffer> vertexBuffer;
            vertexBuffer.reset(VertexBuffer::create(vertices, sizeof(vertices)));
        
            BufferLayout layout = {
                { "position", ShaderDataType::Float3 },
                { "color", ShaderDataType::Float4, true }
            };
        
            vertexBuffer->setLayout(layout);
        
            std::shared_ptr<IndexBuffer> indexBuffer;
            indexBuffer.reset(IndexBuffer::create(indices, sizeof(indices) / sizeof(Uint32)));
            
            mVertexArray->addVertexBuffer(vertexBuffer);
            mVertexArray->setIndexBuffer(indexBuffer);
        
            mShaderProgram.reset(Shader::create("Test", {"resources/Test.vert", "resources/Test.frag"}));
            mShaderProgram->load();
            // ================================
        }
        
        void onUpdate() override
        {
            
        }
        
        void onRender() override
        {
            mShaderProgram->use();
            mShaderProgram->setFloat("uTime", static_cast<float>(TimeClock::time()));
            Renderer::submit(mVertexArray);
        }

    public:
        [[nodiscard]] std::string getName() const override { return "DefaultScene"; }
    };
}
