//
// Created by Aaron Ishibashi on 5/3/22.
//
#pragma once
#include <SDG/Math/Matrix4x4.h>

using SDG::Matrix4x4;

void TestMatrix()
{
    Matrix4x4 mat = Matrix4x4::Identity();
    mat.Log();

    mat.Translate({3, 4, 5});
    mat.Log();

    mat.Translate({3, 4, 5});
    mat.Log();

    mat.Scale(4);
    mat.Log();

    mat.Rotate(10, {1, 1, 1});
    mat.Log();
}
