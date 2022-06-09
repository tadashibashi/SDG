// Matrix4x4 implementation file

#include "Matrix4x4.h"
#include "Math.h"

#include <Engine/Debug/Assert.h>

#include <glm/ext/matrix_clip_space.hpp>
#include <glm/glm.hpp>
#include <glm/gtx/transform.hpp>
#include <SDL_gpu.h>

#include <utility>

namespace SDG
{
    struct Matrix4x4::Impl
    {
        explicit Impl(float s) : mat(s) { }
        explicit Impl(glm::mat4x4 mat) : mat(std::move(mat)) { }

        glm::mat4x4 mat;
    };

    Matrix4x4::Matrix4x4() : impl(new Impl(0))
    {

    }

    Matrix4x4::Matrix4x4(float s) : impl(new Impl(s))
    {

    }

    Matrix4x4::Matrix4x4(const Matrix4x4 &matrix) : impl(new Impl(matrix.impl->mat))
    {
        
    }

    Matrix4x4::Matrix4x4(void *glm_mat4x4) : impl(new Impl( *(glm::mat4x4 *)(glm_mat4x4) ))
    {

    }

    Matrix4x4::~Matrix4x4()
    {
        delete impl;
    }

    Matrix4x4 Matrix4x4::Ortho(float left, float right, float bottom, float top)
    {
        auto mat = glm::ortho(left, right, bottom, top);
        return Matrix4x4{&mat};
    }

    Matrix4x4 &
    Matrix4x4::operator=(const Matrix4x4 &other)
    {
        impl->mat = other.impl->mat;
        return *this;
    }

    const float *
    Matrix4x4::Data() const 
    {
        return &impl->mat[0][0];
    }

    Matrix4x4 &
    Matrix4x4::Translate(Vector3 position)
    {
        impl->mat *= glm::translate(glm::vec3{position.X(), position.Y(), position.Z()});
        return *this;
    }

    Matrix4x4 &
    Matrix4x4::Rotate(float degrees, Vector3 axis)
    {
        if (degrees != 0)
            impl->mat *= glm::rotate((float) Math::ToRadians(degrees), glm::vec3{axis.X(), axis.Y(), axis.Z()});
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
        impl->mat = glm::scale(impl->mat, {scalar.X(), scalar.Y(), scalar.Z()});
        return *this;
    }

    Matrix4x4 &
    Matrix4x4::Scale(float scalar)
    {
        impl->mat = glm::scale(impl->mat, {scalar, scalar, scalar});
        return *this;
    }

    Matrix4x4 &
    Matrix4x4::Perspective(float fovy, float aspect, float znear, float zfar)
    {
        impl->mat *= glm::perspective(fovy, aspect, znear, zfar);
        return *this;
    }

    Matrix4x4 &
    Matrix4x4::operator *= (const Matrix4x4 &other)
    {
        impl->mat *= other.impl->mat;
        return *this;
    }

    Matrix4x4 &
    Matrix4x4::operator *= (float scalar)
    {
        impl->mat *= scalar;

        return *this;
    }

    Matrix4x4 &
    Matrix4x4::operator += (const Matrix4x4 &other)
    {
        impl->mat += other.impl->mat;
        return *this;
    }

    Matrix4x4 &
    Matrix4x4::operator -= (const Matrix4x4 &other)
    {
        impl->mat -= other.impl->mat;

        return *this;
    }

    Matrix4x4 &Matrix4x4::Multiply(const Matrix4x4 &other)
    {
        return *this *= other;
    }

    String
    Matrix4x4::Str() const
    {
        char buf[256];
        sprintf(buf, "[%f %f %f %f\n"
                " %f %f %f %f\n"
                " %f %f %f %f\n"
                " %f %f %f %f]\n",
                impl->mat[0][0], impl->mat[1][0], impl->mat[2][0], impl->mat[3][0],
                impl->mat[0][1], impl->mat[1][1], impl->mat[2][1], impl->mat[3][1],
                impl->mat[0][2], impl->mat[1][2], impl->mat[2][2], impl->mat[3][2],
                impl->mat[0][3], impl->mat[1][3], impl->mat[2][3], impl->mat[3][3]
        );

        return buf;
    }

    float
    Matrix4x4::Entry(int row, int column) const
    {
        SDG_Assert(row >= 0 && row < 4 && column >= 0 && column < 4);
        return impl->mat[column][row];
    }

    float &
    Matrix4x4::Entry(int row, int column)
    {
        SDG_Assert(row >= 0 && row < 4 && column >= 0 && column < 4);
        return impl->mat[column][row];
    }


    Matrix4x4 &
    Matrix4x4::LookAt(Vector3 eye, Vector3 center, Vector3 up)
    {
        impl->mat = glm::lookAt(glm::vec3{eye.X(), eye.Y(), eye.Z()},
                           glm::vec3{center.X(), center.Y(), center.Z()},
                           glm::vec3{up.X(), up.Y(), up.Z()});
        return *this;
    }

    Matrix4x4 &Matrix4x4::Invert()
    {
        impl->mat = glm::inverse(impl->mat);
        return *this;
    }
    

    // ===== Global operators =================================================

    Matrix4x4
    operator * (const Matrix4x4 &m1, const Matrix4x4 &m2)
    {
        return Matrix4x4(m1) *= m2;
    }

    Matrix4x4
    operator * (const Matrix4x4 &m1, float scalar)
    {
        return Matrix4x4(m1) *= scalar;
    }

    Matrix4x4
    operator + (const Matrix4x4 &m1, const Matrix4x4 &m2)
    {
        return Matrix4x4(m1) += m2;
    }

    Matrix4x4
    operator - (const Matrix4x4 &m1, const Matrix4x4 &m2)
    {
        return Matrix4x4(m1) -= m2;
    }

    bool
    Matrix4x4::operator == (const Matrix4x4 &other) const
    {
        return impl->mat == other.impl->mat;
    }

    bool
    Matrix4x4::operator != (const Matrix4x4 &other) const
    {
        return !operator==(other);
    }

    void
    Matrix4x4::Transform(float *x, float *y) const
    {
        float resX = (*x * impl->mat[0][0]) + (*y * impl->mat[1][0]) + impl->mat[3][0];
        float resY = (*x * impl->mat[0][1]) + (*y * impl->mat[1][1]) + impl->mat[3][1];
        *x = resX;
        *y = resY;
    }
}
