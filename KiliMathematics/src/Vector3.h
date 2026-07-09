#pragma once

#include <stdexcept>
#include <string>

#include <Maths.h>

struct Vector3
{
    float x, y, z;
    
    Vector3() : x(0.0f), y(0.0f), z(0.0f) {}
    explicit Vector3(const float x, const float y, const float z) : x(x), y(y), z(z) {}
    explicit Vector3(const float size) : x(size), y(size), z(size) {}
    
    [[nodiscard]] const float* asFloatPtr() const { return &x; }
    
    [[nodiscard]] float& operator[](const int i)
    {
        switch (i) {
            case 0: return x;
            case 1: return y;
            case 2: return z;
            default: throw std::out_of_range("Vector3 index out of range");
        }
    }
    
    [[nodiscard]] float operator[](const int i) const
    {
        switch (i) {
        case 0: return x;
        case 1: return y;
        case 2: return z;
        default: throw std::out_of_range("Vector3 index out of range");
        }
    }
    
    [[nodiscard]] float at(const int i) const
    {
        switch (i)
        {
            case 0: return x;
            case 1: return y;
            case 2: return z;
            default: return 0;
        }
    }
    
    [[nodiscard]] std::string asString() const { return "x : " + std::to_string(x) + " , y: " + std::to_string(y) + " , z: " + std::to_string(z); }
    
    Vector3 operator+(const Vector3& rhs) const { return Vector3(x + rhs.x, y + rhs.y, z + rhs.z); }
    Vector3 operator-(const Vector3& rhs) const { return Vector3(x - rhs.x, y - rhs.y, z - rhs.z); }
    Vector3 operator*(const Vector3& rhs) const { return Vector3(x * rhs.x, y * rhs.y, z * rhs.z); }
    Vector3 operator/(const Vector3& rhs) const { return Vector3(x / rhs.x, y / rhs.y, z / rhs.z); }
    
    friend Vector3 operator*(const Vector3& a, const float b)       { return Vector3(a.x * b, a.y * b, a.z * b); }
    friend Vector3 operator*(const float a, const Vector3& b)       { return Vector3(a * b.x, a * b.y, a * b.z); }
    friend Vector3 operator/(const Vector3& a, const float b)       { return Vector3(a.x / b, a.y / b, a.z / b); }
    
    Vector3& operator+=(const Vector3& rhs) { x += rhs.x; y += rhs.y; z += rhs.z; return *this; }
    Vector3& operator-=(const Vector3& rhs) { x -= rhs.x; y -= rhs.y; z -= rhs.z; return *this; }
    Vector3& operator*=(const Vector3& rhs) { x *= rhs.x; y *= rhs.y; z *= rhs.z; return *this; }
    Vector3& operator/=(const Vector3& rhs) { x /= rhs.x; y /= rhs.y; z /= rhs.z; return *this; }
    
    Vector3& operator*=(const float b)      { x *= b; y *= b; z *= b; return *this; }
    Vector3& operator/=(const float b)      { x /= b; y /= b; z /= b; return *this; }
    
    Vector3 operator-() const { return Vector3(-x, -y, -z); }
    
    bool operator==(const Vector3& rhs) const
    {
        if (Klm::nearlyEqual(x, rhs.x)) if (Klm::nearlyEqual(y, rhs.y)) if (Klm::nearlyEqual(z, rhs.z)) return true;
        return false;
    }
    bool operator!=(const Vector3& rhs) const { return !(*this == rhs); }

    [[nodiscard]] float lengthSquared() const   { return x * x + y * y + z * z; }
    [[nodiscard]] float length() const          { return Klm::sqrt(lengthSquared()); }
    
    void normalize() { *this /= length(); }
    [[nodiscard]] Vector3 normalized() const    { return *this / length(); }
    
    [[nodiscard]] float dot(const Vector3& rhs) const { return x * rhs.x + y * rhs.y + z * rhs.z; }
    [[nodiscard]] Vector3 cross(const Vector3& rhs) const { return Vector3(y * rhs.z - z * rhs.y, z * rhs.x - x * rhs.z, x * rhs.y - y * rhs.x ); }
    
    [[nodiscard]] static Vector3 lerp(const Vector3& a, const Vector3& b, const float t) { return a + (b - a) * t; }
    [[nodiscard]] static Vector3 reflect(const Vector3& v, const Vector3& n) { return v - 2.0f * v.dot(n) * n; }
    
    static const Vector3 Zero;
    static const Vector3 Unit;
    static const Vector3 UnitX;
    static const Vector3 UnitY;
    static const Vector3 UnitZ;
};
