#include "Enemy.h"
#include <cassert>
#include "../Player/Player.h"

// コンストラクタ
Enemy::Enemy() {

}
// デストラクタ
Enemy::~Enemy() {
	delete phase_;
	// 弾をDELETE
	for (EnemyBullet* bullet : bullets_) {
		delete bullet;
	}
	delete timedCall_;
}

/// <summary>
/// 初期化
/// </summary>
void Enemy::Initialize(Model* model, uint32_t textureHandle) {

	// NULLポインタチェック
	assert(model);


	// モデル
	model_ = model;
	textureHandle_ = textureHandle;

	// ワールドトランスフォ－ムの初期化
	worldTransform_.Initialize();
	worldTransform_.translation_ = {20, 3, 50};

	// ワールドトランスフォームの更新
	worldTransform_.UpdateMatrix();
	
	// 最初の行動フェーズ
	ChangePhase(new EnemyApproach());
}

/// <summary>
/// 更新
/// </summary>
void Enemy::Update() {
	// 行動フェーズごとの更新処理
	phase_->Update(this);

	// 弾更新
	for (EnemyBullet* bullet : bullets_) {
		bullet->Update();
	}

	// デスフラグの立った弾を削除
	bullets_.remove_if([](EnemyBullet* bullet) {
		if (bullet->isDead()) {
			delete bullet;
			return true;
		}
		return false;
	});

	// ワールドトランスフォームの更新
	worldTransform_.UpdateMatrix();
}

/// <summary>
/// 描画
/// </summary>
void Enemy::Draw(const ViewProjection& viewProjection) {
	// 弾描画
	for (EnemyBullet* bullet : bullets_) {
		bullet->Draw(viewProjection);
	}

	model_->Draw(worldTransform_, viewProjection, textureHandle_);
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
	bullets_.push_back(newBullet);

	std::function<void()> f = std::bind(&Enemy::Fire, this);
	timedCall_ = new TimedCall<void()>(f, 30);
}