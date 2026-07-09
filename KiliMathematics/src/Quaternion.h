#pragma once
#include "Vector3.h"

struct Quaternion
{
    float x, y, z, w;
    
    Quaternion() { *this = Quaternion::Identity; }
    
    explicit Quaternion(const float x, const float y, const float z, const float w) : x(x), y(y), z(z), w(w) {}
    explicit Quaternion(const Vector3& axis, float angle);

    [[nodiscard]] struct Matrix4 asMatrixRow() const;
    
    Quaternion operator*(const Quaternion& rhs) const;
    
    void conjugate();
    [[nodiscard]] Quaternion conjugated() const;
    
    void normalize();

    [[nodiscard]] float lengthSquared() const { return x * x + y * y + z * z + w * w; }
    [[nodiscard]] float length() const { return Klm::sqrt(lengthSquared()); }
    
    [[nodiscard]] float dot(const Quaternion& rhs) const { return x * rhs.x + y * rhs.y + z * rhs.z + w * rhs.w; }
    
    static Quaternion lerp(const Quaternion& a, const Quaternion& b, float t);
    static Quaternion slerp(const Quaternion& a, const Quaternion& b, float t);
    
    static Quaternion concatenate(const Quaternion& q, const Quaternion& p);
    
    static const Quaternion Identity;
};
