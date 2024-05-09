#include "MyDraw.h"

void MyDrawTriangle(const Vector3Array& screenPos1, const Vector3Array& screenPos2, const Vector3Array& screenPos3, const unsigned int color){
	Novice::DrawTriangle(int(screenPos1.vector3[0]), int(screenPos1.vector3[1]),
		int(screenPos2.vector3[0]), int(screenPos2.vector3[1]),
		int(screenPos3.vector3[0]), int(screenPos3.vector3[1]),
		color, kFillModeSolid
		);
}
