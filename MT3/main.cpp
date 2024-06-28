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

	Vector3Array controlPoints[3]{
		{-0.8f,0.58f,1.0f},
		{1.76f,1.0f,-0.3f},
		{0.94f,-0.7f,2.3f},
	};

	/*Sphere sphere{};
	sphere.center = { 0,0,0 };
	sphere.radius = 0.5f;*/

	/*OBB obb1{
		.center{-0.1f,0.0f,0.0f},
		.orientations = {
		{1.0f,0.0f,0.0f},
		{0.0f,1.0f,0.0f},
		{0.0f,0.0f,1.0f}
			},
		.size{0.5,0.5f,0.5f}
	};

	OBB obb2{
		.center{-0.1f,0.0f,0.0f},
		.orientations = {
		{1.0f,0.0f,0.0f},
		{0.0f,1.0f,0.0f},
		{0.0f,0.0f,1.0f}
			},
		.size{0.5,0.5f,0.5f}
	};

	Vector3Array rotate1{};
	Vector3Array rotate2{};*/

	/*Sphere sphere2{};
	sphere1.center = { 3,0,0 };
	sphere1.radius = 2;*/

	//Segment segment{ {-0.7f,0.3f,0.0f},{2.0f,-0.5f,0.0f} };
	/*Vector3Array point{ -1.5f,0.6f,0.6f };
	Vector3Array project{};
	Vector3Array closestPoint{};

	project = Project(Subtract(point, segment.origin), segment.diff);
	closestPoint = ClosestPoint(point, segment);

	Sphere pointSphere{ point,0.01f };
	Sphere closestPointSphere{ closestPoint,0.01f };*/

	/*Triangle triangle{};
	triangle.pos[0].local = { 0,1,0 };
	triangle.pos[1].local = { 1,-1,0 };
	triangle.pos[2].local = { -1,-1,0 };
	triangle.scale = { 1,1,1 };

	Vector3Array v01 = Subtract(triangle.worldPos[1], triangle.worldPos[0]);
	Vector3Array v12 = Subtract(triangle.worldPos[2], triangle.worldPos[1]);
	Vector3Array n = Normalize(Cross(v01, v12));

	Plane plane = {};
	plane.distance = Dot(triangle.worldPos[1],n);
	plane.normal = n;*/

	/*AABB aabb = {
	.min = {-0.5f,-0.5f,-0.5f},
	.max = {0.5f,0.5f,0.5f},
	};*/

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

		/*aabb.min.v[0] = (std::min)(aabb.min.v[0], aabb.max.v[0]);
		aabb.min.v[1] = (std::min)(aabb.min.v[1], aabb.max.v[1]);
		aabb.min.v[2] = (std::min)(aabb.min.v[2], aabb.max.v[2]);*/

		/*if (isCollision(obb1, obb2)) {
			color = RED;
		}*/
		/*v01 = Subtract(triangle.worldPos[1], triangle.worldPos[0]);
		v12 = Subtract(triangle.worldPos[2], triangle.worldPos[1]);
		n = Normalize(Cross(v01, v12));

		plane.distance = Dot(triangle.worldPos[0], n);
		plane.normal = n;*/

		/*RenderingPipeline(triangle, camera->GetCamera());
		if (isCollision(segment, plane)) {
			color = BLUE;
		}
		if (isCollision(triangle, segment) && isCollision(segment, plane)) {
			color = RED;
		}*/

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
		DrawBezier(controlPoints[0], controlPoints[1], controlPoints[2], camera->GetCamera(), color);
		DrawSphere(Sphere{ .center = controlPoints[0],.radius = 0.01f }, camera->GetCamera(), 0x000000FF, 5);
		DrawSphere(Sphere{ .center = controlPoints[1],.radius = 0.01f }, camera->GetCamera(), 0x000000FF, 5);
		DrawSphere(Sphere{ .center = controlPoints[2],.radius = 0.01f }, camera->GetCamera(), 0x000000FF, 5);
		/*DrawOBB(obb1, camera->GetCamera(), color);
		DrawOBB(obb2, camera->GetCamera(), color);*/
		////DrawLine(camera->GetCamera());
		camera->DebugDraw();
		//Novice::DrawLine(int(start.v[0]), int(start.v[1]), int(end.v[0]), int(end.v[1]), color);
		//MyDrawTriangle(triangle, color);
		//DrawPlane(plane, camera->GetCamera(), color);

		//Novice::ScreenPrintf(0, 15, "%f", plane.distance);

		//DrawSphere(sphere, camera->GetCamera(), color, 10);
		//DrawSphere(closestPointSphere, camera->GetCamera(), BLACK, 10);
		/*if (isCollision(sphere1, sphere2)) {
			color = RED;
		}*/

		//DrawSphere(sphere1, camera->GetCamera(), color, 36);
		/*DrawSphere(sphere2, camera->GetCamera(), 0xFFFFFFFF, 10); */

		//DrawPlane(plane, camera->GetCamera(), color);

		//imgui
		ImGui::Begin("Bezier");
		ImGui::DragFloat3("control0", controlPoints[0].v, 0.1f);
		ImGui::DragFloat3("control1", controlPoints[1].v, 0.1f);
		ImGui::DragFloat3("control2", controlPoints[2].v, 0.1f);
		/*ImGui::SliderFloat3("center1", obb1.center.v, -30.0f, 30.0f);
		ImGui::SliderFloat3("rotate1", rotate1.v, -10.0f, 10.0f);
		ImGui::SliderFloat3("center2", obb2.center.v, -30.0f, 30.0f);
		ImGui::SliderFloat3("rotate2", rotate2.v, -10.0f, 10.0f);*/
		/*ImGui::SliderFloat3("aabb1.min", aabb.min.v, -10.0f, 10.0f);
		ImGui::SliderFloat3("aabb1.max", aabb.max.v, -10.0f, 10.0f);*/
		ImGui::End();

		//ImGui::Begin("Segment");
		//ImGui::DragFloat3("PlaneNormal", plane.normal.v, 0.1f);
		//ImGui::DragFloat("PlaneDistance", &plane.distance, 0.1f);
		//ImGui::DragFloat3("segmentOrigin", segment.origin.v, 0.1f);
		//ImGui::DragFloat3("segmentDiff", segment.diff.v, 0.1f);
		//plane.normal = Normalize(plane.normal);
		/*ImGui::SliderFloat3("center1", sphere.center.v, -10.0f, 10.0f);
		ImGui::SliderFloat("radius1", &sphere.radius, 0.01f, 2.0f);*/
		/*ImGui::SliderFloat3("center2", sphere2.center.v, -10.0f, 10.0f);
		ImGui::SliderFloat("radius2", &sphere2.radius, 0.01f, 2.0f);*/
		/*ImGui::InputFloat3("Point", point.v, "%0.3f", ImGuiInputTextFlags_ReadOnly);
		ImGui::InputFloat3("SegmentOrigin", segment.origin.v, "%0.3f", ImGuiInputTextFlags_ReadOnly);
		ImGui::InputFloat3("SegmentDiff", segment.diff.v, "%0.3f", ImGuiInputTextFlags_ReadOnly);
		ImGui::InputFloat3("Project", project.v, "%0.3f", ImGuiInputTextFlags_ReadOnly);*/
		//ImGui::End();
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
