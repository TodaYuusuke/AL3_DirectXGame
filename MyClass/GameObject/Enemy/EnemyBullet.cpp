#include "EnemyBullet.h"
#include "../Player/Player.h"

void EnemyBullet::Initialize(Model* model, const Vector3& position, const Vector3& velocity) {
	// NULLポインタチェック
	assert(model);

	model_ = model;
	// テクスチャ読み込み
	textureHandle_ = TextureManager::Load("EnemyBullet.png");

	// 衝突属性を設定
	SetCollisionAttribute(kCollisionAttributeEnemy);
	SetCollisionMask(~kCollisionAttributeEnemy);

	// ワールドトランスフォ－ムの初期化
	worldTransform_.Initialize();
	// 引数で受け取った初期座標をセット
	worldTransform_.translation_ = position;

	// 引数で受け取った速度を代入
	velocity_ = velocity;

	worldTransform_.scale_.x = 0.5f;
	worldTransform_.scale_.y = 0.5f;
	worldTransform_.scale_.z = 0.5f;
}

void EnemyBullet::Update() {

	// プレイヤーの方向へ誘導
	velocity_ = Slerp(
	    Normalize(velocity_), 
		Normalize(player_->GetWorldPosition() - worldTransform_.translation_),
	    0.01f
	);
	// Y軸周りの角度
	worldTransform_.rotation_.y = std::atan2f(velocity_.x, velocity_.z);
	// X軸周りの角度
	worldTransform_.rotation_.x = std::atan2f(-velocity_.y, Length({velocity_.x, 0, velocity_.z}));

	// 座標を移動させる
	worldTransform_.translation_ += velocity_;

	// ワールドトランスフォームの更新
	worldTransform_.UpdateMatrix();

	// 時間経過でデス
	if (--deathTimer_ <= 0) {
		isDead_ = true;
	}
}

void EnemyBullet::Draw(const ViewProjection& viewProjection) {
	model_->Draw(worldTransform_, viewProjection, textureHandle_);
}

void EnemyBullet::OnCollision() { 
	isDead_ = true;
}

Vector3 EnemyBullet::GetWorldPosition() { 
	Vector3 result;
	result.x = worldTransform_.matWorld_.m[3][0];
	result.y = worldTransform_.matWorld_.m[3][1];
	result.z = worldTransform_.matWorld_.m[3][2];
	return result;
}