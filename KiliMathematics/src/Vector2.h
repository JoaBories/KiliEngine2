#pragma once

#include <stdexcept>
#include <string>

#include <Maths.h>

struct Vector2
{
    float x, y;
    
    Vector2() : x(0.0f), y(0.0f) {}
    explicit Vector2(const float x, const float y) : x(x), y(y) {}
    explicit Vector2(const float size) : x(size), y(size) {}
    
    [[nodiscard]] const float* asFloatPtr() const { return &x; }
    
    [[nodiscard]] float& operator[](const int i)
    {
        switch (i) {
            case 0: return x;
            case 1: return y;
            default: throw std::out_of_range("Vector2 index out of range");
        }
    }
    
    [[nodiscard]] float operator[](const int i) const
    {
        switch (i) {
        case 0: return x;
        case 1: return y;
        default: throw std::out_of_range("Vector2 index out of range");
        }
    }
    
    [[nodiscard]] float at(const int i) const
    {
        switch (i)
        {
            case 0: return x;
            case 1: return y;
            default: return 0;
        }
    }
    
    [[nodiscard]] std::string asString() const { return "x : " + std::to_string(x) + " , y: " + std::to_string(y); }
    
    Vector2 operator+(const Vector2& rhs) const { return Vector2(x + rhs.x, y + rhs.y); }
    Vector2 operator-(const Vector2& rhs) const { return Vector2(x - rhs.x, y - rhs.y); }
    Vector2 operator*(const Vector2& rhs) const { return Vector2(x * rhs.x, y * rhs.y); }
    Vector2 operator/(const Vector2& rhs) const { return Vector2(x / rhs.x, y / rhs.y); }
    
    friend Vector2 operator*(const Vector2& a, const float b)       { return Vector2(a.x * b, a.y * b); }
    friend Vector2 operator*(const float a, const Vector2& b)       { return Vector2(a * b.x, a * b.y); }
    friend Vector2 operator/(const Vector2& a, const float b)       { return Vector2(a.x / b, a.y / b); }
    
    Vector2& operator+=(const Vector2& rhs) { x += rhs.x; y += rhs.y; return *this; }
    Vector2& operator-=(const Vector2& rhs) { x -= rhs.x; y -= rhs.y; return *this; }
    Vector2& operator*=(const Vector2& rhs) { x *= rhs.x; y *= rhs.y; return *this; }
    Vector2& operator/=(const Vector2& rhs) { x /= rhs.x; y /= rhs.y; return *this; }
    
    Vector2& operator*=(const float b)      { x *= b; y *= b; return *this; }
    Vector2& operator/=(const float b)      { x /= b; y /= b; return *this; }
    
    Vector2 operator-() const { return Vector2(-x, -y); }
    
    bool operator==(const Vector2& rhs) const
    {
        if (Klm::nearlyEqual(x, rhs.x)) if (Klm::nearlyEqual(y, rhs.y)) return true;
        return false;
    }
    bool operator!=(const Vector2& rhs) const { return !(*this == rhs); }

    [[nodiscard]] float lengthSquared() const   { return x * x + y * y; }
    [[nodiscard]] float length() const          { return Klm::sqrt(lengthSquared()); }
    
    void normalize() { *this /= length(); }
    [[nodiscard]] Vector2 normalized() const    { return *this / length(); }
    
    [[nodiscard]] float dot(const Vector2& rhs) const { return x * rhs.x + y * rhs.y; }
    
    [[nodiscard]] static Vector2 lerp(const Vector2& a, const Vector2& b, const float t) { return a + (b - a) * t; }
    [[nodiscard]] static Vector2 reflect(const Vector2& v, const Vector2& n) { return v - 2.0f * v.dot(n) * n; }
    
    static const Vector2 Zero;
    static const Vector2 Unit;
    static const Vector2 UnitX;
    static const Vector2 UnitY;
};