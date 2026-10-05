#pragma once

#include "DefaultScene.h"
#include "Scene.h"
#include "Kili/Transform.h"
#include "Kili/CameraManager.h"
#include "Kili/FileReadWrite/MaterialFile.h"
#include "Kili/AssetManager/AssetManager.h"

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
            
            mMesh.reset();
            
            CameraManager::removeCamera(mCamera);
            mCamera.reset();
        }
        
        void load() override
        {
            mShaderProgram = AssetManager::getShader("resources/Test.shader");
            
            MaterialFile test = MaterialFile::readMaterial("resources/Test.mat");
            
            mTransform = Transform(Vector3(5,0,0), Quaternion(Vector3::UnitZ, Klm::DEG_2_RAD * 45.0f), Vector3::Unit);
            
            mCamera.reset(new Camera(Transform(), 60.0f));
            CameraManager::addCamera(mCamera);
            CameraManager::setActiveCamera(mCamera);
            
            mTexture = AssetManager::getTexture("resources/kili.png");
            mMesh = AssetManager::getMesh("resources/cube.obj");
        }
        
        void onUpdate() override
        {
            mTransform.rotate(Quaternion(Vector3::UnitY, 10.0f * TimeClock::deltaTime() * Klm::DEG_2_RAD));
        }
        
        void onRender() override
        {
            mTexture->use();
            Renderer::submit(mShaderProgram, mMesh->getVertexArray(), mTransform);
        }

        void onEvent(const IEvent& event) override
        {
        }
        
    public:
        [[nodiscard]] std::string getName() const override { return "DefaultScene"; }
    };
}
