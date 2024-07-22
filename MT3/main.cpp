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

	//ConicalPendulum conicalPendulum;

	//conicalPendulum = {
	//	.anchor = {0.0f,1.0f,0.0f},
	//	.length = 0.8f,
	//	.halfApexAngle = 0.7f,
	//	.angle = 0.0f,
	//	.angularVelocity = 0.0f
	//};

	Ball ball{
		.position = {0.8f,1.0f,0.1f},
		.acceleration = {0.0f,-9.8f,0.0f},
		.mass = 2.0f,
		.radius = 0.05f,
		.color = BLUE
	};

	Ball startBall = ball;

	Plane plane{
		.normal = {0.2f,0.9f,0.2f},
		.distance = 0.0f
	};

	float e = 0.8f;

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

		Vector3Array p = { 0,0,0 };

		if (isStart) {
			ball.velocity += ball.acceleration * deltaTime;
			ball.position += ball.velocity * deltaTime;

			if (isCollision(Sphere{ ball.position,ball.radius }, plane)) {
				Vector3Array reflected = Reflect(ball.velocity, plane.normal);
				Vector3Array projectToNormal = Project(reflected, plane.normal);
				Vector3Array movingDirection = reflected - projectToNormal;
				ball.velocity = projectToNormal * e + movingDirection;
			}
		}
		else {
			ball = startBall;
		}

		//imgui
		ImGui::Begin("Window");
		if (ImGui::Button("Start")) {
			isStart = true;
			ball = startBall;
		}
		if (ImGui::Button("Stop")) {
			isStart = false;
			ball = startBall;
		}
		ImGui::End();

		ImGui::Begin("Plane");
		ImGui::DragFloat3("normal", plane.normal.v, 0.01f);
		ImGui::DragFloat("disance", &plane.distance, 0.01f);

		plane.normal = Normalize(plane.normal);
		ImGui::End();

		ImGui::Begin("Ball");
		ImGui::DragFloat3("position", startBall.position.v, 0.01f);
		ImGui::End();

		///
		/// ↑更新処理ここまで
		///

		///
		/// ↓描画処理ここから
		///
		DrawGrid(camera->GetCamera());

		DrawSphere(Sphere{ .center = ball.position,.radius = 0.05f }, camera->GetCamera(), 0x0000FFFF, 20);
		DrawPlane(plane, camera->GetCamera(), 0xFFFFFFFF);
		//DrawLine(conicalPendulum.anchor, p, camera->GetCamera(), WHITE);

		/*DrawSphere(Sphere{ .center = worldPS,.radius = 0.1f }, camera->GetCamera(), 0xFF0000FF, 10);
		DrawSphere(Sphere{ .center = worldPE,.radius = 0.1f }, camera->GetCamera(), 0x00FF00FF, 10);
		DrawSphere(Sphere{ .center = worldPH,.radius = 0.1f }, camera->GetCamera(), 0x0000FFFF, 10);

		DrawLine(worldPS, worldPE, camera->GetCamera(), WHITE);
		DrawLine(worldPE, worldPH, camera->GetCamera(), WHITE);*/

		camera->DebugDraw();
		//Novice::DrawLine(int(start.v[0]), int(start.v[1]), int(end.v[0]), int(end.v[1]), color);

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
