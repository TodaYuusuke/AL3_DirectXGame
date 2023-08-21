#include "Player.h"
#include <ImGuiManager.h>
#include <cassert>

void Player::Initialize(Model* model, uint32_t textureHandle, Vector3 position) {
	
	// NULLポインタチェック
	assert(model);

	// モデル
	model_ = model;
	textureHandle_ = textureHandle;

	// ワールドトランスフォ－ムの初期化
	worldTransform_.Initialize();
	worldTransform_.translation_ = position;
}



void Player::Update() {
	ImGui::Begin("Player");
	ImGui::DragFloat3("translation", &worldTransform_.translation_.x, 0.1f);
	ImGui::DragFloat3("rotation", &worldTransform_.rotation_.x, 0.01f);
	ImGui::End();

	worldTransform_.UpdateMatrix();
}



void Player::Draw(ViewProjection viewProjection) {
	model_->Draw(worldTransform_, viewProjection, textureHandle_);
}