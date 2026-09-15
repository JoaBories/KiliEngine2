#include "klpch.h"
#include "Transform.h"

namespace Kili
{
    void Transform::rotate(const Quaternion& rotation)
    {
        mRotation = Quaternion::concatenate(mRotation, rotation);
        mRotation.normalize();
    }

    void Transform::rotate(const Vector3& axis, const float angle)
    {
        const Quaternion increment(axis, angle);
        mRotation = Quaternion::concatenate(mRotation, increment);
    }

    void WorldTransform::recomputeWorldTransformMatrix() const
    {
        if (!mNeedUpdate) return;
        mNeedUpdate = false;
        mTransformMatrix = Matrix4::createScale(mTransform.getScale());
        mTransformMatrix *= Matrix4::createFromQuaternion(mTransform.getRotation());
        mTransformMatrix *= Matrix4::createTranslation(mTransform.getPosition());
    }
}
