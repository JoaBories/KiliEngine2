#pragma once

#include "DefaultScene.h"
#include "Scene.h"
#include "Kili/Transform.h"
#include "Kili/CameraManager.h"
#include "Kili/Rendering/Mesh.h"
#include "Kili/Rendering/RHI/Texture.h"

namespace Kili
{
    class DefaultScene : public Scene
    {
    private:
        std::shared_ptr<Mesh> mMesh;
        std::shared_ptr<Shader> mShaderProgram;
        std::shared_ptr<Texture> mTexture;
        std::shared_ptr<Camera> mCamera;
        WorldTransform mTransform;
        
    protected:
        void onClose() override
        {
            mShaderProgram.reset();
            
            mMesh->unload();
            mMesh.reset();
            
            CameraManager::removeCamera(mCamera);
            mCamera.reset();
        }
        
        void load() override
        {
            // Temp =====================================
            mShaderProgram.reset(Shader::create("Test", "resources/Test.shader"));
            
            mTransform = Transform(Vector3(5,0,0), Quaternion(Vector3::UnitZ, Klm::DEG_2_RAD * 45.0f), Vector3::Unit);
            
            mCamera.reset(new Camera(Transform(), 60.0f));
            CameraManager::addCamera(mCamera);
            CameraManager::setActiveCamera(mCamera);
            
            mTexture.reset(Texture::create({true, WrapMode::Repeat, TextureFilterMethod::Linear}, "resources/kili.png"));
            mTexture->load();
            
            mMesh.reset(new Mesh("resources/cube.obj", mShaderProgram));
            mMesh->load();
            // ==========================================
        }
        
        void onUpdate() override
        {
            mTransform.rotate(Quaternion(Vector3::UnitY, 10.0f * TimeClock::deltaTime() * Klm::DEG_2_RAD));
        }
        
        void onRender() override
        {
            mTexture->use();
            Renderer::submit(mMesh->getShader(), mMesh->getVertexArray(), mTransform);
        }

        void onEvent(const IEvent& event) override
        {
        }
        
    public:
        [[nodiscard]] std::string getName() const override { return "DefaultScene"; }
    };
}
