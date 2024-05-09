#pragma once
#include "MatrixFunc.h"
#include "Struct.h"
#include "ImGuiManager.h"

class Camera3d{
private:
	Camera3dData camera_;

public:
	Camera3d(Vector3Array scale, Vector3Array rotate, Vector3Array translate) { Initialize(scale, rotate, translate); };
	~Camera3d() {};

	void Initialize(Vector3Array scale, Vector3Array rotate, Vector3Array translate);

	void Update(char keys[]);

	void DebugDraw();

	Camera3dData GetCamera() { return camera_; };
};