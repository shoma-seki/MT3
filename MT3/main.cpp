#include <Novice.h>
#include "MatrixFunc.h"
#include "Functions.h"
#define _USE_MATH_DEFINES
#include <math.h>
#include <time.h>
#include <stdlib.h>
#include "Camera3d.h"
#include "ImGuiManager.h"


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

	Sphere sphere{};
	sphere.center = { 0,0,0 };
	sphere.radius = 1;

	Segment segment{ {-2.0f,-1.0f,0.0f},{3.0f,2.0f,2.0f} };
	Vector3Array point{ -1.5f,0.6f,0.6f };
	Vector3Array project{};
	Vector3Array closestPoint{};
	Matrix4x4 startWorldMatrix = MakeAffineMatrix({ 1,1,1 }, { 0,0,0 }, segment.origin);
	Matrix4x4 endWorldMatrix = MakeAffineMatrix({ 1,1,1 }, { 0,0,0 }, segment.diff);
	
	project = Project(Subtract(point, segment.origin), segment.diff);
	closestPoint = ClosestPoint(point, segment);

	Sphere pointSphere{ point,0.01f };
	Sphere closestPointSphere{ closestPoint,0.01f };
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
		Vector3Array start = RenderingPipeline(Vector3Array{}, startWorldMatrix, camera->GetCamera());
		Vector3Array end = RenderingPipeline(Vector3Array{}, endWorldMatrix, camera->GetCamera());
		///
		/// ↑更新処理ここまで
		///

		///
		/// ↓描画処理ここから
		///
		DrawGrid(camera->GetCamera());
		//DrawLine(camera->GetCamera());
		camera->DebugDraw();
		Novice::DrawLine(int(start.v[0]), int(start.v[1]), int(end.v[0]), int(end.v[1]), 0xFFFFFFFF);

		DrawSphere(pointSphere, camera->GetCamera(), RED, 10);
		DrawSphere(closestPointSphere, camera->GetCamera(), BLACK, 10);
		//imgui
		ImGui::Begin("Sphere");
		//ImGui::SliderFloat3("center", sphere.center.v, -10.0f, 10.0f);
		//ImGui::SliderFloat("radius", &sphere.radius, 0.0f, 2.0f);
		ImGui::InputFloat3("Point", point.v, "%0.3f", ImGuiInputTextFlags_ReadOnly);
		ImGui::InputFloat3("SegmentOrigin", segment.origin.v, "%0.3f", ImGuiInputTextFlags_ReadOnly);
		ImGui::InputFloat3("SegmentDiff", segment.diff.v, "%0.3f", ImGuiInputTextFlags_ReadOnly);
		ImGui::InputFloat3("Project", project.v, "%0.3f", ImGuiInputTextFlags_ReadOnly);
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
