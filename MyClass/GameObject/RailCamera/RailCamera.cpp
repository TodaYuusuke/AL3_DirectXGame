#include "RailCamera.h"
#include <ImGuiManager.h>
#include "PrimitiveDrawer.h"

void RailCamera::Initialize(Vector3 worldPosition, Vector3 radian) {
	// ワールドトランスフォームの初期化
	worldTransform_.Initialize();
	worldTransform_.translation_ = worldPosition;
	worldTransform_.rotation_ = radian;
	worldTransform_.UpdateMatrix();

	viewProjection_.Initialize();

	controlPoints_ = {
	    {0,  0,  0},
        {10, 10, 0},
        {10, 15, 0},
        {20, 15, 0},
        {20, 0,  0},
        {30, 0,  0}
	};
	t = 1.0f;
}

void RailCamera::Update() {
	// カメラの座標を画面表示する処理
	ImGui::Begin("Camera");
	ImGui::DragFloat3("translation", &worldTransform_.translation_.x, 0.1f);
	ImGui::DragFloat3("rotation", &worldTransform_.rotation_.x, 0.01f);
	ImGui::DragFloat("t", &t, 0.01f, 0.0f, 1.0f);
	ImGui::End();
	// レールに沿って進む
	worldTransform_.translation_ = GetCatmullRomPosition(controlPoints_, t);

	worldTransform_.UpdateMatrix();

	// カメラオブジェクトのワールド行列からビュー行列を計算する
	viewProjection_.matView = Matrix4x4::Inverse(worldTransform_.matWorld_);
}

void RailCamera::Draw() {
	// スプライン曲線を描画
	DrawCatmullRom(controlPoints_, 100);
}