#pragma once

#include <stdexcept>
#include <string>

#include <Maths.h>

struct Vector4
{
    float x, y, z, w;
    
    Vector4() : x(0.0f), y(0.0f), z(0.0f), w(0.0f) {}
    explicit Vector4(const float x, const float y, const float z, const float w) : x(x), y(y), z(z), w(w) {}
    explicit Vector4(const float size) : x(size), y(size), z(size), w(size) {}
    
    [[nodiscard]] const float* asFloatPtr() const { return &x; }
    
    [[nodiscard]] float& operator[](const int i)
    {
        switch (i) {
            case 0: return x;
            case 1: return y;
            case 2: return z;
            case 3: return w;
            default: throw std::out_of_range("Vector4 index out of range");
        }
    }
    
    [[nodiscard]] float operator[](const int i) const
    {
        switch (i) {
        case 0: return x;
        case 1: return y;
        case 2: return z;
        case 3: return w;
        default: throw std::out_of_range("Vector4 index out of range");
        }
    }
    
    [[nodiscard]] float at(const int i) const
    {
        switch (i)
        {
            case 0: return x;
            case 1: return y;
            case 2: return z;
            case 3: return w;
            default: return 0;
        }
    }
    
    [[nodiscard]] std::string asString() const { return "x : " + std::to_string(x) + " , y: " + std::to_string(y) + " , z: " + std::to_string(z) + " , w: " + std::to_string(w); }
    
    Vector4 operator+(const Vector4& rhs) const { return Vector4(x + rhs.x, y + rhs.y, z + rhs.z, w + rhs.w); }
    Vector4 operator-(const Vector4& rhs) const { return Vector4(x - rhs.x, y - rhs.y, z - rhs.z, w - rhs.w); }
    Vector4 operator*(const Vector4& rhs) const { return Vector4(x * rhs.x, y * rhs.y, z * rhs.z, w * rhs.w); }
    Vector4 operator/(const Vector4& rhs) const { return Vector4(x / rhs.x, y / rhs.y, z / rhs.z, w / rhs.w); }
    
    friend Vector4 operator*(const Vector4& a, const float b)       { return Vector4(a.x * b, a.y * b, a.z * b, a.w * b); }
    friend Vector4 operator*(const float a, const Vector4& b)       { return Vector4(a * b.x, a * b.y, a * b.z, a * b.w); }
    friend Vector4 operator/(const Vector4& a, const float b)       { return Vector4(a.x / b, a.y / b, a.z / b, a.w / b); }
    
    Vector4& operator+=(const Vector4& rhs) { x += rhs.x; y += rhs.y; z += rhs.z; w += rhs.w ; return *this; }
    Vector4& operator-=(const Vector4& rhs) { x -= rhs.x; y -= rhs.y; z -= rhs.z; w -= rhs.w ; return *this; }
    Vector4& operator*=(const Vector4& rhs) { x *= rhs.x; y *= rhs.y; z *= rhs.z; w *= rhs.w ; return *this; }
    Vector4& operator/=(const Vector4& rhs) { x /= rhs.x; y /= rhs.y; z /= rhs.z; w /= rhs.w ; return *this; }
    
    Vector4& operator*=(const float b)      { x *= b; y *= b; z *= b; w *= b; return *this; }
    Vector4& operator/=(const float b)      { x /= b; y /= b; z /= b; w /= b; return *this; }
    
    Vector4 operator-() const { return Vector4(-x, -y, -z, -w); }
    
    bool operator==(const Vector4& rhs) const
    {
        if (Klm::nearlyEqual(x, rhs.x)) if (Klm::nearlyEqual(y, rhs.y)) if (Klm::nearlyEqual(z, rhs.z)) return true;
        return false;
    }
    bool operator!=(const Vector4& rhs) const { return !(*this == rhs); }

    [[nodiscard]] float lengthSquared() const   { return x * x + y * y + z * z + w * w; }
    [[nodiscard]] float length() const          { return Klm::sqrt(lengthSquared()); }
    
    void normalize() { *this /= length(); }
    [[nodiscard]] Vector4 normalized() const    { return *this / length(); }
    
    [[nodiscard]] float dot(const Vector4& rhs) const { return x * rhs.x + y * rhs.y + z * rhs.z; }
    [[nodiscard]] Vector4 cross(const Vector4& rhs) const { return Vector4(y * rhs.z - z * rhs.y, z * rhs.x - x * rhs.z, x * rhs.y - y * rhs.x, 0.0f); }
    
    [[nodiscard]] static Vector4 lerp(const Vector4& a, const Vector4& b, const float t) { return a + (b - a) * t; }
    [[nodiscard]] static Vector4 reflect(const Vector4& v, const Vector4& n) { return v - 2.0f * v.dot(n) * n; }
    
    static const Vector4 Zero;
    static const Vector4 Unit;
    static const Vector4 UnitX;
    static const Vector4 UnitY;
    static const Vector4 UnitZ;
    static const Vector4 UnitW;
};