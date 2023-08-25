#include "Player.h"
#include <ImGuiManager.h>
#include <cassert>
#include <Input.h>

void Player::Initialize(const std::vector<Model*>& models, Vector3 position) {
	BaseCharacter::Initialize(models, position);
	// 親子関連付け
	models_[Body].worldTransform_.parent_ = &worldTransform_;
	models_[Head].worldTransform_.parent_ = &models_[Body].worldTransform_;
	models_[LeftArm].worldTransform_.parent_ = &models_[Body].worldTransform_;
	models_[RightArm].worldTransform_.parent_ = &models_[Body].worldTransform_;
	models_[Weapon].worldTransform_.parent_ = &models_[Body].worldTransform_;
	// アニメーション初期化
	SetModelNeutral();

	behaviorRequest_ = Behavior::kRoot;
}

void Player::Update() {
	ImGui::Begin("Player");
	ImGui::Text("L Stick ... Move");
	ImGui::Text("R Stick ... Camera Move");
	ImGui::Text("R Button ... Attack");
	ImGui::End();

	if (behaviorRequest_) {
		// 振る舞いを変更する
		behavior_ = behaviorRequest_.value();
		// 各振る舞いごとの初期化を実行
		switch (behavior_) {
		case Behavior::kRoot:
		default:
			BehaviorRootReset();
			break;
		case Behavior::kAttack:
			BehaviorAttackReset();
			break;
		}
		// 振る舞いリクエストをリセット
		behaviorRequest_ = std::nullopt;
	}

	
	switch (behavior_) {
	case Behavior::kRoot:
	default:
		BehaviorRootUpdate();
		break;
	case Behavior::kAttack:
		BehaviorAttackUpdate();
		break;
	}


	BaseCharacter::Update();
}

void Player::Draw(const ViewProjection& viewProjection) {
	for (int i = 0; i < Weapon; i++) {
		models_[i].model_->Draw(models_[i].worldTransform_, viewProjection);
	}

	if (behavior_ == Behavior::kAttack) {
		models_[Weapon].model_->Draw(models_[Weapon].worldTransform_, viewProjection);
	}
}


void Player::BehaviorRootReset() {
	SetModelNeutral();

	floatingParameter_ = 0.0f;
	armSwingParameter_ = 0.0f;
}
void Player::BehaviorRootUpdate() {
	// 移動処理
	MoveJoyStick();
	// アニメーション
	FloatingUpdate();
	ArmSwingUpdate();
}

void Player::BehaviorAttackReset() {
	SetModelNeutral();

	attackAnimationFrame = 0;
}
void Player::BehaviorAttackUpdate() {
	if (attackAnimationFrame < kPreliminaryCycle_) {
		models_[LeftArm].worldTransform_.rotation_.x -= kPreliminary_ArmRotationX / kPreliminaryCycle_;
		models_[RightArm].worldTransform_.rotation_.x -= kPreliminary_ArmRotationX / kPreliminaryCycle_;
		models_[Weapon].worldTransform_.rotation_.x -= kPreliminary_WeaponRotationX / kPreliminaryCycle_;
	} else if (attackAnimationFrame < kPreliminaryCycle_ + kPreliminaryWaitCycle_) {

	} else if (attackAnimationFrame < kPreliminaryCycle_ + kPreliminaryWaitCycle_ + kAttackCycle_) {
		models_[LeftArm].worldTransform_.rotation_.x += kPreliminary_ArmRotationX / kAttackCycle_;
		models_[RightArm].worldTransform_.rotation_.x += kPreliminary_ArmRotationX / kAttackCycle_;
		models_[Weapon].worldTransform_.rotation_.x += kPreliminary_WeaponRotationX / kAttackCycle_;
	} else if (attackAnimationFrame < kPreliminaryCycle_ + kPreliminaryWaitCycle_ + kAttackCycle_ + kAttackWaitCycle_) {
		
	} else {
		behaviorRequest_ = Behavior::kRoot;
	}

	attackAnimationFrame++;
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

	
	// Rトリガーを押していたら
	if (joyState.Gamepad.wButtons & XINPUT_GAMEPAD_RIGHT_SHOULDER) {
		// 攻撃
		behaviorRequest_ = Behavior::kAttack;
	}
}

void Player::SetModelNeutral() {
	models_[Body].worldTransform_.scale_ = {1.5f, 1.5f, 1.5f};
	
	models_[Head].worldTransform_.translation_ = {0.0f, 1.5f, 0.0f};
	models_[Body].worldTransform_.translation_ = {0.0f, 0.0f, 0.0f};
	models_[LeftArm].worldTransform_.translation_ = {-0.44f, 1.34f, 0.0f};
	models_[RightArm].worldTransform_.translation_ = {0.44f, 1.34f, 0.0f};
	models_[LeftArm].worldTransform_.rotation_ = {0.0f, 0.0f, 0.25f};
	models_[RightArm].worldTransform_.rotation_ = {0.0f, 0.0f, -0.25f};
	models_[Weapon].worldTransform_.translation_ = {0.0f, 1.0f, 0.0f};
	models_[Weapon].worldTransform_.rotation_ = {1.6f, 0.0f, 0.0f};
}


void Player::FloatingUpdate() {
	// パラメータを1ステップ分加算
	floatingParameter_ += (float)kFloatingStep_;
	// 2πを超えたら0に戻す
	floatingParameter_ = (float)std::fmod(floatingParameter_, 2.0f * M_PI);
	
	// 浮遊を座標に反映
	models_[Body].worldTransform_.translation_.y = std::sin(floatingParameter_) * kFloatingHeight;
}

void Player::ArmSwingUpdate() {
	// パラメータを1ステップ分加算
	armSwingParameter_ += (float)kArmSwingStep_;
	// 2πを超えたら0に戻す
	armSwingParameter_ = (float)std::fmod(armSwingParameter_, 2.0f * M_PI);

	// 浮遊を座標に反映
	models_[LeftArm].worldTransform_.rotation_.x = std::sin(armSwingParameter_) * kArmSwingHeight;
	models_[RightArm].worldTransform_.rotation_.x = std::sin(armSwingParameter_) * kArmSwingHeight;
}