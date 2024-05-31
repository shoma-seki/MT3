#include "MatrixFunc.h"

Matrix4x4 Add(const Matrix4x4& m1, const Matrix4x4& m2) {
	Matrix4x4 result{};
	for (int i = 0; i < 4; ++i) {
		for (int j = 0; j < 4; ++j) {
			result.matrix[i][j] = m1.matrix[i][j] + m2.matrix[i][j];
		}
	}
	return result;
}

Matrix4x4 Subtract(const Matrix4x4& m1, const Matrix4x4& m2) {
	Matrix4x4 result{};
	for (int i = 0; i < 4; ++i) {
		for (int j = 0; j < 4; ++j) {
			result.matrix[i][j] = m1.matrix[i][j] - m2.matrix[i][j];
		}
	}
	return result;
}

Matrix4x4 Multiply(const Matrix4x4& m1, const Matrix4x4& m2) {
	Matrix4x4 result{};

	for (int i = 0; i < 4; ++i) {
		for (int j = 0; j < 4; ++j) {
			result.matrix[i][j] = 0.0f;
			for (int k = 0; k < 4; ++k) {
				result.matrix[i][j] += m1.matrix[i][k] * m2.matrix[k][j];
			}
		}
	}

	return result;
}

Matrix4x4 inverse(const Matrix4x4& matrix) {
	Matrix4x4 a = matrix;
	Matrix4x4 result{};

	float buf2 = 0.0f;
	int n = 4;
	int i = 0;
	int j = 0;
	int k = 0;


	for (i = 0; i < n; i++) {
		for (j = 0; j < n; j++) {
			if (i == j) {
				result.matrix[i][j] = 1.0f;
			}
			else {
				result.matrix[i][j] = 0.0f;
			}
		}
	}

	for (i = 0; i < n; i++) {
		buf2 = 1 / a.matrix[i][i];
		for (j = 0; j < n; j++) {
			a.matrix[i][j] *= buf2;
			result.matrix[i][j] *= buf2;
		}
		for (j = 0; j < n; j++) {
			if (i != j) {
				buf2 = a.matrix[j][i];
				for (k = 0; k < n; k++) {
					a.matrix[j][k] -= a.matrix[i][k] * buf2;
					result.matrix[j][k] -= result.matrix[i][k] * buf2;
				}
			}
		}
	}

	return result;
}
Matrix4x4 Transpose(const Matrix4x4& m) {
	Matrix4x4 result{};

	for (int i = 0; i < 4; ++i) {
		for (int j = 0; j < 4; ++j) {
			result.matrix[i][j] = m.matrix[j][i];
		}
	}

	return result;
}

Matrix4x4 MakeIdentityMatrix() {
	Matrix4x4 result{};

	for (int i = 0; i < 4; ++i) {
		for (int j = 0; j < 4; ++j) {
			if (i == j) {
				result.matrix[i][j] = 1.0f;
			}
		}
	}

	return result;
}

Matrix4x4 MakeTranslateMatrix(const Vector3Array& translate) {
	Matrix4x4 result = {
		1.0f, 0.0f, 0.0f, 0.0f,
		0.0f, 1.0f, 0.0f, 0.0f,
		0.0f, 0.0f, 1.0f, 0.0f,
		translate.v[0], translate.v[1], translate.v[2], 1.0f
	};

	return result;
}

Matrix4x4 MakeScaleMatrix(const Vector3Array& scale) {
	Matrix4x4 result = {
		scale.v[0], 0.0f, 0.0f, 0.0f,
		0.0f, scale.v[1], 0.0f, 0.0f,
		0.0f, 0.0f, scale.v[2], 0.0f,
		0.0f, 0.0f, 0.0f, 1.0f
	};

	return result;
}

Matrix4x4 MakeRotateXMatrix(float radian) {
	Matrix4x4 result{};

	result = {
				1,0,0,0,
				0,std::cos(radian),std::sin(radian),0,
				0,-std::sin(radian),std::cos(radian),0,
				0,0,0,1
	};

	return result;
}

Matrix4x4 MakeRotateYMatrix(float radian) {
	Matrix4x4 result{};

	result = {
				std::cos(radian),0,-std::sin(radian),0,
				0,1,0,0,
				std::sin(radian),0,std::cos(radian),0,
				0,0,0,1
	};

	return result;
}

Matrix4x4 MakeRotateZMatrix(float radian) {
	Matrix4x4 result{};

	result = {
				std::cos(radian),std::sin(radian),0,0,
				-std::sin(radian),std::cos(radian),0,0,
				0,0,1,0,
				0,0,0,1
	};

	return result;
}

Matrix4x4 MakeAffineMatrix(const Vector3Array& scale, const Vector3Array& rotate, const Vector3Array& translate) {
	Matrix4x4 result{};
	Matrix4x4 rotateXMatrix = MakeRotateXMatrix(rotate.v[0]);
	Matrix4x4 rotateYMatrix = MakeRotateYMatrix(rotate.v[1]);
	Matrix4x4 rotateZMatrix = MakeRotateZMatrix(rotate.v[2]);
	Matrix4x4 rotateXYZ = Multiply(rotateXMatrix, Multiply(rotateYMatrix, rotateZMatrix));

	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 4; j++) {
			if (j == 3) {
				result.matrix[i][j] = 0.0f;
			}
			else {
				result.matrix[i][j] = scale.v[i] * rotateXYZ.matrix[i][j];
			}
		}
	}
	for (int i = 0; i < 3; i++) {
		result.matrix[3][i] = translate.v[i];
	}
	result.matrix[3][3] = 1.0f;

	return result;
}

Vector3Array Transform(const Vector3Array& vector, const Matrix4x4& matrix) {
	Vector3Array result{};
	for (int i = 0; i < 3; i++) {
		result.v[i] = vector.v[0] * matrix.matrix[0][i] +
			vector.v[1] * matrix.matrix[1][i] + vector.v[2] * matrix.matrix[2][i] + matrix.matrix[3][i];
	}
	float w = vector.v[0] * matrix.matrix[0][3] +
		vector.v[1] * matrix.matrix[1][3] + vector.v[2] * matrix.matrix[2][3] + matrix.matrix[3][3];
	assert(w != 0.0f);
	for (int i = 0; i < 3; i++) {
		result.v[i] /= w;
	}
	return result;
}

Matrix4x4 MakePerspectiveFovMatrix(float fovY, float aspectRatio, float nearClip, float farClip) {
	Matrix4x4 result{};

	result.matrix[0][0] = (1.0f / aspectRatio) * (1.0f / std::tan(fovY / 2));
	result.matrix[0][1] = 0.0f;
	result.matrix[0][2] = 0.0f;
	result.matrix[0][3] = 0.0f;
	result.matrix[1][0] = 0.0f;
	result.matrix[1][1] = 1.0f / std::tan(fovY / 2);
	result.matrix[1][2] = 0.0f;
	result.matrix[1][3] = 0.0f;
	result.matrix[2][0] = 0.0f;
	result.matrix[2][1] = 0.0f;
	result.matrix[2][2] = farClip / (farClip - nearClip);
	result.matrix[2][3] = 1.0f;
	result.matrix[3][0] = 0.0f;
	result.matrix[3][1] = 0.0f;
	result.matrix[3][2] = -nearClip * farClip / (farClip - nearClip);
	result.matrix[3][3] = 0.0f;

	return result;
}

Matrix4x4 MakeOrthographicMatrix(float left, float top, float right, float bottom, float nearClip, float farClip) {
	Matrix4x4 result{};

	result.matrix[0][0] = 2.0f / (right - left);
	result.matrix[0][1] = 0.0f;
	result.matrix[0][2] = 0.0f;
	result.matrix[0][3] = 0.0f;
	result.matrix[1][0] = 0.0f;
	result.matrix[1][1] = 2.0f / (top - bottom);
	result.matrix[1][2] = 0.0f;
	result.matrix[1][3] = 0.0f;
	result.matrix[2][0] = 0.0f;
	result.matrix[2][1] = 0.0f;
	result.matrix[2][2] = 1.0f / (farClip - nearClip);
	result.matrix[2][3] = 0.0f;
	result.matrix[3][0] = (left + right) / (left - right);
	result.matrix[3][1] = (top + bottom) / (bottom - top);
	result.matrix[3][2] = nearClip / (nearClip - farClip);
	result.matrix[3][3] = 1.0f;

	return result;
}

Matrix4x4 MakeViewportMatrix(float left, float top, float width, float height, float minDepth, float maxDepth) {
	Matrix4x4 result{};

	result.matrix[0][0] = width / 2.0f;
	result.matrix[0][1] = 0.0f;
	result.matrix[0][2] = 0.0f;
	result.matrix[0][3] = 0.0f;
	result.matrix[1][0] = 0.0f;
	result.matrix[1][1] = -(height / 2.0f);
	result.matrix[1][2] = 0.0f;
	result.matrix[1][3] = 0.0f;
	result.matrix[2][0] = 0.0f;
	result.matrix[2][1] = 0.0f;
	result.matrix[2][2] = maxDepth - minDepth;
	result.matrix[2][3] = 0.0f;
	result.matrix[3][0] = left + width / 2.0f;
	result.matrix[3][1] = top + height / 2.0f;
	result.matrix[3][2] = minDepth;
	result.matrix[3][3] = 1.0f;

	return result;
}

Vector3Array RenderingPipeline(const Vector3Array& local, const Matrix4x4& worldMatrix, const Camera3dData& camera) {
	Vector3Array screen{};
	Matrix4x4 worldViewProjectionMatrix = Multiply(worldMatrix, Multiply(camera.viewMatrix, camera.projectionMatrix));
	Vector3Array ndc = Transform(local, worldViewProjectionMatrix);
	screen = Transform(ndc, camera.viewportMatrix);
	return screen;
}

Vector3Array RenderingPipeline(const Vector3Array& local, const Vector3Array& translate, const Camera3dData& camera)
{
	Matrix4x4 worldMatrix = MakeAffineMatrix({ 1,1,1 }, { 0,0,0 }, translate);
	Vector3Array result = RenderingPipeline(local, worldMatrix, camera);
	return result;
}

void RenderingPipeline(Triangle& triangle, const Camera3dData& camera)
{
	triangle.worldMatrix = MakeAffineMatrix(triangle.scale, triangle.rotate, triangle.translate);
	for (int i = 0; i < 3; i++) {
		triangle.pos[i].screen = RenderingPipeline(triangle.pos[i].local, triangle.worldMatrix, camera);
		Matrix4x4 worldViewProjectionMatrix = Multiply(triangle.worldMatrix, Multiply(camera.viewMatrix, camera.projectionMatrix));
		triangle.worldPos[i] = Transform(triangle.pos[i].local, triangle.worldMatrix);
		Novice::ScreenPrintf(0, 30 + 15 * i, "%f", triangle.worldPos[i].v[0]);
	}
}

void DrawSphere(const Sphere& sphere, const Camera3dData& camera, uint32_t color, uint32_t subdivision) {
	const uint32_t kSubdivision = subdivision;
	const float kLonEvery = float(2.0 * M_PI / kSubdivision);//phi
	const float kLatEvery = float(2.0 * M_PI / kSubdivision);//theta
	const float thetaD = float(M_PI) / float(kSubdivision);
	const float phiD = float(2.0 * M_PI) / float(kSubdivision);

	for (uint32_t latIndex = 0; latIndex < kSubdivision; ++latIndex) {
		float lat = float(-M_PI / 2.0) + kLatEvery * float(latIndex);
		for (uint32_t lonIndex = 0; lonIndex < kSubdivision; ++lonIndex) {
			float lon = float(lonIndex) * kLonEvery;
			Vector3Array worldA{};
			Vector3Array worldB{};
			Vector3Array worldC{};
			Vector3Array screenA{};
			Vector3Array screenB{};
			Vector3Array screenC{};

			//ワールド座標系でのa,b,cを求める
			worldA.v[0] = sphere.radius * (std::cos(lat) * cos(lon)) + sphere.center.v[0];
			worldA.v[1] = sphere.radius * (std::sin(lat)) + sphere.center.v[1];
			worldA.v[2] = sphere.radius * (std::cos(lat)) * sin(lon) + sphere.center.v[2];

			worldB.v[0] = sphere.radius * (std::cos(lat + thetaD) * cos(lon)) + sphere.center.v[0];
			worldB.v[1] = sphere.radius * (std::sin(lat + thetaD)) + sphere.center.v[1];
			worldB.v[2] = sphere.radius * (std::cos(lat + thetaD) * sin(lon)) + sphere.center.v[2];

			worldC.v[0] = sphere.radius * (std::cos(lat) * cos(lon + phiD)) + sphere.center.v[0];
			worldC.v[1] = sphere.radius * (std::sin(lat)) + sphere.center.v[1];
			worldC.v[2] = sphere.radius * (std::cos(lat) * sin(lon + phiD)) + sphere.center.v[2];

			//ワールドマトリックス
			Matrix4x4 aWorldMatrix = MakeAffineMatrix({ 1,1,1 }, { 0,0,0 }, worldA);
			Matrix4x4 bWorldMatrix = MakeAffineMatrix({ 1,1,1 }, { 0,0,0 }, worldB);
			Matrix4x4 cWorldMatrix = MakeAffineMatrix({ 1,1,1 }, { 0,0,0 }, worldC);

			//スクリーンに変換
			screenA = RenderingPipeline({ 0,0,0 }, aWorldMatrix, camera);
			screenB = RenderingPipeline({ 0,0,0 }, bWorldMatrix, camera);
			screenC = RenderingPipeline({ 0,0,0 }, cWorldMatrix, camera);

			//線を引く
			Novice::DrawLine(int(screenA.v[0]), int(screenA.v[1]), int(screenB.v[0]), int(screenB.v[1]), color);
			Novice::DrawLine(int(screenA.v[0]), int(screenA.v[1]), int(screenC.v[0]), int(screenC.v[1]), color);
		}
	}
}

void DrawGrid(const Camera3dData& camera) {
	const float kGridHalfWidth = 2.0f;
	const uint32_t kSubdivision = 10;
	const float kGridEvery = (kGridHalfWidth * 2.0f) / float(kSubdivision);

	Vector3Array lineStartWorld = {};
	Vector3Array lineEndWorld = {};
	Matrix4x4 lineWorldMatrix = {};
	Vector3Array lineStartScreen = {};
	Vector3Array lineEndScreen = {};

	static Vector3Array translate = {};

	for (uint32_t xIndex = 0; xIndex <= kSubdivision; ++xIndex) {
		lineStartWorld.v[0] = xIndex * (kGridHalfWidth * 0.2f);
		lineStartWorld.v[2] = 0.0f;
		lineEndWorld.v[0] = lineStartWorld.v[0];
		lineEndWorld.v[2] = kGridEvery * float(kSubdivision);

		lineStartWorld.v[0] -= kGridEvery * float(kSubdivision / 2);
		lineStartWorld.v[2] -= kGridEvery * float(kSubdivision / 2);
		lineEndWorld.v[0] -= kGridEvery * float(kSubdivision / 2);
		lineEndWorld.v[2] -= kGridEvery * float(kSubdivision / 2);

		lineWorldMatrix = MakeAffineMatrix({ 1,1,1 }, { 0,0,0 }, translate);
		lineStartScreen = RenderingPipeline(lineStartWorld, lineWorldMatrix, camera);
		lineEndScreen = RenderingPipeline(lineEndWorld, lineWorldMatrix, camera);

		if (xIndex != kSubdivision / 2) {
			Novice::DrawLine(int(lineStartScreen.v[0]), int(lineStartScreen.v[1]),
				int(lineEndScreen.v[0]), int(lineEndScreen.v[1]),
				0xAAAAAAFF);
		}
		else {
			Novice::DrawLine(int(lineStartScreen.v[0]), int(lineStartScreen.v[1]),
				int(lineEndScreen.v[0]), int(lineEndScreen.v[1]),
				0x111111FF);
		}
	}

	for (uint32_t zIndex = 0; zIndex <= kSubdivision; ++zIndex) {
		lineStartWorld.v[0] = 0.0f;
		lineStartWorld.v[2] = zIndex * (kGridHalfWidth * 0.2f);
		lineEndWorld.v[0] = kGridEvery * float(kSubdivision);
		lineEndWorld.v[2] = lineStartWorld.v[2];

		lineStartWorld.v[0] -= kGridEvery * float(kSubdivision / 2);
		lineStartWorld.v[2] -= kGridEvery * float(kSubdivision / 2);
		lineEndWorld.v[0] -= kGridEvery * float(kSubdivision / 2);
		lineEndWorld.v[2] -= kGridEvery * float(kSubdivision / 2);

		lineWorldMatrix = MakeAffineMatrix({ 1,1,1 }, { 0,0,0 }, translate);
		lineStartScreen = RenderingPipeline(lineStartWorld, lineWorldMatrix, camera);
		lineEndScreen = RenderingPipeline(lineEndWorld, lineWorldMatrix, camera);

		if (zIndex != kSubdivision / 2) {
			Novice::DrawLine(int(lineStartScreen.v[0]), int(lineStartScreen.v[1]),
				int(lineEndScreen.v[0]), int(lineEndScreen.v[1]),
				0xAAAAAAFF);
		}
		else {
			Novice::DrawLine(int(lineStartScreen.v[0]), int(lineStartScreen.v[1]),
				int(lineEndScreen.v[0]), int(lineEndScreen.v[1]),
				0x111111FF);
		}
	}

	ImGui::Begin("Grid");

	ImGui::SliderFloat3("translate", translate.v, -10.0f, 10.0f);

	ImGui::End();
}

void DrawLine(const Camera3dData& camera) {
	Vector3Array lineStartWorld = {};
	Vector3Array lineEndWorld = {};
	Matrix4x4 lineWorldMatrix = {};
	Vector3Array lineStartScreen = {};
	Vector3Array lineEndScreen = {};

	lineWorldMatrix = MakeAffineMatrix({ 1,1,1 }, { 0,0,0 }, { 0.0f,0.0f,0.0f });

	lineStartWorld.v[0] = -100;
	lineEndWorld.v[0] = 100;

	lineStartScreen = RenderingPipeline(lineStartWorld, lineWorldMatrix, camera);
	lineEndScreen = RenderingPipeline(lineEndWorld, lineWorldMatrix, camera);
	Novice::DrawLine(int(lineStartScreen.v[0]), int(lineStartScreen.v[1]),
		int(lineEndScreen.v[0]), int(lineEndScreen.v[1]),
		RED);

	lineStartWorld.v[0] = 0;
	lineEndWorld.v[0] = 0;
	lineStartWorld.v[1] = -100;
	lineEndWorld.v[1] = 100;

	lineStartScreen = RenderingPipeline(lineStartWorld, lineWorldMatrix, camera);
	lineEndScreen = RenderingPipeline(lineEndWorld, lineWorldMatrix, camera);
	Novice::DrawLine(int(lineStartScreen.v[0]), int(lineStartScreen.v[1]),
		int(lineEndScreen.v[0]), int(lineEndScreen.v[1]),
		RED);

	lineStartWorld.v[0] = 0;
	lineEndWorld.v[0] = 0;
	lineStartWorld.v[1] = 0;
	lineEndWorld.v[1] = 0;
	lineStartWorld.v[2] = -100;
	lineEndWorld.v[2] = 100;

	lineStartScreen = RenderingPipeline(lineStartWorld, lineWorldMatrix, camera);
	lineEndScreen = RenderingPipeline(lineEndWorld, lineWorldMatrix, camera);
	Novice::DrawLine(int(lineStartScreen.v[0]), int(lineStartScreen.v[1]),
		int(lineEndScreen.v[0]), int(lineEndScreen.v[1]),
		RED);
}

void DrawLine(const Vector3Array& p1, const Vector3Array& p2, const Camera3dData& camera, uint32_t color)
{
	Vector3Array screenP1 = RenderingPipeline({ 0,0,0 }, p1, camera);
	Vector3Array screenP2 = RenderingPipeline({ 0,0,0 }, p2, camera);
	Novice::DrawLine(int(screenP1.v[0]), int(screenP1.v[1]), int(screenP2.v[0]), int(screenP2.v[1]), color);
}

void DrawAABB(const AABB& aabb, const Camera3dData& camera, uint32_t color)
{
	Vector3Array point[8] = {};

	point[0] = aabb.min;
	point[7] = aabb.max;

	point[1].v[0] = aabb.min.v[0];
	point[1].v[1] = aabb.min.v[1];
	point[1].v[2] = aabb.max.v[2];

	point[2].v[0] = aabb.min.v[0];
	point[2].v[1] = aabb.max.v[1];
	point[2].v[2] = aabb.min.v[2];

	point[3].v[0] = aabb.min.v[0];
	point[3].v[1] = aabb.max.v[1];
	point[3].v[2] = aabb.max.v[2];

	point[4].v[0] = aabb.max.v[0];
	point[4].v[1] = aabb.min.v[1];
	point[4].v[2] = aabb.min.v[2];

	point[5].v[0] = aabb.max.v[0];
	point[5].v[1] = aabb.min.v[1];
	point[5].v[2] = aabb.max.v[2];

	point[6].v[0] = aabb.max.v[0];
	point[6].v[1] = aabb.max.v[1];
	point[6].v[2] = aabb.min.v[2];

	DrawLine(point[0], point[1], camera, color);
	DrawLine(point[1], point[3], camera, color);
	DrawLine(point[3], point[2], camera, color);
	DrawLine(point[0], point[2], camera, color);

	DrawLine(point[4], point[5], camera, color);
	DrawLine(point[5], point[7], camera, color);
	DrawLine(point[7], point[6], camera, color);
	DrawLine(point[4], point[6], camera, color);

	DrawLine(point[0], point[4], camera, color);
	DrawLine(point[1], point[5], camera, color);
	DrawLine(point[2], point[6], camera, color);
	DrawLine(point[3], point[7], camera, color);

	for (int i = 0; i < 8; i++) {
		point[i] = RenderingPipeline({ 0,0,0 }, point[i], camera);
		Novice::ScreenPrintf(int(point[i].v[0]), int(point[i].v[1]), "%d", i);
	}
}
