#include "ThirdPersonCamera.h"
#include <ImGuiManager.h>

void ThirdPersonCamera::Initialize(Vector3 worldPosition, Vector3 radian) {
	// ワールドトランスフォームの初期化
	worldTransform_.Initialize();
	worldTransform_.translation_ = worldPosition;
	worldTransform_.rotation_ = radian;
	worldTransform_.UpdateMatrix();

	viewProjection_.Initialize();
}

void ThirdPersonCamera::Update() {
	// カメラの座標を画面表示する処理
	ImGui::Begin("Camera");
	ImGui::DragFloat3("translation", &worldTransform_.translation_.x, 0.1f);
	ImGui::DragFloat3("rotation", &worldTransform_.rotation_.x, 0.01f);
	ImGui::End();

	// 徐々に前に進む
	//worldTransform_.translation_.z += 0.02f;

	worldTransform_.UpdateMatrix();

	// カメラオブジェクトのワールド行列からビュー行列を計算する
	viewProjection_.matView = Matrix4x4::Inverse(worldTransform_.matWorld_);
}