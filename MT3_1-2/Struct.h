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

struct Point3d{
	Vector3Array local;
	Vector3Array screen;
};

struct Triangle {
	Point3d pos[3];
	Vector3Array worldPos[3];
	Vector3Array translate;
	float speed;
	Vector3Array dir;
	Vector3Array velocity;
	Vector3Array rotate;
	Vector3Array scale;
	Matrix4x4 worldMatrix;
};

struct CameraData {
	Vector2Array translate;
	Vector2Float dir;
	Vector2Float dirN;
	float speed;
	Vector2Float velocity;
	float theta;
	Vector2Array scale;
	Matrix3x3 matrix;
	Matrix3x3 viewMatrix;
	Matrix3x3 orthographicMatrix;
	Matrix3x3 viewportMatrix;
};

struct Camera3dData {
	Vector3Array translate;
	Vector3Array rotate;
	Vector3Array scale;
	Vector3Float dir;
	Vector3Float dirN;
	float speed;
	Vector3Float velocity;
	Matrix4x4 matrix;
	Matrix4x4 viewMatrix;
	Matrix4x4 projectionMatrix;
	Matrix4x4 viewportMatrix;
};

struct Sphere {
	Vector3Array center;
	float radius;
};