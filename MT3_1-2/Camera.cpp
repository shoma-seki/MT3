#include "Camera.h"

Camera::Camera() {
	camera_.orthographicMatrix = MakeOrthographicMatrix(-1280, 720, 1280, -720);
	camera_.viewportMatrix = MakeViewportMatrix(0, 0, 1280, 720);
	camera_.translate = { 1,1 };
	camera_.scale = { 1,1 };
	camera_.theta = 0;
}

Camera::~Camera() {}

void Camera::Initialize(){
	camera_.orthographicMatrix = MakeOrthographicMatrix(-1280, 720, 1280, -720);
	camera_.viewportMatrix = MakeViewportMatrix(0, 0, 1280, 720);
	camera_.translate = { 1,1 };
	camera_.scale = { 1,1 };
	camera_.theta = 0;
}

void Camera::Update(Vector2Array translate,Vector2Array shakePos) {
	camera_.translate = translate;
	camera_.translate.vector2[0] += shakePos.vector2[0];
	camera_.translate.vector2[1] += shakePos.vector2[1];
	camera_.matrix = MakeAffineMatrix(camera_.scale, camera_.theta, camera_.translate);
	camera_.viewMatrix = inverse(camera_.matrix);
}

CameraData Camera::GetCamera() {
	return camera_;
}