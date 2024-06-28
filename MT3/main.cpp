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

	Vector3Array translates[3] = {
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
	};

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

		Matrix4x4 localS = MakeAffineMatrix(scales[0], rotates[0], translates[0]);
		Matrix4x4 localE = MakeAffineMatrix(scales[1], rotates[1], translates[1]);
		Matrix4x4 localH = MakeAffineMatrix(scales[2], rotates[2], translates[2]);

		Matrix4x4 worldS = localS;
		Matrix4x4 worldE = Multiply(localE, localS);
		Matrix4x4 worldH = Multiply(localH, Multiply(localE, localS));

		Vector3Array worldPS = Transform({ 0,0,0 }, worldS);
		Vector3Array worldPE = Transform({ 0,0,0 }, worldE);
		Vector3Array worldPH = Transform({ 0,0,0 }, worldH);

		/*Matrix4x4 rotateMatrix1 = Multiply(MakeRotateXMatrix(rotate1.v[0]), Multiply(MakeRotateYMatrix(rotate1.v[1]), MakeRotateZMatrix(rotate1.v[2])));

		obb1.orientations[0].v[0] = rotateMatrix1.matrix[0][0];
		obb1.orientations[0].v[1] = rotateMatrix1.matrix[0][1];
		obb1.orientations[0].v[2] = rotateMatrix1.matrix[0][2];

		obb1.orientations[1].v[0] = rotateMatrix1.matrix[1][0];
		obb1.orientations[1].v[1] = rotateMatrix1.matrix[1][1];
		obb1.orientations[1].v[2] = rotateMatrix1.matrix[1][2];

		obb1.orientations[2].v[0] = rotateMatrix1.matrix[2][0];
		obb1.orientations[2].v[1] = rotateMatrix1.matrix[2][1];
		obb1.orientations[2].v[2] = rotateMatrix1.matrix[2][2];

		Matrix4x4 rotateMatrix2 = Multiply(MakeRotateXMatrix(rotate2.v[0]), Multiply(MakeRotateYMatrix(rotate2.v[1]), MakeRotateZMatrix(rotate2.v[2])));

		obb2.orientations[0].v[0] = rotateMatrix2.matrix[0][0];
		obb2.orientations[0].v[1] = rotateMatrix2.matrix[0][1];
		obb2.orientations[0].v[2] = rotateMatrix2.matrix[0][2];

		obb2.orientations[1].v[0] = rotateMatrix2.matrix[1][0];
		obb2.orientations[1].v[1] = rotateMatrix2.matrix[1][1];
		obb2.orientations[1].v[2] = rotateMatrix2.matrix[1][2];

		obb2.orientations[2].v[0] = rotateMatrix2.matrix[2][0];
		obb2.orientations[2].v[1] = rotateMatrix2.matrix[2][1];
		obb2.orientations[2].v[2] = rotateMatrix2.matrix[2][2];*/

		///
		/// ↑更新処理ここまで
		///

		///
		/// ↓描画処理ここから
		///
		DrawGrid(camera->GetCamera());

		DrawSphere(Sphere{ .center = worldPS,.radius = 0.1f }, camera->GetCamera(), 0xFF0000FF, 10);
		DrawSphere(Sphere{ .center = worldPE,.radius = 0.1f }, camera->GetCamera(), 0x00FF00FF, 10);
		DrawSphere(Sphere{ .center = worldPH,.radius = 0.1f }, camera->GetCamera(), 0x0000FFFF, 10);
		
		DrawLine(worldPS, worldPE, camera->GetCamera(), WHITE);
		DrawLine(worldPE, worldPH, camera->GetCamera(), WHITE);

		camera->DebugDraw();
		//Novice::DrawLine(int(start.v[0]), int(start.v[1]), int(end.v[0]), int(end.v[1]), color);

		//imgui
		ImGui::Begin("Window");
		ImGui::DragFloat3("translates0", translates[0].v, 0.1f);
		ImGui::DragFloat3("rotates0", rotates[0].v, 0.1f);
		ImGui::DragFloat3("scales0", scales[0].v, 0.1f);
		ImGui::DragFloat3("translates1", translates[1].v, 0.1f);
		ImGui::DragFloat3("rotates1", rotates[1].v, 0.1f);
		ImGui::DragFloat3("scales1", scales[1].v, 0.1f);
		ImGui::DragFloat3("translates2", translates[2].v, 0.1f);
		ImGui::DragFloat3("rotates2", rotates[2].v, 0.1f);
		ImGui::DragFloat3("scales2", scales[2].v, 0.1f);
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
