#pragma once

#include "Novice.h"
#include "Struct.h"

void MyDrawTriangle(const Vector3Array& screenPos1, const Vector3Array& screenPos2, const Vector3Array& screenPos3, const unsigned int color);
void MyDrawQuad(const Object& obj, Vector2Array imageSize, int GH, unsigned int color);
void MyDrawQuadR(const Object& obj, Vector2Array random, Vector2Array imageSize, int GH, unsigned int color);