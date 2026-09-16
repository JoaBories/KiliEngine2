#pragma once

#include "DefaultScene.h"
#include "Scene.h"
#include "Kili/Transform.h"
#include "Kili/CameraManager.h"

namespace Kili
{
    class DefaultScene : public Scene
    {
    private:
        std::shared_ptr<VertexArray> mVertexArray;
        std::shared_ptr<Shader> mShaderProgram;
        std::shared_ptr<Camera> mCamera;
        WorldTransform mTransform;
        
    protected:
        void onClose() override
        {
            mShaderProgram.reset();
            mVertexArray.reset();
            
            CameraManager::removeCamera(mCamera);
            mCamera.reset();
        }
        
        void load() override
        {
            // Temp ===========================
            mVertexArray.reset(VertexArray::create());
            
            float vertices[4*9] = {
                -0.5f, -0.5f, 0.0f,     0.0f, 0.0f,
                 0.5f, -0.5f, 0.0f,     1.0f, 0.0f,
                 0.5f,  0.5f, 0.0f,     1.0f, 1.0f,
                -0.5f,  0.5f, 0.0f,     0.0f, 1.0f
            };
        
            Uint32 indices[2*3] = {
                0, 1, 2,
                0, 2, 3
            };
        
            std::shared_ptr<VertexBuffer> vertexBuffer;
            vertexBuffer.reset(VertexBuffer::create(vertices, sizeof(vertices)));
        
            BufferLayout layout = {
                { "position", ShaderDataType::Float3 },
                { "uv", ShaderDataType::Float2, false },
            };
        
            vertexBuffer->setLayout(layout);
        
            std::shared_ptr<IndexBuffer> indexBuffer;
            indexBuffer.reset(IndexBuffer::create(indices, sizeof(indices) / sizeof(Uint32)));
            
            mVertexArray->addVertexBuffer(vertexBuffer);
            mVertexArray->setIndexBuffer(indexBuffer);
        
            mShaderProgram.reset(Shader::create("Test", {"resources/Test.vert", "resources/Test.frag"}));
            
            mTransform = Transform(Vector3(1,0,0), Quaternion(Vector3::UnitY, Klm::DEG_2_RAD * 90.0f), Vector3::Unit);
            
            mCamera.reset(new Camera(Transform()));
            CameraManager::addCamera(mCamera);
            CameraManager::setActiveCamera(mCamera);
            // ================================
        }
        
        void onUpdate() override
        {
        }
        
        void onRender() override
        {
            Renderer::submit(mShaderProgram, mVertexArray, mTransform);
        }

        void onEvent(const IEvent& event) override
        {
        }
        
    public:
        [[nodiscard]] std::string getName() const override { return "DefaultScene"; }
    };
}
