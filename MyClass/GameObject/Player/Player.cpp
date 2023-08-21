#include "Player.h"
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
	worldTransform_.TransferMatrix();
}



void Player::Draw(ViewProjection viewProjection) {
	model_->Draw(worldTransform_, viewProjection, textureHandle_);
}