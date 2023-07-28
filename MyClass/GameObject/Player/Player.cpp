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
	delete sprite2DReticle_;
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

	// 3Dレティクルのワールドトランスフォーム初期化
	worldTransform3DReticle_.Initialize();
	worldTransform3DReticle_.translation_.z += 50.0f;
	worldTransform3DReticle_.parent_ = &worldTransform_;
	worldTransform3DReticle_.UpdateMatrix();

	// 2Dレティクル用テクスチャ取得
	uint32_t textureReticle = TextureManager::Load("Reticle.png");
	// スプライト生成
	sprite2DReticle_ = Sprite::Create(textureReticle, {0,0}, {1,1,1,1}, {0.5f, 0.5f});
}



void Player::Update(const ViewProjection& viewProjection) {

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

	// 3Dレティクルのワールド座標から2Dレティクルのスクリーン座標を計算
	worldTransform3DReticle_.UpdateMatrix();

	Vector3 positionReticle = worldTransform3DReticle_.GetWorldPosition();

	// ビューポート行列
	Matrix4x4 matViewport = Matrix4x4::CreateViewportMatrix(0, 0, WinApp::kWindowWidth, WinApp::kWindowHeight, 0, 1);
	// ビュー行列とプロジェクション行列、ビューポート行列を合成する
	Matrix4x4 matViewProjectionViewport = viewProjection.matView * viewProjection.matProjection * matViewport;
	// ワールド→スクリーン座標変換（ここで3Dから2Dになる）
	positionReticle = Matrix4x4::TransformCoord(positionReticle, matViewProjectionViewport);
	// スプライトのレティクルに座標を設定
	sprite2DReticle_->SetPosition(Vector2(positionReticle.x, positionReticle.y));
}



void Player::Draw(const ViewProjection& viewProjection) {
	model_->Draw(worldTransform_, viewProjection, textureHandle_);

	// 弾描画
	for (PlayerBullet* bullet : bullets_) {
		bullet->Draw(viewProjection);
	}
}
void Player::DrawUI() {
	sprite2DReticle_->Draw();
}


void Player::OnCollision() {
	// 何もしない
}

Vector3 Player::GetWorldPosition() { return worldTransform_.GetWorldPosition(); }


/*ーーーーーーーーーーーーーー*/
/*　　　　　　関数　　　　　　*/
/*ーーーーーーーーーーーーーー*/


/// <summary>
/// 弾発射
/// </summary>
void Player::Attack() {

	if (input_->TriggerKey(DIK_SPACE)) {

		// 弾の速度
		Vector3 velocity{};

		velocity = worldTransform3DReticle_.GetWorldPosition() - worldTransform_.GetWorldPosition();
		velocity = Normalize(velocity) * kBulletSpeed;
		//velocity = Matrix4x4::TransformNormal(velocity, Matrix4x4::MakeRotateMatrix(worldTransform_.rotation_));

		// 弾を生成し、初期化
		PlayerBullet* newBullet = new PlayerBullet();
		newBullet->Initialize(model_, GetWorldPosition(), velocity);

		// 弾を登録する
		bullets_.push_back(newBullet);
	}

}