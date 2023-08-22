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

	// 親子関連付け
	modelTransform_[1].parent_ = &worldTransform_;
	modelTransform_[0].parent_ = &modelTransform_[1];
	modelTransform_[2].parent_ = &modelTransform_[1];
	modelTransform_[3].parent_ = &modelTransform_[1];
	// アニメーション初期化
	InitializeAnimation();
}

void Player::Update() {
	ImGui::Begin("Player");
	ImGui::DragFloat3("translation", &worldTransform_.translation_.x, 0.1f);
	ImGui::DragFloat3("rotation", &worldTransform_.rotation_.x, 0.01f);
	//ImGui::DragFloat3("head", &modelTransform_[0].translation_.x, 0.01f);
	//ImGui::DragFloat3("body", &modelTransform_[1].translation_.x, 0.01f);
	//ImGui::DragFloat3("Larm", &modelTransform_[2].translation_.x, 0.01f);
	//ImGui::DragFloat3("Rarm", &modelTransform_[3].translation_.x, 0.01f);
	ImGui::End();

	// 移動処理
	MoveJoyStick();
	// アニメーション
	Animation();

	worldTransform_.UpdateMatrix();
	for (int i = 0; i < 4; i++) {
		modelTransform_[i].UpdateMatrix();
	}
}

void Player::Draw(ViewProjection viewProjection) {
	headModel_->Draw(modelTransform_[Head], viewProjection);
	bodyModel_->Draw(modelTransform_[Body], viewProjection);
	leftArmModel_->Draw(modelTransform_[LeftArm], viewProjection);
	rightArmModel_->Draw(modelTransform_[RightArm], viewProjection);
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
			// 目的の角度
			Vector3 goalRotation = {0.0f, 0.0f, 0.0f};
			// Y軸周りの角度
			goalRotation.y = std::atan2f(move.x, move.z);
			// X軸周りの角度
			goalRotation.x = std::atan2f(-move.y, Length({move.x, 0, move.z}));

			// 現在の角度と目標の角度を比較し、逆回転の場合に調整
			if (std::abs(worldTransform_.rotation_.y - goalRotation.y) > M_PI) {
				if (worldTransform_.rotation_.y > goalRotation.y) {
					worldTransform_.rotation_.y -= static_cast<float>(2.0f * M_PI);
				} else {
					worldTransform_.rotation_.y += static_cast<float>(2.0f * M_PI);
				}
			}

			// 角度を適応
			worldTransform_.rotation_ = Slerp(worldTransform_.rotation_, goalRotation, 0.2f);
		}
	}

	// 移動
	worldTransform_.translation_ += move;
}

void Player::InitializeAnimation() {
	modelTransform_[Body].scale_ = {1.5f, 1.5f, 1.5f};
	
	for (int i = 0; i < 4; i++) {
		modelTransform_[i].Initialize();
		//modelTransform_[i].scale_ = {1.5f, 1.5f, 1.5f};
	}
	modelTransform_[Head].translation_ = {0.0f, 1.5f, 0.0f};
	modelTransform_[Body].translation_ = {0.0f, 0.0f, 0.0f};
	modelTransform_[LeftArm].translation_ = {-0.44f, 1.34f, 0.0f};
	modelTransform_[RightArm].translation_ = {0.44f, 1.34f, 0.0f};
}

void Player::Animation() {
	FloatingUpdate();
}

void Player::FloatingUpdate() {
	// パラメータを1ステップ分加算
	floatingParameter_ += (float)kFloatingStep_;
	// 2πを超えたら0に戻す
	floatingParameter_ = (float)std::fmod(floatingParameter_, 2.0f * M_PI);
	
	// 浮遊を座標に反映
	modelTransform_[Body].translation_.y = std::sin(floatingParameter_) * kFloatingHeight;
}
