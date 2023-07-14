#include "Player.h"
#include <cassert>
#include <ImGuiManager.h>

// コンストラクタ
Player::Player() {

}
// デストラクタ
Player::~Player() { 
	// 弾をDELETE
	for (PlayerBullet* bullet : bullets_) {
		delete bullet;
	}
}




void Player::Initialize(Model* model, uint32_t textureHandle, Vector3 position) {
	
	// NULLポインタチェック
	assert(model);

	// 衝突属性を設定
	SetCollisionAttribute(kCollisionAttributePlayer);
	SetCollisionMask(~kCollisionAttributePlayer);

	input_ = Input::GetInstance();

	// モデル
	model_ = model;
	textureHandle_ = textureHandle;

	// ワールドトランスフォ－ムの初期化
	worldTransform_.Initialize();
	worldTransform_.translation_ = position;
	worldTransform_.UpdateMatrix();
}



void Player::Update() {

	// 弾の発射判定
	Attack();

	// 弾更新
	for (PlayerBullet* bullet : bullets_){
		bullet->Update();
	}

	// デスフラグの立った弾を削除
	bullets_.remove_if([](PlayerBullet* bullet) {
		if (bullet->isDead()) {
			delete bullet;
			return true;
		}
		return false;
	});

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

/*
#pragma region ImGUI
	ImGui::Begin("Player");
	// 座標の入力ボックス
	float* t[3] = {
	    &worldTransform_.translation_.x,
	    &worldTransform_.translation_.y,
	    &worldTransform_.translation_.z,
	};
	ImGui::InputFloat3("translation", *t);
	ImGui::End();
#pragma endregion
*/
}



void Player::Draw(const ViewProjection& viewProjection) {
	model_->Draw(worldTransform_, viewProjection, textureHandle_);

	// 弾描画
	for (PlayerBullet* bullet : bullets_) {
		bullet->Draw(viewProjection);
	}
}

void Player::OnCollision() {
	// 何もしない
}

Vector3 Player::GetWorldPosition() { 
	Vector3 result;
	result.x = worldTransform_.matWorld_.m[3][0];
	result.y = worldTransform_.matWorld_.m[3][1];
	result.z = worldTransform_.matWorld_.m[3][2];
	return result;
}


/*ーーーーーーーーーーーーーー*/
/*　　　　　　関数　　　　　　*/
/*ーーーーーーーーーーーーーー*/


/// <summary>
/// 弾発射
/// </summary>
void Player::Attack() {

	if (input_->TriggerKey(DIK_SPACE)) {

		// 弾の速度
		Vector3 velocity(0, 0, kBulletSpeed);

		velocity = Matrix4x4::TransformNormal(velocity, Matrix4x4::MakeRotateMatrix(worldTransform_.rotation_));

		// 弾を生成し、初期化
		PlayerBullet* newBullet = new PlayerBullet();
		newBullet->Initialize(model_, GetWorldPosition(), velocity);

		// 弾を登録する
		bullets_.push_back(newBullet);
	}

}