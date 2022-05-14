//
// Created by Aaron Ishibashi on 5/3/22.
//
#include "Matrix4x4.h"
#include "SDG/Debug/Assert.h"
#include "Math.h"
#include <glm/glm.hpp>
#include <glm/ext/matrix_clip_space.hpp>
#include <glm/gtx/transform.hpp>
#include <SDL_gpu.h>

namespace SDG
{
    Matrix4x4::Matrix4x4() : mat{0}
    {

    }

    Matrix4x4::Matrix4x4(float s) : mat {s}
    {

    }

    Matrix4x4::Matrix4x4(const Matrix4x4 &matrix)
    {
        mat = matrix.mat;
    }

    Matrix4x4 Matrix4x4::Ortho(float left, float right, float bottom, float top)
    {
        return Matrix4x4{glm::ortho(left, right, bottom, top)};
    }

    Matrix4x4 &
    Matrix4x4::operator=(const Matrix4x4 &other)
    {
        mat = other.mat;
        return *this;
    }

    Matrix4x4::~Matrix4x4()
    {

    }

    Matrix4x4 &
    Matrix4x4::Translate(Vector3 position)
    {
        mat *= glm::translate(glm::vec3{position.X(), position.Y(), position.Z()});
        return *this;
    }

    Matrix4x4 &
    Matrix4x4::Rotate(float degrees, Vector3 axis)
    {
        if (degrees != 0)
            mat *= glm::rotate((float)Math::DegToRad(degrees), glm::vec3{axis.X(), axis.Y(), axis.Z()});
        return *this;
    }

    Matrix4x4
    Matrix4x4::Identity()
    {
        return Matrix4x4{1.f};
    }


    Matrix4x4 &
    Matrix4x4::Scale(Vector3 scalar)
    {
        mat = glm::scale(mat, {scalar.X(), scalar.Y(), scalar.Z()});
        return *this;
    }

    Matrix4x4 &
    Matrix4x4::Scale(float scalar)
    {
        mat = glm::scale(mat, {scalar, scalar, scalar});
        return *this;
    }

    Matrix4x4 &
    Matrix4x4::Perspective(float fovy, float aspect, float znear, float zfar)
    {
        mat *= glm::perspective(fovy, aspect, znear, zfar);
        return *this;
    }

    Matrix4x4 &
    Matrix4x4::operator *= (const Matrix4x4 &other)
    {
        mat *= other.mat;
        return *this;
    }

    Matrix4x4 &
    Matrix4x4::operator *= (float scalar)
    {
        mat *= scalar;

        return *this;
    }

    Matrix4x4 &
    Matrix4x4::operator += (const Matrix4x4 &other)
    {
        mat += other.mat;
        return *this;
    }

    Matrix4x4 &
    Matrix4x4::operator -= (const Matrix4x4 &other)
    {
        mat -= other.mat;

        return *this;
    }

    Matrix4x4 &Matrix4x4::Multiply(const Matrix4x4 &other)
    {
        return *this *= other;
    }

    std::string
    Matrix4x4::ToString() const
    {
        char buf[256];
        sprintf(buf, "[%f %f %f %f\n"
                " %f %f %f %f\n"
                " %f %f %f %f\n"
                " %f %f %f %f]\n",
                mat[0][0], mat[1][0], mat[2][0], mat[3][0],
                mat[0][1], mat[1][1], mat[2][1], mat[3][1],
                mat[0][2], mat[1][2], mat[2][2], mat[3][2],
                mat[0][3], mat[1][3], mat[2][3], mat[3][3]
        );

        return buf;
    }

    void
    Matrix4x4::Log() const
    {
        printf("%s", ToString().c_str());
    }

    float Matrix4x4::Entry(int row, int column)
    {
        SDG_Assert(row >= 0 && row < 4 && column >= 0 && column < 4);
        return mat[column][row];
    }


    Matrix4x4 &
    Matrix4x4::LookAt(Vector3 eye, Vector3 center, Vector3 up)
    {
        mat = glm::lookAt(glm::vec3{eye.X(), eye.Y(), eye.Z()},
                           glm::vec3{center.X(), center.Y(), center.Z()},
                           glm::vec3{up.X(), up.Y(), up.Z()});
        return *this;
    }

    Matrix4x4 &Matrix4x4::Invert()
    {
        mat = glm::inverse(mat);
        return *this;
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

bool
SDG::Matrix4x4::operator == (const SDG::Matrix4x4 &other) const
{
    return mat == other.mat;
}

bool
SDG::Matrix4x4::operator != (const SDG::Matrix4x4 &other) const
{
    return !(*this == other);
}

void
SDG::Matrix4x4::Transform(float *x, float *y) const
{
    float resX = (*x * mat[0][0]) + (*y * mat[1][0]) + mat[3][0];
    float resY = (*x * mat[0][1]) + (*y * mat[1][1]) + mat[3][1];
    *x = resX;
    *y = resY;
}
