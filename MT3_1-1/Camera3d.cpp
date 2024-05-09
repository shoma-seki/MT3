#include "Camera3d.h"

void Camera3d::Initialize(Vector3Array scale, Vector3Array rotate, Vector3Array translate) {
	camera_.translate = translate;
	camera_.rotate = rotate;
	camera_.scale = scale;

	camera_.matrix = MakeAffineMatrix(camera_.scale, camera_.rotate, camera_.translate);
	camera_.viewMatrix = inverse(camera_.matrix);
	camera_.projectionMatrix = MakePerspectiveFovMatrix(0.45f, 1280.0f / 720.0f, 0.1f, 100.0f);
	camera_.viewportMatrix = MakeViewportMatrix(0, 0, 1280.0f, 720.0f, 0.0f, 1.0f);
}

void Camera3d::Update(char keys[]) {
	camera_.matrix = MakeAffineMatrix(camera_.scale, camera_.rotate, camera_.translate);
	camera_.viewMatrix = inverse(camera_.matrix);
	keys;
	if (keys[DIK_UP]) {
		camera_.translate.vector3[2] += 2;
	}
	if (keys[DIK_DOWN]) {
		camera_.translate.vector3[2] -= 2;
	}
	if (keys[DIK_LEFT]) {
		camera_.translate.vector3[0] -= 2;
	}
	if (keys[DIK_RIGHT]) {
		camera_.translate.vector3[0] += 2;
	}

	Novice::ScreenPrintf(0, 100, "%f,%f", camera_.translate.vector3[0], camera_.translate.vector3[2]);
}
