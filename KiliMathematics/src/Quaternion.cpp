#include "Quaternion.h"

#include "Maths.h"
#include "Matrix4.h"

Quaternion Quaternion::lerp(const Quaternion& a, const Quaternion& b, const float t)
{
    Quaternion temp;
    temp.x = Klm::lerp(a.x, b.x, t);
    temp.y = Klm::lerp(a.y, b.y, t);
    temp.z = Klm::lerp(a.z, b.z, t);
    temp.w = Klm::lerp(a.w, b.w, t);
    temp.normalize();
    return temp;
}

Quaternion Quaternion::slerp(const Quaternion& a, const Quaternion& b, const float t)
{
    const float rawCosm = a.dot(b);

    float cosom = -rawCosm;
    if (rawCosm >= 0.0f)
    {
        cosom = rawCosm;
    }

    float scale0, scale1;

    if (cosom < 0.9999f)
    {
        const float omega = Klm::aCos(cosom);
        const float invSin = 1.f / Klm::sin(omega);
        scale0 = Klm::sin((1.f - t) * omega) * invSin;
        scale1 = Klm::sin(t * omega) * invSin;
    }
    else
    {
        // Use linear interpolation if the quaternions
        // are collinear
        scale0 = 1.0f - t;
        scale1 = t;
    }

    if (rawCosm < 0.0f)
    {
        scale1 = -scale1;
    }

    Quaternion temp;
    temp.x = scale0 * a.x + scale1 * b.x;
    temp.y = scale0 * a.y + scale1 * b.y;
    temp.z = scale0 * a.z + scale1 * b.z;
    temp.w = scale0 * a.w + scale1 * b.w;
    temp.normalize();
    return temp;
}

Quaternion Quaternion::concatenate(const Quaternion& q, const Quaternion& p)
{
    Quaternion retVal;

    // Vector component is:
    // ps * qv + qs * pv + pv x qv
    const Vector3 qv(q.x, q.y, q.z);
    const Vector3 pv(p.x, p.y, p.z);
    const Vector3 newVec = p.w * qv + q.w * pv + pv.cross(qv);
    retVal.x = newVec.x;
    retVal.y = newVec.y;
    retVal.z = newVec.z;

    // Scalar component is:
    // ps * qs - pv . qv
    retVal.w = p.w * q.w - pv.dot(qv);

    return retVal;
}

const Quaternion Quaternion::Identity = Quaternion(0.0f, 0.0f, 0.0f, 1.0f);

Quaternion::Quaternion(const Vector3& axis, const float angle)
{
    const float scalar = Klm::sin(angle / 2.0f);
    x = axis.x * scalar;
    y = axis.y * scalar;
    z = axis.z * scalar;
    w = Klm::cos(angle / 2.0f);
}

Matrix4 Quaternion::asMatrixRow() const
{
    Matrix4 m;

    const float xx = x * x;
    const float yy = y * y;
    const float zz = z * z;
    const float ww = w * w;
    const float xy = x * y;
    const float xz = x * z;
    const float xw = x * w;
    const float yz = y * z;
    const float yw = y * w;
    const float zw = z * w;

    m.mat[0][0] = 1.0f - 2.0f * (yy + zz);
    m.mat[0][1] =        2.0f * (xy - zw);
    m.mat[0][2] =        2.0f * (xz + yw);
    m.mat[0][3] =        0.0f;

    m.mat[1][0] =        2.0f * (xy + zw);
    m.mat[1][1] = 1.0f - 2.0f * (xx + zz);
    m.mat[1][2] =        2.0f * (yz - xw);
    m.mat[1][3] =        0.0f;

    m.mat[2][0] =        2.0f * (xz - yw);
    m.mat[2][1] =        2.0f * (yz + xw);
    m.mat[2][2] = 1.0f - 2.0f * (xx + yy);
    m.mat[2][3] =        0.0f;

    m.mat[3][0] =        0.0f;
    m.mat[3][1] =        0.0f;
    m.mat[3][2] =        0.0f;
    m.mat[3][3] =        1.0f;

    return m;
}

Quaternion Quaternion::operator*(const Quaternion& rhs) const
{
    Quaternion result;
    result.x = w * rhs.x + x * rhs.w + y * rhs.z - z * rhs.y;
    result.y = w * rhs.y - x * rhs.z + y * rhs.w + z * rhs.x;
    result.z = w * rhs.z + x * rhs.y - y * rhs.x + z * rhs.w;
    result.w = w * rhs.w - x * rhs.x - y * rhs.y - z * rhs.z;
    return result;
}

void Quaternion::conjugate()
{
    x *= -1.0f;
    y *= -1.0f;
    z *= -1.0f;
}

Quaternion Quaternion::conjugated() const
{
    Quaternion result = *this;
    result.conjugate();
    return result;
}

void Quaternion::normalize()
{
    const float len = length();
    x /= len;
    y /= len;
    z /= len;
    w /= len;
}
