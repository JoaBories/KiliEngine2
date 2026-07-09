#pragma once

#include <Vector3.h>

#include "Quaternion.h"

// Matrix in row major

struct Matrix4
{
    float mat[4][4];
    
    Matrix4() { *this = Matrix4::Identity; }
    explicit Matrix4(float inMat[4][4]) { memcpy(mat, inMat, 16 * sizeof(float)); }

    [[nodiscard]] const float* asFloatPtr() const { return &mat[0][0]; }
    
    bool operator==(const Matrix4& other) const { return std::equal(std::begin(mat), std::end(mat), std::begin(other.mat)); }
    
    friend Matrix4 operator*(const Matrix4& a, const Matrix4& b);
    Matrix4 operator*=(const Matrix4& rhs);
    
    void invert();

    [[nodiscard]] Vector3 transformVector3(const Vector3& vector, float w = 1.0f) const;

    [[nodiscard]] Vector3 getTranslation() const { return Vector3(mat[3][0], mat[3][1], mat[3][2]); }

    [[nodiscard]] Vector3 getXAxis() const { return Vector3(mat[0][0], mat[0][1], mat[0][2]).normalized(); }
    [[nodiscard]] Vector3 getYAxis() const { return Vector3(mat[1][0], mat[1][1], mat[1][2]).normalized(); }
    [[nodiscard]] Vector3 getZAxis() const { return Vector3(mat[2][0], mat[2][1], mat[2][2]).normalized(); }

    [[nodiscard]] Vector3 getScale() const
    {
        Vector3 temp;
        temp.x = Vector3(mat[0][0], mat[0][1], mat[0][2]).length();
        temp.y = Vector3(mat[1][0], mat[1][1], mat[1][2]).length();
        temp.z = Vector3(mat[2][0], mat[2][1], mat[2][2]).length();
        return temp; 
    }
    
    [[nodiscard]] Vector3 getEulerRotation() const
    {
        const float sy = Klm::sqrt(mat[0][0] * mat[0][0] + mat[1][0] * mat[1][0]);
        Vector3 temp;

        if (sy > 1e-6)
        {
            temp.x = Klm::aTan2(mat[2][1], mat[2][2]);
            temp.y = Klm::aTan2(-mat[2][0], sy);
            temp.z = Klm::aTan2(mat[1][0], mat[0][0]);
        }
        else
        {
            temp.x = Klm::aTan2(-mat[1][2], mat[1][1]);
            temp.y = Klm::aTan2(-mat[2][0], sy);
            temp.z = 0;
        }
        return temp;
    }
    
    static Matrix4 createScale(const float xScale, const float yScale, const float zScale)
    {
        float temp[4][4] =
        {
            { xScale, 0.0f, 0.0f, 0.0f },
            { 0.0f, yScale, 0.0f, 0.0f },
            { 0.0f, 0.0f, zScale, 0.0f },
            { 0.0f, 0.0f, 0.0f  , 1.0f }
        };
        return Matrix4(temp);
    }

    static Matrix4 createScale(const Vector3& scaleVector)
    {
        return createScale(scaleVector.x, scaleVector.y, scaleVector.z);
    }

    static Matrix4 createScale(const float scale)
    {
        return createScale(scale, scale, scale);
    }
    
    static Matrix4 createRotationX(const float theta)
    {
        float temp[4][4] =
        {
            { 1.0f, 0.0f, 0.0f , 0.0f },
            { 0.0f, Klm::cos(theta), -Klm::sin(theta), 0.0f },
            { 0.0f, Klm::sin(theta), Klm::cos(theta), 0.0f },
            { 0.0f, 0.0f, 0.0f, 1.0f },
        };
        return Matrix4(temp);
    }

    static Matrix4 createRotationY(const float theta)
    {
        float temp[4][4] =
        {
            { Klm::cos(theta), 0.0f, Klm::sin(theta), 0.0f },
            { 0.0f, 1.0f, 0.0f, 0.0f },
            { -Klm::sin(theta), 0.0f, Klm::cos(theta), 0.0f },
            { 0.0f, 0.0f, 0.0f, 1.0f },
        };
        return Matrix4(temp);
    }

    static Matrix4 createRotationZ(const float theta)
    {
        float temp[4][4] =
        {
            { Klm::cos(theta), -Klm::sin(theta), 0.0f, 0.0f },
            { Klm::sin(theta), Klm::cos(theta), 0.0f, 0.0f },
            { 0.0f, 0.0f, 1.0f, 0.0f },
            { 0.0f, 0.0f, 0.0f, 1.0f },
        };
        return Matrix4(temp);
    }
    
    static Matrix4 createTranslation(const Vector3& trans)
    {
        float temp[4][4] =
        {
            { 1.0f, 0.0f, 0.0f, 0.0f },
            { 0.0f, 1.0f, 0.0f, 0.0f },
            { 0.0f, 0.0f, 1.0f, 0.0f },
            { trans.x, trans.y, trans.z, 1.0f }
        };
        return Matrix4(temp);
    }

    static Matrix4 createSimpleViewProj(const float width, const float height)
    {
        float temp[4][4] =
        {
            { 2.0f / width, 0.0f, 0.0f, 0.0f },
            { 0.0f, 2.0f / height, 0.0f, 0.0f },
            { 0.0f, 0.0f, 1.0f, 0.0f },
            { 0.0f, 0.0f, 1.0f, 1.0f }
        };
        return Matrix4(temp);
    }
    
    static Matrix4 createFromQuaternion(const Quaternion& q);
    static Matrix4 createLookAt(const Vector3& eye, const Vector3& target, const Vector3& up);
    
    static Matrix4 createOrtho(const float width, const float height, const float near, const float far)
    {
        float temp[4][4] =
        {
            { 1.0f / width, 0.0f, 0.0f, 0.0f },
            { 0.0f, 1.0f / height, 0.0f, 0.0f },
            { 0.0f, 0.0f, -2.0f / (far - near), 0.0f },
            { 0.0f, 0.0f, (far + near) / (near - far), 1.0f }
        };
        return Matrix4(temp);
    }

    static Matrix4 createPerspectiveFov(const float fovY, const float width, const float height, const float near, const float far)
    {
        const float yScale = Klm::cot(fovY / 2.0f);
        const float xScale = yScale * height / width;
        float temp[4][4] =
        {
            { xScale, 0.0f, 0.0f, 0.0f },
            { 0.0f, yScale, 0.0f, 0.0f },
            { 0.0f, 0.0f, far / (far - near), 1.0f },
            { 0.0f, 0.0f, -near * far / (far - near), 0.0f }
        };
        return Matrix4(temp);
    }

    static Matrix4 createPerspective(const float left, const float right, const float bottom, const float top, const float near, const float far)
    {
        float temp[4][4] =
        {
            { 2 * near / (right - left), 0.0f, 0.0f, 0.0f },
            { 0.0f, 2 * near / (top - bottom), 0.0f, 0.0f },
            { (right + left) / (right - left), (top + bottom) / (top - bottom), (far + near) / (near - far), -1.0f },
            { 0.0f, 0.0f, 2 * near * far / (near - far), 0.0f }
        };
        return Matrix4(temp);
    }
    
    static const Matrix4 Identity;
};
