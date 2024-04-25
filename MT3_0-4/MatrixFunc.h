#pragma once

#include <Novice.h>
#include <stdio.h>
#define _USE_MATH_DEFINES
#include "Struct.h"
#include <assert.h>
#include <cmath>

Matrix4x4 Add(const Matrix4x4& m1, const Matrix4x4& m2);
Matrix4x4 Subtract(const Matrix4x4& m1, const Matrix4x4& m2);
Matrix4x4 Multiply(const Matrix4x4& m1, const Matrix4x4& m2);
Matrix4x4 inverse(const Matrix4x4& matrix);
Matrix4x4 Transpose(const Matrix4x4& m);
Matrix4x4 MakeIdentityMatrix();

Matrix4x4 MakeTranslateMatrix(const Vector3Array& translate);
Matrix4x4 MakeScaleMatrix(const Vector3Array& scale);
Matrix4x4 MakeRotateXMatrix(float radian);
Matrix4x4 MakeRotateYMatrix(float radian);
Matrix4x4 MakeRotateZMatrix(float radian);
Vector3Array Transform(const Vector3Array& point, const Matrix4x4& transformationMatrix);