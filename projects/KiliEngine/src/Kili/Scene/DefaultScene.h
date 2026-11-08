#pragma once

#include "Scene.h"
#include "Kili/Transform.h"
#include "Kili/CameraManager.h"
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
        std::vector<WorldTransform> mTransform;
        
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
            
            mTransform.reserve(10*10*10);
            for (int x = 1; x < 11; ++x) {
                for (int y = -5; y < 5; ++y) {
                    for (int z = -5; z < 5; ++z) {
                        mTransform.emplace_back(glm::vec3(x*4,y*4,z*4), glm::quat(glm::vec3(0.0f,0.0f,static_cast<float>(x+y+z))), glm::vec3(1.0f, 1.0f, 1.0f));
                    }
                }
            }
            
            mCamera.reset(new Camera(Transform(), 90.0f));
            CameraManager::addCamera(mCamera);
            CameraManager::setActiveCamera(mCamera);
            
            mTexture = AssetManager::getTexture("resources/kili.png");
            mMesh = AssetManager::getMesh("resources/cube.obj");
        }
        
        void onUpdate() override
        {
            for (int i = 0; i < mTransform.size(); ++i)
            {
                mTransform[i].rotate(glm::quat(glm::vec3(0.0f, glm::radians(30.0f * TimeClock::deltaTime()) ,0.0f)));
            }
            
            Transform& transform = mCamera->getTransform();
            glm::vec3 dir = glm::vec3(0.0f);
            if (InputManager::isKeyPressed(SDL_SCANCODE_A)) dir += glm::vec3(-1.0f, 0.0f, 0.0f);
            if (InputManager::isKeyPressed(SDL_SCANCODE_D)) dir += glm::vec3( 1.0f, 0.0f, 0.0f);
            if (InputManager::isKeyPressed(SDL_SCANCODE_W)) dir += glm::vec3( 0.0f, 1.0f, 0.0f);
            if (InputManager::isKeyPressed(SDL_SCANCODE_S)) dir += glm::vec3( 0.0f,-1.0f, 0.0f);
            if (InputManager::isKeyPressed(SDL_SCANCODE_Q)) dir += glm::vec3( 0.0f, 0.0f,-1.0f);
            if (InputManager::isKeyPressed(SDL_SCANCODE_E)) dir += glm::vec3( 0.0f, 0.0f, 1.0f);
            
            if (dir != glm::vec3(0.0f))
            {
                transform.addPosition(transform.right()   * dir.x * TimeClock::deltaTime() * 10.0f);
                transform.addPosition(transform.forward() * dir.y * TimeClock::deltaTime() * 10.0f);
                transform.addPosition(WORLD_UP * dir.z * TimeClock::deltaTime() * 10.0f);
            }
            
            glm::vec2 mouseDelta = InputManager::getMouseDelta();
            if (mouseDelta != glm::vec2(0.0f))
            {
                glm::vec3 forward = transform.forward();
                float yaw = glm::atan(-forward.z, forward.x);
                float pitch = glm::asin(glm::clamp(forward.y, -1.0f, 1.0f));
        
                yaw -= glm::radians(mouseDelta.x * 0.1f);
                pitch -= glm::radians(mouseDelta.y * 0.1f);
        
                pitch = glm::clamp(pitch, glm::radians(-89.0f), glm::radians(89.0f));

                glm::quat rotation = glm::normalize(glm::angleAxis(yaw, WORLD_UP) * glm::angleAxis(pitch, WORLD_RIGHT));
                transform.setRotation(rotation);
            }
        }
        
        void onRender() override
        {
            mTexture->use();
            for (int i = 0; i < mTransform.size(); ++i)
            {
                Renderer::submit(mShaderProgram, mMesh->getVertexArray(), mTransform[i]);
            }
        }

        void onEvent(const IEvent& event) override
        {
        }
        
    public:
        [[nodiscard]] std::string getName() const override { return "DefaultScene"; }
    };
}
