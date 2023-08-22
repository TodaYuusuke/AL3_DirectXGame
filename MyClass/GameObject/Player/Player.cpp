#include "Player.h"
#include <ImGuiManager.h>
#include <cassert>
#include <Input.h>

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

	// 移動処理
	MoveJoyStick();

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


void Player::MoveJoyStick() {
	// キャラクターの移動ベクトル
	Vector3 move = {0, 0, 0};

	// ゲームパッドの状態を得る変数（XINPUT）
	XINPUT_STATE joyState;

	// ゲームパッド状態取得
	if (Input::GetInstance()->GetJoystickState(0, joyState)) {
		// キャラクター移動
		move = {
		    (float)joyState.Gamepad.sThumbLX / SHRT_MAX, 
			0.0f,
		    (float)joyState.Gamepad.sThumbLY / SHRT_MAX};
		move = Normalize(move) * kCharacterSpeed;
		Vector3 rotation = viewProjection_->rotation_;
		rotation.x = 0.0f;
		move = move * Matrix4x4::MakeRotateMatrix(rotation);

		// キャラクターの向きを決定する
		if (Length(move) > 0.0f) {
			// Y軸周りの角度
			worldTransform_.rotation_.y = std::atan2f(move.x, move.z);
			// X軸周りの角度
			worldTransform_.rotation_.x = std::atan2f(-move.y, Length({move.x, 0, move.z}));
		}
	}

	// 移動
	worldTransform_.translation_ += move;
}