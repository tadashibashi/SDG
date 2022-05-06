//
// Created by Aaron Ishibashi on 5/3/22.
//
#pragma once
#include "Vector3.h"
#include <string>
#include <glm/mat4x4.hpp>
#include "Rectangle.h"

namespace SDG
{
    /// Wraps glm::mat4x4
    /// Future: implement functions without glm
    class Matrix4x4
    {
    public:
        /// Default matrix constructor, set to a zero matrix.
        Matrix4x4();
        explicit Matrix4x4(float s);
        explicit Matrix4x4(glm::mat4x4 matrix) : mat(matrix) {}
        Matrix4x4(const Matrix4x4 &matrix);
        Matrix4x4 &operator=(const Matrix4x4 &other);
        ~Matrix4x4();

        void Log() const;
        std::string ToString() const;

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
        float Entry(int row, int column);

        static Matrix4x4 Identity();
        static Matrix4x4 Ortho(FRectangle rect);

        /// Gets the inner matrix, an array of 16 float values. Read-only.
        [[nodiscard]] const float *Data() const { return &mat[0][0]; }

        Matrix4x4 &operator *= (const Matrix4x4 &other);
        Matrix4x4 &operator *= (float scalar);
        Matrix4x4 &operator += (const Matrix4x4 &other);
        Matrix4x4 &operator -= (const Matrix4x4 &other);
        bool operator ==(const Matrix4x4 &other) const;
        bool operator !=(const Matrix4x4 &other) const;
    private:
        glm::mat4x4 mat;
    };


}

SDG::Matrix4x4 operator * (const SDG::Matrix4x4 &m1, const SDG::Matrix4x4 &m2);
SDG::Matrix4x4 operator * (const SDG::Matrix4x4 &m1, float scalar);
SDG::Matrix4x4 operator + (const SDG::Matrix4x4 &m1, const SDG::Matrix4x4 &m2);
SDG::Matrix4x4 operator - (const SDG::Matrix4x4 &m1, const SDG::Matrix4x4 &m2);
