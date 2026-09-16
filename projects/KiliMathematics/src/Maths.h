#pragma once

#include <limits>
#include <cmath>

namespace Klm {

    constexpr float PI = 3.1415926536f;
    constexpr float TWO_PI = PI * 2.0f;
    constexpr float HALF_PI = PI / 2.0f;
    constexpr float QUARTER_PI = PI / 4.0f;
    
    constexpr float DEG_2_RAD = PI/180;
    constexpr float RAD_2_DEG = 180/PI;
    
    constexpr double EPSILON = 1e-8;
    
    constexpr float INFINITY_POS = std::numeric_limits<float>::infinity();
    constexpr float INFINITY_NEG = -INFINITY_POS;

    // Arithmetic
    inline float Min(const float a, const float b)							                { return a <= b ? a : b; }
    inline int Min(const int a, const int b)							                    { return a <= b ? a : b; }
    inline float Max(const float a, const float b)							                { return a >= b ? a : b; }
    inline int Max(const int a, const int b)							                    { return a >= b ? a : b; }
    inline float Clamp(const float value, const float lower, const float upper)             { return Min(upper, Max(value, lower)); }
    inline int Clamp(const int value, const int lower, const int upper)                     { return Min(upper, Max(value, lower)); }
    
    inline float Abs(const float value)													    { return std::fabs(value); }
    inline float Sign(const float value)												    { return value > 0 ? 1.0f : value < 0 ? -1.0f : 0.0f; }
    inline float Lerp(const float a, const float b, const float t)						    { return a + (b - a) * Clamp(t, 0.0f, 1.0f); }
    inline float Sqrt(const float val)													    { return std::sqrtf(val); }
    inline float Fmod(const float x, const float y)								            { return std::fmod(x, y); }
    
    inline float Round(const float val, const int precision = 0)
    {
        const float power = static_cast<float>(std::pow(10, precision));
        return std::round(val * power) / power;
    }
    
    inline bool NearZero(const float value, const double epsilon = EPSILON)				    { return Abs(value) <= epsilon; }
    inline bool NearlyEqual(const float a, const float b, const double epsilon = EPSILON)   { return NearZero(a - b, epsilon); }
    
    // Trigonometry
    inline float Cos(const float angle)													    { return std::cosf(angle); }
    inline float Sin(const float angle)													    { return std::sinf(angle); }
    inline float Tan(const float angle)													    { return std::tanf(angle); }
    inline float ACos(const float angle)												    { return std::acosf(angle); }
    inline float ASin(const float angle)												    { return std::asinf(angle); }
    inline float ATan(const float angle)												    { return std::atanf(angle); }
    inline float ATan2(const float opposite, const float adjacent)						    { return std::atan2f(opposite, adjacent); }
    inline float Cot(const float angle)													    { return 1.0f / Tan(angle); }
};