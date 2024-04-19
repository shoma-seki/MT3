#pragma once
#include "Struct.h"
#define _USE_MATH_DEFINES
#include <time.h>
#include <stdlib.h>
#include <Novice.h>
#include <stdio.h>
#include <assert.h>
#include <math.h>

const int MapSizeX = 80;
const int MapSizeY = 44;

static const int kRowHeight = 20;
static const int kColumnWidth = 60;

Matrix2x2 Add(Matrix2x2 matrix1, Matrix2x2 matrix2);
Matrix2x2 Subtract(Matrix2x2 matrix1, Matrix2x2 matrix2);
Matrix2x2 Multiply(Matrix2x2 matrix1, Matrix2x2 matrix2);
Matrix3x3 Multiply(Matrix3x3 matrix1, Matrix3x3 matrix2);
Vector2Array MultiplyV(Matrix2x2 matrix1, Vector2Array vector2);
Vector2Array Transform(Vector2Array vector, Matrix3x3 matrix);
Matrix3x3 MakeScaleMatrix(Vector2Array scale);
Matrix3x3 MakeTranslateMatrix(Vector2Array translate);
Matrix3x3 MakeRotateMatrix(float theta);
Matrix3x3 MakeAffineMatrix(Vector2Array scale, float theta, Vector2Array translate);
Matrix3x3 MakeOrthographicMatrix(float left, float top, float right, float bottom);
Matrix3x3 MakeViewportMatrix(float left, float top, float width, float height);
Matrix3x3 inverse(Matrix3x3 matrix);
Matrix3x3 RenderingPipeline(Matrix3x3 worldMatrix, Matrix3x3 viewMatrix, Matrix3x3 orthographicMatrix, Matrix3x3 viewportMatrix);

void MatrixScreenPrintf(int x, int y, const Matrix4x4 matrix, const char* label);

Vector3Float Add(const Vector3Float& v1, const Vector3Float& v2);
Vector3Float Subtract(const Vector3Float& v1, const Vector3Float& v2);
Vector3Float Multiply(float scalar, const Vector3Float& v);
Vector3Array Add(const Vector3Array& v1, const Vector3Array& v2);
Vector3Array Subtract(const Vector3Array& v1, const Vector3Array& v2);
Vector3Array Multiply(float scalar, const Vector3Array& v2);
float Dot(const Vector3Float& v1, const Vector3Float& v2);
float Dot(const Vector3Array& v1, const Vector3Array& v2);
float Length(const Vector3Float& v);
Vector3Float Normalize(const Vector3Float& v);
Vector3Array Cross(const Vector3Array& v1, const Vector3Array& v2);
Vector3Float Cross(const Vector3Float& v1, const Vector3Float& v2);

void VectorScreenPrintf(int x, int y, const Vector3Float& vector, const char* label);
void VectorScreenPrintf(int x, int y, const Vector3Array& vector, const char* label);

float DotProduct(
	float AstartX, float AstartY, float AendX, float AendY, float BstartX, float BstartY,
	float BendX, float BendY);
float CrossProduct(
	float AstartX, float AstartY, float AendX, float AendY, float BstartX, float BstartY,
	float BendX, float BendY);
float MAX(float x, float y);
float pNorm(float x, float y, float p);
float GetRadianThree(
	float AstartX, float AstartY, float AendX, float AendY, float BstartX, float BstartY,
	float BendX, float BendY);
float GetDegree(float radian);
float GetDis(Vector2Array pos1, Vector2Array pos2);
float GetDis(Vector2Float pos1, Vector2Float pos2);
float Normalize(float startX, float startY, float endX, float endY, int n);
Vector2Array NewNormalize(Vector2Array start, Vector2Array end);
float Clamp(float n, float min, float max);
float isBoxCollisionBeta(
	float leftTopX1, float leftTopY1, float rightBottomX1, float rightBottomY1, float leftTopX2,
	float leftTopY2, float rightBottomX2, float rightBottomY2);
float isCircleCollision(
	float posX1, float posY1, float posX2, float posY2, int radius1, int radius2);
bool NewCircleCollision(Vector2Array pos1, Vector2Array pos2, int radius1, int radius2);
float CC(float posY);
float LeftTopX(float posX, float width);
float LeftTopY(float posY, float height);
float LeftBottomX(float posX, float width);
float LeftBottomY(float posY, float height);
float RightTopX(float posX, float width);
float RightTopY(float posY, float height);
float RightBottomX(float posX, float width);
float RightBottomY(float posY, float height);
float CenterC(float leftTopX, float leftTopY, float width, float height, int n);
float isBoxCollision(
	float posX1, float posY1, float posX2, float posY2, float width, float height, float width2,
	float height2);
float IsOutOfScreen(float posX, float posYn, int ScreenSizeX, int ScreenSizeY);
float BoxPointCollision(
	float BoxLtX, float BoxLtY, float BoxRbX, float BoxRbY, int pointX, int pointY);
void MatrixScreenPrintf(int x, int y, Matrix2x2 matrix);
void Vector2ScreenPrintf(int x, int y, Vector2Array vector2);
void VDrawQuad(Vector2Array lt, Vector2Array rt, Vector2Array lb, Vector2Array rb, int textureWidth, int textureHeight, int Tex, unsigned int color);
void Easing(Vector2Array& pos, Vector2Array start, Vector2Array end, float t);
Vector2Array RotateDirection(Vector2Array direction, float theta);
int LinearInterpolation(int start, int end, float t);
float GetRadian(float degree);