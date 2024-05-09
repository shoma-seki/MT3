#include <Novice.h>
#include "Functions.h"
#include "MatrixFunc.h"
#define _USE_MATH_DEFINES
#include <math.h>
#include <time.h>
#include <stdlib.h>
#include "MyDraw.h"
#include "Camera3d.h"
#include "MatrixFunc.h"


const char kWindowTitle[] = "LC1A_17_セキ_ショウマ_タイトル";

// Windowsアプリでのエントリーポイント(main関数)
int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int) {

	// ライブラリの初期化
	Novice::Initialize(kWindowTitle, 1280, 720);

	// キー入力結果を受け取る箱
	char keys[256] = { 0 };
	char preKeys[256] = { 0 };
	srand(unsigned int(time(nullptr)));

	Camera3d* camera3d = new Camera3d({ 1.0f,1.0f,1.0f }, { 0.26f,0.0f,0.0f }, { 0.0f,1.9f,-6.49f });

	Triangle triangle = {};
	triangle.pos[0].local = { 0,1,0 };
	triangle.pos[1].local = { 1,-1,0 };
	triangle.pos[2].local = { -1,-1,0 };
	triangle.worldPos[0] = Add(triangle.pos[0].local, triangle.translate);
	triangle.worldPos[1] = Add(triangle.pos[1].local, triangle.translate);
	triangle.worldPos[2] = Add(triangle.pos[2].local, triangle.translate);
	triangle.translate.vector3[1] = 0;
	triangle.translate.vector3[2] = 0;
	triangle.speed = 0.1f;
	triangle.scale = { 1.0f,1.0f,1.0f };
	triangle.worldMatrix = MakeAffineMatrix(triangle.scale, triangle.rotate, triangle.translate);

	Vector3Array dirVector[2] = {};
	dirVector[0] = Subtract(triangle.worldPos[1], triangle.worldPos[0]);
	dirVector[1] = Subtract(triangle.worldPos[2], triangle.worldPos[1]);
	Vector3Array cameraDir = { 0,0,1 };
	float dot = Dot(cameraDir, Cross(dirVector[0], dirVector[1]));

	Vector3Array v1{ 1.2f, -3.9f, 2.5f };
	Vector3Array v2{ 2.8f, 0.4f, -1.3f };
	Vector3Array cross = Cross(v1, v2);

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
		if (keys[DIK_W]) {
			triangle.dir.vector3[2]++;
		}
		if (keys[DIK_S]) {
			triangle.dir.vector3[2]--;
		}
		if (keys[DIK_A]) {
			triangle.dir.vector3[0]--;
		}
		if (keys[DIK_D]) {
			triangle.dir.vector3[0]++;
		}

		triangle.velocity = Multiply(triangle.speed, triangle.dir);
		triangle.translate = Add(triangle.velocity, triangle.translate);

		triangle.dir.vector3[0] = 0;
		triangle.dir.vector3[1] = 0;
		triangle.dir.vector3[2] = 0;
		triangle.rotate.vector3[1] += 0.03f;

		triangle.worldMatrix = MakeAffineMatrix(triangle.scale, triangle.rotate, triangle.translate);

		for (int i = 0; i < 3; i++) {
			triangle.pos[i].screen = RenderingPipeline(triangle.pos[i].local, triangle.worldMatrix, camera3d->GetCamera(), triangle.worldPos[i]);
		}

		dirVector[0] = Subtract(triangle.worldPos[1], triangle.worldPos[0]);
		dirVector[1] = Subtract(triangle.worldPos[2], triangle.worldPos[1]);
		dot = Dot(cameraDir, Cross(dirVector[0], dirVector[1]));

		camera3d->Update(keys);
		///
		/// ↑更新処理ここまで
		///

		///
		/// ↓描画処理ここから
		///
		if (dot <= 0) {
			MyDrawTriangle(triangle.pos[0].screen, triangle.pos[1].screen, triangle.pos[2].screen, RED);
		}
		else {
			MyDrawTriangle(triangle.pos[0].screen, triangle.pos[1].screen, triangle.pos[2].screen, 0x00000000);
		}
		Novice::ScreenPrintf(0, 60, "%f", triangle.pos[0].screen.vector3[0]);
		Novice::ScreenPrintf(0, 75, "%f", triangle.pos[0].screen.vector3[1]);
		VectorScreenPrintf(0, 0, cross, "Cross");
		for (int i = 0; i < 3; i++) {
			Novice::ScreenPrintf(int(triangle.pos[i].screen.vector3[0]), int(triangle.pos[i].screen.vector3[1]), "%d", i);
		}
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
