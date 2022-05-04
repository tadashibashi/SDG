//
// Created by Aaron Ishibashi on 5/3/22.
//
#pragma once

#include "Vector3.h"

namespace SDG
{
    class Matrix4x4
    {
    public:
        /// Default matrix constructor, set to a zero matrix.
        Matrix4x4();
        explicit Matrix4x4(float *data);
        Matrix4x4(const Matrix4x4 &matrix);
        Matrix4x4 &operator=(const Matrix4x4 &other);
        ~Matrix4x4();
        void Log();

        Matrix4x4 &Translate(Vector3 position);
        Matrix4x4 &Rotate(float degrees, Vector3 anchor);
        Matrix4x4 &Scale(Vector3 scalar);
        Matrix4x4 &Scale(float scalar);
        Matrix4x4 &Multiply(const Matrix4x4 &other);

        /// Both row and column must be numbers between 1-4 (inclusive)
        float GetEntry(int row, int column);

        Vector3 Position() const; // not sure if this is correct...

        static Matrix4x4 Identity();;
        /// Gets the inner matrix, an array of 16 float values. Read-only.
        [[nodiscard]] const float *Data() const { return mat; }

        Matrix4x4 &operator *= (const Matrix4x4 &other);
        Matrix4x4 &operator *= (float scalar);
        Matrix4x4 &operator += (const Matrix4x4 &other);
        Matrix4x4 &operator -= (const Matrix4x4 &other);
    private:
        float mat[16];
    };


}

SDG::Matrix4x4 operator * (const SDG::Matrix4x4 &m1, const SDG::Matrix4x4 &m2);
SDG::Matrix4x4 operator * (const SDG::Matrix4x4 &m1, float scalar);
SDG::Matrix4x4 operator + (const SDG::Matrix4x4 &m1, const SDG::Matrix4x4 &m2);
SDG::Matrix4x4 operator - (const SDG::Matrix4x4 &m1, const SDG::Matrix4x4 &m2);
bool operator == (const SDG::Matrix4x4 &m1, const SDG::Matrix4x4 &m2);
bool operator != (const SDG::Matrix4x4 &m1, const SDG::Matrix4x4 &m2);
