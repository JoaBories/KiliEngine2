#include "klpch.h"
#include "CameraManager.h"

#include "Kili/Rendering/Renderer.h"

namespace Kili
{
    std::vector<std::shared_ptr<Camera>> CameraManager::mCameras = {};
    uint32_t CameraManager::mActiveCamera = 0;
    
    Camera::Camera(const Transform& transform, const float fov, const float near, const float far) :
        mTransform(transform), mFov(fov), mNearPane(near), mFarPane(far)
    {
    }

    void Camera::recalculate()
    {
        const Vector3 camPosition = mTransform.getPosition();
        const Vector3 target = camPosition + mTransform.getForwardVector() * 100.0f;
        mViewMatrix = Matrix4::createLookAt(camPosition, target, Vector3::UnitY);

        const Vector2 screenSize = Renderer::getScreenSize();
        mProjMatrix = Matrix4::createPerspectiveFov(mFov, screenSize.x, screenSize.y, mNearPane, mFarPane);
    }

    void CameraManager::addCamera(const std::shared_ptr<Camera>& camera)
    {
        if (const auto iter = std::find(mCameras.begin(), mCameras.end(), camera); iter == mCameras.end())
            mCameras.emplace_back(camera);
    }

    void CameraManager::removeCamera(const std::shared_ptr<Camera>& camera)
    {
        if (const auto iter = std::find(mCameras.begin(), mCameras.end(), camera); iter == mCameras.end())
            mCameras.erase(iter);
    }

    bool CameraManager::setActiveCamera(const std::shared_ptr<Camera>& camera)
    {
        if (const auto iter = std::find(mCameras.begin(), mCameras.end(), camera); iter == mCameras.end())
        {
            mActiveCamera = static_cast<uint32_t>(std::distance(mCameras.begin(), iter));
            return true;
        }
        
        return false;
    }
}
