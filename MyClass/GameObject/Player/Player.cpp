#include "Player.h"
#include <ImGuiManager.h>
#include <cassert>

void Player::Initialize(Model* head, Model* body, Model* Larm, Model* Rarm, Vector3 position) {
	// NULLポインタチェック
	assert(head);
	assert(body);
	assert(Larm);
	assert(Rarm);

	// モデル
	headModel_ = head;
	bodyModel_ = body;
	leftArmModel_ = Larm;
	rightArmModel_ = Rarm;

	// ワールドトランスフォ－ムの初期化
	worldTransform_.Initialize();
	worldTransform_.translation_ = position;

	for (int i = 0; i < 4; i++) {
		modelTransform_[i].Initialize();
		modelTransform_[i].parent_ = &worldTransform_;
		modelTransform_[i].scale_ = {1.5f, 1.5f, 1.5f};
	}
	modelTransform_[0].translation_ = {0.0f, 2.3f, 0.0f};
	modelTransform_[1].translation_ = {0.0f, 0.0f, 0.0f};
	modelTransform_[2].translation_ = {-0.6f, 2.2f, 0.0f};
	modelTransform_[3].translation_ = {0.6f, 2.2f, 0.0f};
}



void Player::Update() {
	ImGui::Begin("Player");
	ImGui::DragFloat3("translation", &worldTransform_.translation_.x, 0.1f);
	ImGui::DragFloat3("rotation", &worldTransform_.rotation_.x, 0.01f);
	ImGui::End();

	worldTransform_.UpdateMatrix();
	for (int i = 0; i < 4; i++) {
		modelTransform_[i].UpdateMatrix();
	}
}



void Player::Draw(ViewProjection viewProjection) {
	headModel_->Draw(modelTransform_[0], viewProjection);
	bodyModel_->Draw(modelTransform_[1], viewProjection);
	leftArmModel_->Draw(modelTransform_[2], viewProjection);
	rightArmModel_->Draw(modelTransform_[3], viewProjection);
}