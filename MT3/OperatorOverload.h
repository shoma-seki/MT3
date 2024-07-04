#pragma once
#include "Struct.h"
#include "Functions.h"


Vector3Array operator+(const Vector3Array& v1, const Vector3Array& v2) { return Add(v1, v2); }
Vector3Array operator-(const Vector3Array& v1, const Vector3Array& v2) { return Subtract(v1, v2); }
Vector3Array operator*(float s, const Vector3Array& v) { return Multiply(s, v); }
Vector3Array operator*(const Vector3Array& v, float s) { return Multiply(s, v); }
Vector3Array operator/(const Vector3Array& v, float s) { return Multiply(1.0f / s, v); }
Vector3Array operator-(const Vector3Array& v) { return { -v.v[0],-v.v[1],-v.v[2] }; }
Vector3Array operator+(const Vector3Array& v) { return v; }

Vector3Float operator+(const Vector3Float& v1, const Vector3Float& v2) { return Add(v1, v2); }
Vector3Float operator-(const Vector3Float& v1, const Vector3Float& v2) { return Subtract(v1, v2); }
Vector3Float operator*(float s, const Vector3Float& v) { return Multiply(s, v); }
Vector3Float operator* (const Vector3Float& v, float s) { return s * v; }
Vector3Float operator/(const Vector3Float& v, float s) { return Multiply(1.0f / s, v); }
Matrix4x4 operator+(const Matrix4x4& m1, const Matrix4x4& m2) { return Add(m1, m2); }
Matrix4x4 operator-(const Matrix4x4& m1, const Matrix4x4& m2) { return Subtract(m1, m2); }
Matrix4x4 operator*(const Matrix4x4& m1, const Matrix4x4& m2) { return Multiply(m1, m2); }