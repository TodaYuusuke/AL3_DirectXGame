#include "Player.h"
#include <cassert>
#include <ImGuiManager.h>

void Player::Initialize(Model* model, uint32_t textureHandle) {
	
	// NULLポインタチェック
	assert(model);

	input_ = Input::GetInstance();

	// モデル
	model_ = model;
	textureHandle_ = textureHandle;

	// ワールドトランスフォ－ムの初期化
	worldTransform_.Initialize();
}



void Player::Update() {

	// 弾の発射判定
	Attack();

	// 弾更新
	if (bullet_) {
		bullet_->Update();
	}

// ーーーーーーーーーーーーーーーーーー//
#pragma region Translation処理
	// キャラクターの移動ベクトル
	Vector3 move = {0, 0, 0};

	// 押した方向で移動ベクトルを変更（左右）
	if (input_->PushKey(DIK_LEFT)) {
		move.x -= kCharacterSpeed;
	}
	if (input_->PushKey(DIK_RIGHT)) {
		move.x += kCharacterSpeed;
	}

	// 押した方向で移動ベクトルを変更（上下）
	if (input_->PushKey(DIK_UP)) {
		move.y += kCharacterSpeed;
	}
	if (input_->PushKey(DIK_DOWN)) {
		move.y -= kCharacterSpeed;
	}

	// 座標移動
	worldTransform_.translation_ += move;

	//*--　　移動限界　　--*//

	// 移動限界座標
	const float kMoveLimitX = 68 / 2;
	const float kMoveLimitY = 37 / 2;
	
	// 範囲を超えない処理
	worldTransform_.translation_.x =
	    std::clamp(worldTransform_.translation_.x, -kMoveLimitX, +kMoveLimitX);
	worldTransform_.translation_.y =
	    std::clamp(worldTransform_.translation_.y, -kMoveLimitY, +kMoveLimitY);
#pragma endregion
// ーーーーーーーーーーーーーーーーーー//
#pragma region rotation処理
	// 押した方向で移動ベクトルを変更
	if (input_->PushKey(DIK_A)) {
		worldTransform_.rotation_.y -= kRotSpeed;
	} else if (input_->PushKey(DIK_D)) {
		worldTransform_.rotation_.y += kRotSpeed;
	}
#pragma endregion
// ーーーーーーーーーーーーーーーーーー//
#pragma region scale処理
#pragma endregion
// ーーーーーーーーーーーーーーーーーー//

	// ワールドトランスフォームの更新
	worldTransform_.UpdateMatrix();

#pragma region ImGUI
	ImGui::Begin("Player");
	// 座標の入力ボックス
	float t[3] = {
	    worldTransform_.translation_.x,
	    worldTransform_.translation_.y,
	    worldTransform_.translation_.z,
	};
	ImGui::InputFloat3("translation", t);
	ImGui::End();
#pragma endregion
}



void Player::Draw(const ViewProjection& viewProjection) {
	model_->Draw(worldTransform_, viewProjection, textureHandle_);

	// 弾描画
	if (bullet_) {
		bullet_->Draw(viewProjection);
	}
}


/*ーーーーーーーーーーーーーー*/
/*　　　　　　関数　　　　　　*/
/*ーーーーーーーーーーーーーー*/


/// <summary>
/// 弾発射
/// </summary>
void Player::Attack() {
	
	if (input_->TriggerKey(DIK_SPACE)) {

		// 弾を生成し、初期化
		PlayerBullet* newBullet = new PlayerBullet();
		newBullet->Initialize(model_, worldTransform_.translation_);

		bullet_ = newBullet;
	}

}