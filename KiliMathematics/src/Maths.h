#pragma once

#include <limits>
#include <cmath>

namespace Klm {

    constexpr float Pi = 3.1415926536f;
    constexpr float TwoPi = Pi * 2.0f;
    constexpr float HalfPi = Pi / 2.0f;
    constexpr float QuarterPi = Pi / 4.0f;
    
    constexpr float Deg2Rad = Pi/180;
    constexpr float Rad2Deg = 180/Pi;
    
    constexpr double Epsilon = 1e-8;
    
    constexpr float InfinityPos = std::numeric_limits<float>::infinity();
    constexpr float InfinityNeg = -InfinityPos;

    // Arithmetic
    inline float min(const float a, const float b)							                { return a <= b ? a : b; }
    inline int min(const int a, const int b)							                    { return a <= b ? a : b; }
    inline float max(const float a, const float b)							                { return a >= b ? a : b; }
    inline int max(const int a, const int b)							                    { return a >= b ? a : b; }
    inline float clamp(const float value, const float lower, const float upper)             { return min(upper, max(value, lower)); }
    inline int clamp(const int value, const int lower, const int upper)                     { return min(upper, max(value, lower)); }
    
    inline float abs(const float value)													    { return std::fabs(value); }
    inline float sign(const float value)												    { return value > 0 ? 1.0f : value < 0 ? -1.0f : 0.0f; }
    inline float lerp(const float a, const float b, const float t)						    { return a + (b - a) * clamp(t, 0.0f, 1.0f); }
    inline float sqrt(const float val)													    { return std::sqrtf(val); }
    inline float fmod(const float x, const float y)								            { return std::fmod(x, y); }
    
    inline float round(const float val, const int precision = 0)
    {
        const float power = static_cast<float>(std::pow(10, precision));
        return std::round(val * power) / power;
    }
    
    inline bool nearZero(const float value, const double epsilon = Epsilon)				    { return abs(value) <= epsilon; }
    inline bool nearlyEqual(const float a, const float b, const double epsilon = Epsilon)   { return nearZero(a - b, epsilon); }
    
    // Trigonometry
    inline float cos(const float angle)													    { return std::cosf(angle); }
    inline float sin(const float angle)													    { return std::sinf(angle); }
    inline float tan(const float angle)													    { return std::tanf(angle); }
    inline float aCos(const float angle)												    { return std::acosf(angle); }
    inline float aSin(const float angle)												    { return std::asinf(angle); }
    inline float aTan(const float angle)												    { return std::atanf(angle); }
    inline float aTan2(const float opposite, const float adjacent)						    { return std::atan2f(opposite, adjacent); }
    inline float cot(const float angle)													    { return 1.0f / tan(angle); }
    
};