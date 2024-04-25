#pragma once
#include <vector>

const int kParticleMax = 200;

const int kRainMax = 200;
const int kSnowMax = 700;

struct Matrix2x2 {
	float matrix[2][2];
};

struct Matrix3x3 {
	float matrix[3][3];
};

struct Matrix4x4 {
	float matrix[4][4];
};

struct Vector2Array {
	float vector2[2];
};

struct Vector2Float {
	float x;
	float y;
};

struct Vector3Array {
	float vector3[3];
};

struct Vector3Float {
	float x;
	float y;
	float z;
};

struct intPos {
	int x;
	int y;
};

struct MapChip {
	intPos LeftTop;
	intPos LeftBottom;
	intPos RightTop;
	intPos RightBottom;
};

struct Vertex {
	Vector2Float LeftTop;
	Vector2Float LeftBottom;
	Vector2Float RightTop;
	Vector2Float RightBottom;
	Vector2Float center;
	float width;
	float height;
};

struct Where {
	bool isX;
	bool isY;
};

struct Object {
	Vector2Array translate;
	Vector2Array scale;
	float theta;
	Vector2Array lt;
	Vector2Array lb;
	Vector2Array rt;
	Vector2Array rb;
	Vector2Array screenLt;
	Vector2Array screenLb;
	Vector2Array screenRt;
	Vector2Array screenRb;
	Matrix3x3 worldMatrix;
	Matrix3x3 wvpVpMatrix{};
};

struct CameraData {
	Vector2Array translate;
	Vector2Float dir;
	Vector2Float dirN;
	float velocity;
	float theta;
	Vector2Array scale;
	Matrix3x3 matrix;
	Matrix3x3 viewMatrix;
	Matrix3x3 orthographicMatrix;
	Matrix3x3 viewportMatrix;
};
