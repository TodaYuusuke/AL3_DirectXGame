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
        {10, 10, 3},
        {10, 15, 6},
        {20, 15, 9},
        {20, 0,  6},
        {30, 0,  3}
	};
	t = 0.0f;
}

void RailCamera::Update() {
	// カメラの座標を画面表示する処理
	ImGui::Begin("Camera");
	ImGui::Text("RAlt ... CameraChange");
	ImGui::DragFloat3("translation", &worldTransform_.translation_.x, 0.1f);
	ImGui::DragFloat3("rotation", &worldTransform_.rotation_.x, 0.01f);
	ImGui::DragFloat("t", &t, 0.001f, 0.0f, 1.0f);
	ImGui::End();
	// レールに沿って進む
	t += 0.001f;
	t = std::clamp(t, 0.0f, 1.0f);
	worldTransform_.translation_ = GetCatmullRomPosition(controlPoints_, t);

	// 回転角を求める
	float forwordT = t + 0.1f;
	forwordT = std::clamp(forwordT, 0.0f, 1.0f);
	Vector3 forword = GetCatmullRomPosition(controlPoints_, forwordT) - worldTransform_.translation_;
	// Y軸周りの角度
	worldTransform_.rotation_.y = std::atan2f(forword.x, forword.z);
	// X軸周りの角度
	worldTransform_.rotation_.x = std::atan2f(-forword.y, Length({forword.x, 0, forword.z}));

	// ワールドトランスフォーム更新
	worldTransform_.UpdateMatrix();

	// カメラオブジェクトのワールド行列からビュー行列を計算する
	viewProjection_.matView = Matrix4x4::Inverse(worldTransform_.matWorld_);
}

void RailCamera::Draw() {
	// スプライン曲線を描画
	DrawCatmullRom(controlPoints_, 100);
}