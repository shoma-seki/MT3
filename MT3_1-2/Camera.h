#pragma once
#include "Struct.h"
#include "Functions.h"

class Camera{
private:
	CameraData camera_;

public:
	Camera();
	~Camera();

	void Initialize();

	CameraData GetCamera();

	void Update(Vector2Array translate, Vector2Array shakePos);
};