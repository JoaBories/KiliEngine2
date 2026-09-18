#pragma once

#include "DefaultScene.h"
#include "Scene.h"
#include "Kili/Transform.h"
#include "Kili/CameraManager.h"
#include "Kili/Rendering/Mesh.h"

namespace Kili
{
    class DefaultScene : public Scene
    {
    private:
        std::shared_ptr<Mesh> mMesh;
        std::shared_ptr<Shader> mShaderProgram;
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
            // Temp ===========================
            mShaderProgram.reset(Shader::create("Test", {"resources/Test.vert", "resources/Test.frag"}));
            
            mTransform = Transform(Vector3(1,0,0), Quaternion(Vector3::UnitY, Klm::DEG_2_RAD * 0.0f), Vector3::Unit);
            
            mCamera.reset(new Camera(Transform(), 60.0f));
            CameraManager::addCamera(mCamera);
            CameraManager::setActiveCamera(mCamera);
            
            mMesh.reset(new Mesh("resources/dragon.obj", mShaderProgram));
            mMesh->load();
            // ================================
        }
        
        void onUpdate() override
        {
            mTransform.rotate(Quaternion(Vector3::UnitY, 10.0f * TimeClock::deltaTime() * Klm::DEG_2_RAD));
        }
        
        void onRender() override
        {
            Renderer::submit(mMesh->getShader(), mMesh->getVertexArray(), mTransform);
        }

        void onEvent(const IEvent& event) override
        {
        }
        
    public:
        [[nodiscard]] std::string getName() const override { return "DefaultScene"; }
    };
}
