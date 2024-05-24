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
}

void Camera3d::DebugDraw() {
	ImGui::Begin("window");

	ImGui::DragFloat3("scale", &camera_.scale.v[0], 0.1f);
	ImGui::DragFloat3("rotate", &camera_.rotate.v[0], 0.01f);
	ImGui::DragFloat3("translate", &camera_.translate.v[0], 0.1f);

	ImGui::End();
}
