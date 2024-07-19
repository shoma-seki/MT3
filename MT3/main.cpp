#include <Novice.h>
#include "MatrixFunc.h"
#include "Functions.h"
#define _USE_MATH_DEFINES
#include <math.h>
#include <time.h>
#include <stdlib.h>
#include "Camera3d.h"
#include "ImGuiManager.h"
#include "MyDraw.h"
#include "OperatorOverload.h"

const char kWindowTitle[] = "LC1A_17_セキ_ショウマ_タイトル";

// Windowsアプリでのエントリーポイント(main関数)
int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int) {

	// ライブラリの初期化
	Novice::Initialize(kWindowTitle, 1280, 720);

	// キー入力結果を受け取る箱
	char keys[256] = { 0 };
	char preKeys[256] = { 0 };
	srand(unsigned int(time(nullptr)));

	Camera3d* camera = new Camera3d({ 1.0f,1.0f,1.0f }, { 0.26f,0.0f,0.0f }, { 0.0f,1.9f,-6.49f });

	/*Spring spring{
		.anchor = {0.0f,1.0f,0.0f},
		.naturalLength = 0.7f,
		.stiffness = 100.0f,
		.dampingCoeffient = 2.0f
	};
*/

	float deltaTime = 1.0f / 60.0f;
	const Vector3Array kGravity{ 0.0f,-9.8f,0.0f };

	/*Vector3Array p{ 0,0.8f,0 };
	Vector3Array c{ 0,0,0 };

	float r = Length(c - p);

	float angularVelocity = 3.14f;
	float angle = 0.0f;*/

	bool isStart = false;

	/*Pendulum pendulum{
		.anchor = {0.0f,1.0f,0.0f},
		.length = 0.8f,
		.angle = 0.7f,
		.angularVelocity = 0.0f,
		.angularAcceleration = 0.0f
	};*/

	ConicalPendulum conicalPendulum;

	conicalPendulum = {
		.anchor = {0.0f,1.0f,0.0f},
		.length = 0.8f,
		.halfApexAngle = 0.7f,
		.angle = 0.0f,
		.angularVelocity = 0.0f
	};

	Ball ball{
		.position = {0.8f,0.2f,0.0f},
		.mass = 2.0f,
		.radius = 0.05f,
		.color = BLUE
	};

	/*Vector3Array translates[3] = {
		{0.2f,1.0f,0.0f},
		{0.4f,0.0f,0.0f},
		{0.3f,0.0f,0.0f},
	};

	Vector3Array rotates[3] = {
		{0.0f,0.0f,-6.8f},
		{0.0f,0.0f,-1.4f},
		{0.0f,0.0f,0.0f},
	};

	Vector3Array scales[3] = {
		{1.0f,1.0f,1.0f},
		{1.0f,1.0f,1.0f},
		{1.0f,1.0f,1.0f},
	};*/

	//Segment segment{ {-0.7f,0.3f,0.0f},{2.0f,-0.5f,0.0f} };
	/*Vector3Array point{ -1.5f,0.6f,0.6f };
	Vector3Array project{};
	Vector3Array closestPoint{};

	project = Project(Subtract(point, segment.origin), segment.diff);
	closestPoint = ClosestPoint(point, segment);

	Sphere pointSphere{ point,0.01f };
	Sphere closestPointSphere{ closestPoint,0.01f };*/

	/*Vector3Array v01 = Subtract(triangle.worldPos[1], triangle.worldPos[0]);
	Vector3Array v12 = Subtract(triangle.worldPos[2], triangle.worldPos[1]);
	Vector3Array n = Normalize(Cross(v01, v12));*/

	/*Vector3Array a{ 0.2f, 1.0f, 0.0f };
	Vector3Array b{ 2.4f, 3.1f, 1.2f };
	Vector3Array c = a + b;
	Vector3Array d = a - b;
	Vector3Array e = a * 2.4f;
	Vector3Array rotate{ 0.4f, 1.43f, -0.8f };
	Matrix4x4 rotateXMatrix = MakeRotateXMatrix(rotate.v[0]);
	Matrix4x4 rotateYMatrix = MakeRotateYMatrix(rotate.v[1]);
	Matrix4x4 rotateZMatrix = MakeRotateZMatrix(rotate.v[2]);
	Matrix4x4 rotateMatrix = rotateXMatrix * rotateYMatrix * rotateZMatrix;*/

	uint32_t color = 0xFFFFFFFF;

	// ウィンドウの×ボタンが押されるまでループ
	while (Novice::ProcessMessage() == 0) {
		// フレームの開始
		Novice::BeginFrame();

		// キー入力を受け取る
		memcpy(preKeys, keys, 256);
		Novice::GetHitKeyStateAll(keys);

		///
		/// ↓更新処理ここから
		///
		camera->Update(keys);
		/*Matrix4x4 startWorldMatrix = MakeAffineMatrix({ 1,1,1 }, { 0,0,0 }, segment.origin);
		Matrix4x4 endWorldMatrix = MakeAffineMatrix({ 1,1,1 }, { 0,0,0 }, Add(segment.origin, segment.diff));
		Vector3Array start = RenderingPipeline(Vector3Array{}, startWorldMatrix, camera->GetCamera());
		Vector3Array end = RenderingPipeline(Vector3Array{}, endWorldMatrix, camera->GetCamera());*/
		color = 0xFFFFFFFF;

		/*Matrix4x4 localS = MakeAffineMatrix(scales[0], rotates[0], translates[0]);
		Matrix4x4 localE = MakeAffineMatrix(scales[1], rotates[1], translates[1]);
		Matrix4x4 localH = MakeAffineMatrix(scales[2], rotates[2], translates[2]);

		Matrix4x4 worldS = localS;
		Matrix4x4 worldE = Multiply(localE, localS);
		Matrix4x4 worldH = Multiply(localH, Multiply(localE, localS));

		Vector3Array worldPS = Transform({ 0,0,0 }, worldS);
		Vector3Array worldPE = Transform({ 0,0,0 }, worldE);
		Vector3Array worldPH = Transform({ 0,0,0 }, worldH);*/

		/*Matrix4x4 rotateMatrix1 = Multiply(MakeRotateXMatrix(rotate1.v[0]), Multiply(MakeRotateYMatrix(rotate1.v[1]), MakeRotateZMatrix(rotate1.v[2])));

		obb1.orientations[0].v[0] = rotateMatrix1.matrixatrix[0][0];
		obb1.orientations[0].v[1] = rotateMatrix1.matrixatrix[0][1];
		obb1.orientations[0].v[2] = rotateMatrix1.matrixatrix[0][2];

		obb1.orientations[1].v[0] = rotateMatrix1.matrixatrix[1][0];
		obb1.orientations[1].v[1] = rotateMatrix1.matrixatrix[1][1];
		obb1.orientations[1].v[2] = rotateMatrix1.matrixatrix[1][2];

		obb1.orientations[2].v[0] = rotateMatrix1.matrixatrix[2][0];
		obb1.orientations[2].v[1] = rotateMatrix1.matrixatrix[2][1];
		obb1.orientations[2].v[2] = rotateMatrix1.matrixatrix[2][2];

		Matrix4x4 rotateMatrix2 = Multiply(MakeRotateXMatrix(rotate2.v[0]), Multiply(MakeRotateYMatrix(rotate2.v[1]), MakeRotateZMatrix(rotate2.v[2])));

		obb2.orientations[0].v[0] = rotateMatrix2.matrixatrix[0][0];
		obb2.orientations[0].v[1] = rotateMatrix2.matrixatrix[0][1];
		obb2.orientations[0].v[2] = rotateMatrix2.matrixatrix[0][2];

		obb2.orientations[1].v[0] = rotateMatrix2.matrixatrix[1][0];
		obb2.orientations[1].v[1] = rotateMatrix2.matrixatrix[1][1];
		obb2.orientations[1].v[2] = rotateMatrix2.matrixatrix[1][2];

		obb2.orientations[2].v[0] = rotateMatrix2.matrixatrix[2][0];
		obb2.orientations[2].v[1] = rotateMatrix2.matrixatrix[2][1];
		obb2.orientations[2].v[2] = rotateMatrix2.matrixatrix[2][2];*/

		/*if (isStart) {
			Vector3Array diff = ball.position - spring.anchor;
			float length = Length(diff);
			if (length != 0.0f) {
				Vector3Array direction = Normalize(diff);
				Vector3Array restPosition = spring.anchor + direction * spring.naturalLength;
				Vector3Array displacement = length * (ball.position - restPosition);
				Vector3Array restoringForce = -spring.stiffness * displacement;
				Vector3Array dampringForce = -spring.dampingCoeffient * ball.velocity;
				Vector3Array force = restoringForce + dampringForce;
				ball.acceleration = force / ball.mass + kGravity;
			}

			ball.velocity += (ball.acceleration ) * deltaTime;
			ball.position += ball.velocity * deltaTime;
		}*/

		Vector3Array p = { 0,0,0 };
		if (isStart) {
			/*pendulum.angularAcceleration = -(9.8f / pendulum.length) * std::sin(pendulum.angle);
			pendulum.angularVelocity += pendulum.angularAcceleration * deltaTime;
			pendulum.angle += pendulum.angularVelocity * deltaTime;
			p.v[0] = pendulum.anchor.v[0] + std::sin(pendulum.angle) * pendulum.length;
			p.v[1] = pendulum.anchor.v[1] - std::cos(pendulum.angle) * pendulum.length;
			p.v[2] = pendulum.anchor.v[2];*/

			conicalPendulum.angularVelocity = std::sqrtf(9.8f / (conicalPendulum.length * std::cosf(conicalPendulum.halfApexAngle)));
			conicalPendulum.angle += conicalPendulum.angularVelocity * deltaTime;

			float radius = std::sin(conicalPendulum.halfApexAngle) * conicalPendulum.length;
			float height = std::cos(conicalPendulum.halfApexAngle) * conicalPendulum.length;
			ball.position.v[0] = conicalPendulum.anchor.v[0] + std::cosf(conicalPendulum.angle) * radius;
			ball.position.v[1] = conicalPendulum.anchor.v[1] - height;
			ball.position.v[2] = conicalPendulum.anchor.v[2] + std::sinf(conicalPendulum.angle) * radius;
			p = ball.position;
		}
		/*if (isStart) {
			Vector3Array v;
			float acceleration = -std::powf(angularVelocity, 2) * r;
			v.v[0] = -r * angularVelocity * std::sin(angle);
			v.v[1] = r * angularVelocity * std::cos(angle);

			p += v * acceleration;
			p.v[2] = 0;
		}*/




		///
		/// ↑更新処理ここまで
		///

		///
		/// ↓描画処理ここから
		///
		DrawGrid(camera->GetCamera());

		DrawSphere(Sphere{ .center = p,.radius = 0.05f }, camera->GetCamera(), 0x0000FFFF, 20);
		DrawLine(conicalPendulum.anchor, p, camera->GetCamera(), WHITE);

		/*DrawSphere(Sphere{ .center = worldPS,.radius = 0.1f }, camera->GetCamera(), 0xFF0000FF, 10);
		DrawSphere(Sphere{ .center = worldPE,.radius = 0.1f }, camera->GetCamera(), 0x00FF00FF, 10);
		DrawSphere(Sphere{ .center = worldPH,.radius = 0.1f }, camera->GetCamera(), 0x0000FFFF, 10);

		DrawLine(worldPS, worldPE, camera->GetCamera(), WHITE);
		DrawLine(worldPE, worldPH, camera->GetCamera(), WHITE);*/

		camera->DebugDraw();
		//Novice::DrawLine(int(start.v[0]), int(start.v[1]), int(end.v[0]), int(end.v[1]), color);

		//imgui
		ImGui::Begin("Window");
		if (ImGui::Button("Start")) {
			isStart = true;
		}
		if (ImGui::Button("Stop")) {
			isStart = false;
		}
		ImGui::DragFloat3("p", p.v);
		/*ImGui::DragFloat3("translates0", translates[0].v, 0.1f);
		ImGui::DragFloat3("rotates0", rotates[0].v, 0.1f);
		ImGui::DragFloat3("scales0", scales[0].v, 0.1f);
		ImGui::DragFloat3("translates1", translates[1].v, 0.1f);
		ImGui::DragFloat3("rotates1", rotates[1].v, 0.1f);
		ImGui::DragFloat3("scales1", scales[1].v, 0.1f);
		ImGui::DragFloat3("translates2", translates[2].v, 0.1f);
		ImGui::DragFloat3("rotates2", rotates[2].v, 0.1f);
		ImGui::DragFloat3("scales2", scales[2].v, 0.1f);*/
		/*ImGui::Text("c:%f, %f, %f", c.v[0], c.v[1], c.v[2]);
		ImGui::Text("d:%f, %f, %f", d.v[0], d.v[1], d.v[2]);
		ImGui::Text("e: %f %f %f", e.v[0], e.v[1], e.v[2]);
		ImGui::Text(
			"matrix:\n%f, %f, %f, %f\n%f, %f, %f, %f\n%f, %f, %f, %f\n%f, %f, %f, %f\n",
			rotateMatrix.matrix[0][0], rotateMatrix.matrix[0][1], rotateMatrix.matrix[0][2],
			rotateMatrix.matrix[0][3], rotateMatrix.matrix[1][0], rotateMatrix.matrix[1][1],
			rotateMatrix.matrix[1][2], rotateMatrix.matrix[1][3], rotateMatrix.matrix[2][0],
			rotateMatrix.matrix[2][1], rotateMatrix.matrix[2][2], rotateMatrix.matrix[2][3],
			rotateMatrix.matrix[3][0], rotateMatrix.matrix[3][1], rotateMatrix.matrix[3][2],
			rotateMatrix.matrix[3][3]);*/
		ImGui::End();

		///
		/// ↑描画処理ここまで
		///

		// フレームの終了
		Novice::EndFrame();

		// ESCキーが押されたらループを抜ける
		if (preKeys[DIK_ESCAPE] == 0 && keys[DIK_ESCAPE] != 0) {
			break;
		}
	}

	// ライブラリの終了
	Novice::Finalize();
	return 0;
}
