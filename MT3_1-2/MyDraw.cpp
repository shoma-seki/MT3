#include "MyDraw.h"

void MyDrawTriangle(const Vector3Array& screenPos1, const Vector3Array& screenPos2, const Vector3Array& screenPos3, const unsigned int color){
	Novice::DrawTriangle(int(screenPos1.vector3[0]), int(screenPos1.vector3[1]),
		int(screenPos2.vector3[0]), int(screenPos2.vector3[1]),
		int(screenPos3.vector3[0]), int(screenPos3.vector3[1]),
		color, kFillModeSolid
		);
}

void MyDrawQuad(const Object& obj, Vector2Array imageSize, int GH, unsigned int color) {
	Novice::DrawQuad(int(obj.screenLt.vector2[0]), int(obj.screenLt.vector2[1]),
		int(obj.screenRt.vector2[0]), int(obj.screenRt.vector2[1]),
		int(obj.screenLb.vector2[0]), int(obj.screenLb.vector2[1]),
		int(obj.screenRb.vector2[0]), int(obj.screenRb.vector2[1]),
		0, 0, int(imageSize.vector2[0]), int(imageSize.vector2[1]), GH, color);
}

void MyDrawQuadR(const Object& obj, Vector2Array random, Vector2Array imageSize, int GH, unsigned int color) {
	Novice::DrawQuad(int(obj.screenLt.vector2[0] + random.vector2[0]), int(obj.screenLt.vector2[1] + random.vector2[1]),
		int(obj.screenRt.vector2[0] + random.vector2[0]), int(obj.screenRt.vector2[1] + random.vector2[1]),
		int(obj.screenLb.vector2[0] + random.vector2[0]), int(obj.screenLb.vector2[1] + random.vector2[1]),
		int(obj.screenRb.vector2[0] + random.vector2[0]), int(obj.screenRb.vector2[1] + random.vector2[1]),
		0, 0, int(imageSize.vector2[0]), int(imageSize.vector2[1]), GH, color);
}
