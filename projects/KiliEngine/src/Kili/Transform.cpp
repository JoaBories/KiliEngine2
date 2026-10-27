#include "klpch.h"
#include "Transform.h"

namespace Kili
{
    void Transform::rotate(const glm::quat& rotation)
    {
        mRotation = rotation * mRotation;
        mRotation = glm::normalize(mRotation);
    }

    void Transform::rotate(const glm::vec3& axis, const float angle)
    {
        const glm::quat increment(angle, axis);
        mRotation = increment * mRotation;
        mRotation = glm::normalize(mRotation);
    }

    void WorldTransform::recomputeWorldTransformMatrix() const
    {
        if (!mNeedUpdate) return;
        mNeedUpdate = false;
        mTransformMatrix = glm::translate(glm::mat4(1.0f), mTransform.getPosition());
        mTransformMatrix *= glm::mat4_cast(mTransform.getRotation());
        mTransformMatrix = glm::scale(mTransformMatrix, mTransform.getScale());
    }
}
