#pragma once
#include "Transform.h"
#include "Core/Logger/Log.h"

namespace Kili
{
    class Camera
    {
    private:
        Transform mTransform;
        
        Matrix4 mViewMatrix;
        Matrix4 mProjMatrix;

        float mFov;
        float mNearPane;
        float mFarPane;
        
    public:
        explicit Camera(const Transform& transform, float fov = 90.0f, float near = 0.01f, float far = 1000.0f);
        
        Camera(const Camera& other) = delete;
        Camera(Camera&& other) noexcept = delete;
        Camera& operator=(const Camera& other) = delete;
        Camera& operator=(Camera&& other) noexcept = delete;
        
        void recalculate();
        
        [[nodiscard]] Matrix4 getViewMatrix() const { return mViewMatrix; }
        [[nodiscard]] Matrix4 getProjMatrix() const { return mProjMatrix; }
        [[nodiscard]] Matrix4 getViewProjMatrix() const { return  mViewMatrix * mProjMatrix; }
        
        [[nodiscard]] float getFov() const { return mFov; }
        void setFov(const float fov) { mFov = fov; }
        
        [[nodiscard]] float getNearPane() const { return mNearPane; }
        void setNearPane(const float near) { mNearPane = near; }
        
        [[nodiscard]] float getFarPane() const { return mFarPane; }
        void setFarPane(const float far) { mFarPane = far; }
    };
    
    class CameraManager
    {
    private:
        static std::vector<std::shared_ptr<Camera>> mCameras;
        static uint32_t mActiveCamera;
        
    public:
        static void addCamera(const std::shared_ptr<Camera>& camera);
        static void removeCamera(const std::shared_ptr<Camera>& camera);
        
        static std::shared_ptr<Camera> getActiveCamera() { if (mCameras.empty()) return nullptr; return mCameras[mActiveCamera]; }
        static bool setActiveCamera(const std::shared_ptr<Camera>& camera);
    };
}
