#pragma once

#include <Novice.h>
#include <stdio.h>
#define _USE_MATH_DEFINES
#include "Struct.h"
#include <assert.h>
#include <cmath>
#include <ImGuiManager.h>

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
Matrix4x4 MakeAffineMatrix(const Vector3Array& scale, const Vector3Array& rotate, const Vector3Array& translate);
Vector3Array Transform(const Vector3Array& point, const Matrix4x4& transformationMatrix);

Matrix4x4 MakePerspectiveFovMatrix(float fovY, float aspectRatio, float nearClip, float farClip);
Matrix4x4 MakeOrthographicMatrix(float left, float top, float right, float bottom, float nearClip, float farClip);
Matrix4x4 MakeViewportMatrix(float left, float top, float width, float height, float minDepth, float maxDepth);

Vector3Array RenderingPipeline(const Vector3Array& local, const Matrix4x4& worldMatrix, const Camera3dData& camera);
Vector3Array RenderingPipeline(const Vector3Array& local, const Vector3Array& translate, const Camera3dData& camera);
void RenderingPipeline(Triangle& triangle, const Camera3dData& camera);

void DrawSphere(const Sphere& sphere, const Camera3dData& camera, uint32_t color, uint32_t subdivision);
void DrawGrid(const Camera3dData& camera);
void DrawLine(const Camera3dData& camera);
void DrawLine(const Vector3Array& p1, const Vector3Array& p2, const Camera3dData& camera, uint32_t color);
void DrawLine(const Vector3Array& p1, const Vector3Array& p2, uint32_t color);
void DrawAABB(const AABB& aabb, const Camera3dData& camera, uint32_t color);
void DrawOBB(const OBB& obb, const Camera3dData& camera, uint32_t color);