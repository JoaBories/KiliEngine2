#include "Vector4.h"

#include "Quaternion.h"
#include "Matrix4.h"

Vector4 Vector4::transform(const Vector4& vec, const Quaternion& quat)
{
    const Vector4 qv(quat.x, quat.y, quat.z, quat.w);
    Vector4 retVal = vec;
    
    retVal += 2.0f * Vector4::cross(qv, Vector4::cross(qv, vec) + quat.w * vec);
    return retVal;
}

Vector4 Vector4::transform(const Vector4& vec, const Matrix4& mat)
{
    Vector4 retVal;
    retVal.x = vec.x * mat.mat[0][0] + vec.y * mat.mat[1][0] + vec.z * mat.mat[2][0] + vec.w * mat.mat[3][0];
    retVal.y = vec.x * mat.mat[0][1] + vec.y * mat.mat[1][1] + vec.z * mat.mat[2][1] + vec.w * mat.mat[3][1];
    retVal.z = vec.x * mat.mat[0][2] + vec.y * mat.mat[1][2] + vec.z * mat.mat[2][2] + vec.w * mat.mat[3][2];
    retVal.w = vec.w;
    
    return retVal;
}

const Vector4 Vector4::Zero = Vector4(0.0f, 0.0f, 0.0f, 0.0f);
const Vector4 Vector4::Unit = Vector4(1.0f, 1.0f, 1.0f, 1.0f);
const Vector4 Vector4::UnitX = Vector4(1.0f, 0.0f, 0.0f, 0.0f);
const Vector4 Vector4::UnitY = Vector4(0.0f, 1.0f, 0.0f, 0.0f);
const Vector4 Vector4::UnitZ = Vector4(0.0f, 0.0f, 1.0f, 0.0f);
const Vector4 Vector4::UnitW = Vector4(0.0f, 0.0f, 0.0f, 1.0f);