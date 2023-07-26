#include "Enemy.h"
#include <cassert>
#include "../Player/Player.h"
#include "../scene/GameScene.h"

// コンストラクタ
Enemy::Enemy() {

}
// デストラクタ
Enemy::~Enemy() {
	delete phase_;
	delete timedCall_;
}

/// <summary>
/// 初期化
/// </summary>
void Enemy::Initialize(Model* model, uint32_t textureHandle, Vector3 position) {

	// NULLポインタチェック
	assert(model);

	// モデル
	model_ = model;
	textureHandle_ = textureHandle;

	// 衝突属性を設定
	SetCollisionAttribute(kCollisionAttributeEnemy);
	SetCollisionMask(~kCollisionAttributeEnemy);

	// ワールドトランスフォ－ムの初期化
	worldTransform_.Initialize();
	worldTransform_.translation_ = position;

	// ワールドトランスフォームの更新
	worldTransform_.UpdateMatrix();
	
	// 最初の行動フェーズ
	ChangePhase(new EnemyApproach());
}

/// <summary>
/// 更新
/// </summary>
void Enemy::Update() {
	if (!isAlive_) {
		return;
	}

	// 行動フェーズごとの更新処理
	phase_->Update(this);

	// ワールドトランスフォームの更新
	worldTransform_.UpdateMatrix();
}

/// <summary>
/// 描画
/// </summary>
void Enemy::Draw(const ViewProjection& viewProjection) {
	if (!isAlive_) {
		return;
	}

	model_->Draw(worldTransform_, viewProjection, textureHandle_);
}

void Enemy::OnCollision() {
	// 何もしない
	isAlive_ = false;
}
Vector3 Enemy::GetWorldPosition() {
	Vector3 result;
	result.x = worldTransform_.matWorld_.m[3][0];
	result.y = worldTransform_.matWorld_.m[3][1];
	result.z = worldTransform_.matWorld_.m[3][2];
	return result;
}

/*ーーーーーーーーーーー*/
/*　　　その他関数　　　*/
/*ーーーーーーーーーーー*/


// 行動フェーズを変更する
void Enemy::ChangePhase(BaseEnemyState* newState) {
	delete phase_;
	phase_ = newState;
	// 初期化
	phase_->Initialize(this);
}

// 弾を発射
void Enemy::Fire() {
	// 弾の速度
	Vector3 velocity(0, 0, -kBulletSpeed);

	velocity = player_->GetWorldPosition() - GetWorldPosition();
	velocity = Normalize(velocity) * 0.5f;

	// 弾を生成し、初期化
	EnemyBullet* newBullet = new EnemyBullet();
	newBullet->Initialize(model_, worldTransform_.translation_, velocity);
	newBullet->SetPlayer(player_);

	// 弾を登録する
	gameScene_->AddEnemyBullet(newBullet);

	std::function<void()> f = std::bind(&Enemy::Fire, this);
	timedCall_ = new TimedCall<void()>(f, 30);
}