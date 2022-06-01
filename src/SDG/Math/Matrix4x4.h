/*!
 * @file Matrix4x4.h
 * @namespace SDG
 * @class Matrix4x4
 * A 4 by 4 matrix. Wraps a glm::mat4x4.
 * 
 */
#pragma once
#include "Vector3.h"
#include "Rectangle.h"

#include <SDG/Lib/String.h>

namespace SDG
{
    /// A 4 by 4 matrix. Wraps a glm::mat4x4.
    class Matrix4x4
    {
        struct Impl;
    public:
        /// Default matrix constructor, set to a zero matrix.
        Matrix4x4();
        explicit Matrix4x4(float s);
        explicit Matrix4x4(void *glm_mat4x4);
        Matrix4x4(const Matrix4x4 &matrix);
        Matrix4x4 &operator=(const Matrix4x4 &other);
        ~Matrix4x4();

        void Log() const;
        String Str() const;

        Matrix4x4 &Translate(Vector3 position);
        void Transform(float *x, float *y) const;
        Matrix4x4 &Rotate(float degrees, Vector3 axis);
        Matrix4x4 &Scale(Vector3 scalar);
        Matrix4x4 &Scale(float scalar);
        Matrix4x4 &Multiply(const Matrix4x4 &other);
        Matrix4x4 &LookAt(Vector3 eye, Vector3 center, Vector3 up);
        Matrix4x4 &Perspective(float fovy, float aspect, float znear, float zfar);
        Matrix4x4 &Invert();

        /// Both row and column must be numbers between 1-4 (inclusive)
        float Entry(int row, int column) const;
        float &Entry(int row, int column);

        [[nodiscard]] static Matrix4x4 Identity();
        [[nodiscard]] static Matrix4x4 Ortho(float left, float right, float bottom, float top);

        /// Gets the inner matrix, an array of 16 float values. Read-only.
        [[nodiscard]] const float *Data() const;

        Matrix4x4 &operator *= (const Matrix4x4 &other);
        Matrix4x4 &operator *= (float scalar);
        Matrix4x4 &operator += (const Matrix4x4 &other);
        Matrix4x4 &operator -= (const Matrix4x4 &other);
        [[nodiscard]] bool operator ==(const Matrix4x4 &other) const;
        [[nodiscard]] bool operator !=(const Matrix4x4 &other) const;
    private:
        Impl *impl;
    };

    Matrix4x4 operator * (const Matrix4x4 &m1, const Matrix4x4 &m2);
    Matrix4x4 operator * (const Matrix4x4 &m1, float scalar);
    Matrix4x4 operator + (const Matrix4x4 &m1, const Matrix4x4 &m2);
    Matrix4x4 operator - (const Matrix4x4 &m1, const Matrix4x4 &m2);
}


