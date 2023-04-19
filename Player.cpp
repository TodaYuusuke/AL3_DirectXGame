#include "Player.h"
#include <cassert>

void Player::Initialize(Model* model, uint32_t textureHandle) {
	
	// NULLポインタチェック
	assert(model);

	// モデル
	model_ = model;
	textureHandle_ = textureHandle;

	// ワールドトランスフォ－ムの初期化
	worldTransform_.Initialize();
}



void Player::Update() {
	worldTransform_.TransferMatrix();
}



void Player::Draw(ViewProjection viewProjection) {
	model_->Draw(worldTransform_, viewProjection, textureHandle_);
}