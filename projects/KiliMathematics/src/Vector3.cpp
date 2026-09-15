#include "Vector3.h"

#include "Matrix4.h"
#include "Quaternion.h"

Vector3 Vector3::transform(const Vector3& vec, const Quaternion& quat)
{
    const Vector3 qv(quat.x, quat.y, quat.z);
    Vector3 retVal = vec;
    
    retVal += 2.0f * Vector3::cross(qv, Vector3::cross(qv, vec) + quat.w * vec);
    return retVal;
}

Vector3 Vector3::transform(const Vector3& vec, const Matrix4& mat, const float w)
{
    Vector3 retVal;
    retVal.x = vec.x * mat.mat[0][0] + vec.y * mat.mat[1][0] + vec.z * mat.mat[2][0] + w * mat.mat[3][0];
    retVal.y = vec.x * mat.mat[0][1] + vec.y * mat.mat[1][1] + vec.z * mat.mat[2][1] + w * mat.mat[3][1];
    retVal.z = vec.x * mat.mat[0][2] + vec.y * mat.mat[1][2] + vec.z * mat.mat[2][2] + w * mat.mat[3][2];

    return retVal;
}

const Vector3 Vector3::Zero(0.0f, 0.0f, 0.0f);
const Vector3 Vector3::Unit(1.0f, 1.0f, 1.0f);
const Vector3 Vector3::UnitX(1.0f, 0.0f, 0.0f);
const Vector3 Vector3::UnitY(0.0f, 1.0f, 0.0f);
const Vector3 Vector3::UnitZ(0.0f, 0.0f, 1.0f);