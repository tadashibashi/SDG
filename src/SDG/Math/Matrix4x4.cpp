//
// Created by Aaron Ishibashi on 5/3/22.
//
#include "Matrix4x4.h"
#include "SDG/Debug/Assert.h"
#include <SDL_gpu.h>

namespace SDG
{
    Matrix4x4::Matrix4x4() : mat{0}
    {

    }

    Matrix4x4::Matrix4x4(const Matrix4x4 &matrix)
    {
        memcpy(mat, matrix.mat, 16);
    }

    Matrix4x4::Matrix4x4(float *data) : mat{0}
    {
        memcpy(mat, data, 16);
    }

    Matrix4x4 &
    Matrix4x4::operator=(const Matrix4x4 &other)
    {
        memcpy(mat, other.mat, 16);
        return *this;
    }

    Matrix4x4::~Matrix4x4()
    {

    }

    Matrix4x4 &
    Matrix4x4::Translate(Vector3 position)
    {
        GPU_MatrixTranslate(mat, position.x, position.y, position.z);
        return *this;
    }

    Matrix4x4 &
    Matrix4x4::Rotate(float degrees, Vector3 anchor)
    {
        GPU_MatrixRotate(mat, degrees, anchor.x, anchor.y, anchor.z);
        return *this;
    }

    Matrix4x4
    Matrix4x4::Identity()
    {
        Matrix4x4 m;
        GPU_MatrixIdentity(m.mat);
        return m;
    }


    Matrix4x4 &
    Matrix4x4::Scale(Vector3 scalar)
    {
        GPU_MatrixScale(mat, scalar.x, scalar.y, scalar.z);
        return *this;
    }

    Matrix4x4 &
    Matrix4x4::Scale(float scalar)
    {
        GPU_MatrixScale(mat, scalar, scalar, scalar);
        return *this;
    }

    Matrix4x4 &
    Matrix4x4::operator *= (const Matrix4x4 &other)
    {
        GPU_MatrixMultiply(mat, mat, other.Data());
        return *this;
    }

    Matrix4x4 &
    Matrix4x4::operator *= (float scalar)
    {
        for (float *n = mat, *end = mat + 16;
             n != end;
             ++n)
        {
            *n *= scalar;
        }

        return *this;
    }

    Matrix4x4 &
    Matrix4x4::operator += (const Matrix4x4 &other)
    {
        const float *i = other.Data();
        for (float *n = mat, *end = mat + 16;
             n != end;
             ++n)
        {
            *n += *i;
        }

        return *this;
    }

    Matrix4x4 &
    Matrix4x4::operator -= (const Matrix4x4 &other)
    {
        const float *i = other.Data();
        for (float *n = mat, *end = mat + 16;
             n != end;
             ++n)
        {
            *n -= *i;
        }

        return *this;
    }

    Matrix4x4 &Matrix4x4::Multiply(const Matrix4x4 &other)
    {
        return *this *= other;
    }

    void Matrix4x4::Log()
    {
        printf("[%f %f %f %f\n"
               " %f %f %f %f\n"
               " %f %f %f %f\n"
               " %f %f %f %f]\n",
               mat[0], mat[1], mat[2], mat[3],
               mat[4], mat[5], mat[6], mat[7],
               mat[8], mat[9], mat[10], mat[11],
               mat[12], mat[13], mat[14], mat[15]
               );
    }

    Vector3 Matrix4x4::Position() const
    {
        return {mat[12], mat[13], mat[14]};
    }

    float Matrix4x4::GetEntry(int row, int column)
    {
        SDG_Assert(row > 0 && row <= 4 && column > 0 && column <= 4);
        return mat[(row - 1) * 4 + column - 1];
    }
}

SDG::Matrix4x4
operator * (const SDG::Matrix4x4 &m1, const SDG::Matrix4x4 &m2)
{
    return SDG::Matrix4x4(m1) *= m2;
}

SDG::Matrix4x4
operator * (const SDG::Matrix4x4 &m1, float scalar)
{
    return SDG::Matrix4x4(m1) *= scalar;
}

SDG::Matrix4x4
operator + (const SDG::Matrix4x4 &m1, const SDG::Matrix4x4 &m2)
{
    return SDG::Matrix4x4(m1) += m2;
}

SDG::Matrix4x4
operator - (const SDG::Matrix4x4 &m1, const SDG::Matrix4x4 &m2)
{
    return SDG::Matrix4x4(m1) -= m2;
}

bool operator == (const SDG::Matrix4x4 &m1, const SDG::Matrix4x4 &m2)
{
    for (const float *v1 = m1.Data(), *v2 = m2.Data(), *end = m1.Data() + 16;
            v1 != end;
            ++v1, ++v2)
    {
        if (*v1 != *v2) return false;
    }

    return true;
}

bool operator != (const SDG::Matrix4x4 &m1, const SDG::Matrix4x4 &m2)
{
    return !(m1 == m2);
}

