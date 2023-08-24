#include "Enemy.h"
#include <ImGuiManager.h>
#include <cassert>
#include <Input.h>

void Enemy::Initialize(const std::vector<Model*>& models, Vector3 position) {
	BaseCharacter::Initialize(models, position);

	// 親子関連付け
	models_[Body].worldTransform_.parent_ = &worldTransform_;
	models_[LeftWheel].worldTransform_.parent_ = &models_[Body].worldTransform_;
	models_[RightWheel].worldTransform_.parent_ = &models_[Body].worldTransform_;
	// アニメーション初期化
	InitializeAnimation();
}

void Enemy::Update() {
	ImGui::Begin("Enemy");
	ImGui::DragFloat3("translation", &worldTransform_.translation_.x, 0.1f);
	ImGui::DragFloat3("rotation", &worldTransform_.rotation_.x, 0.01f);
	ImGui::DragFloat3("body - rotation", &models_[Body].worldTransform_.rotation_.x, 0.01f);
	ImGui::End();

	// アニメーション
	Animation();

	BaseCharacter::Update();
}


void Enemy::InitializeAnimation() {

	models_[Body].worldTransform_.translation_ = {0.0f, 0.0f, 0.0f};
	models_[Body].worldTransform_.scale_ = {3.0f, 3.0f, 3.0f};
	models_[LeftWheel].worldTransform_.translation_ = {0.7f, -0.1f, 0.0f};
	models_[LeftWheel].worldTransform_.scale_ = {1.0f, 1.2f, 1.2f};
	models_[RightWheel].worldTransform_.translation_ = {-0.7f, -0.1f, 0.0f};
	models_[RightWheel].worldTransform_.scale_ = {1.0f, 1.2f, 1.2f};

	engineParameter_ = 0.0f;
}

void Enemy::Animation() {
	EngineUpdate();
	CircleUpdate();
}

void Enemy::EngineUpdate() {
	// パラメータを1ステップ分加算
	engineParameter_ += (float)kEngineStep_;
	// 2πを超えたら0に戻す
	engineParameter_ = (float)std::fmod(engineParameter_, 2.0f * M_PI);
	
	// 振動を座標に反映
	models_[Body].worldTransform_.translation_.y = std::sin(engineParameter_) * kEngineHeight;
}

void Enemy::CircleUpdate() {
	// パラメータを1ステップ分加算
	circleParameter_ += (float)kCircleStep_;
	
	worldTransform_.rotation_.y = circleParameter_;
	models_[LeftWheel].worldTransform_.rotation_.x -= (float)circleParameter_ * kCirclePower;
	models_[RightWheel].worldTransform_.rotation_.x += (float)circleParameter_ * kCirclePower;

	// 2πを超えたら0に戻す
	circleParameter_ = (float)std::fmod(circleParameter_, 2.0f * M_PI);

	// 視点の方向に進む
	Vector3 move = {0.0f, 0.0f, -0.5f};
	worldTransform_.translation_ += move * Matrix4x4::MakeRotateMatrix(worldTransform_.rotation_);
}