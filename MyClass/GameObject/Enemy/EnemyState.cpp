	#include "EnemyState.h"

// 初期化（EnemyApproach）
void EnemyApproach::Initialize(Enemy* enemy) {
	// 弾初期化
	enemy->bullets_.clear();
	enemy->fireTimer_ = enemy->kFireInterval;
}
// 更新処理（EnemyApproach）
void EnemyApproach::Update(Enemy* enemy) {
	// 移動
	enemy->Move(kApproachSpeed);

	// 発射タイマーをデクリメント
	enemy->fireTimer_--;
	if (enemy->fireTimer_ <= 0) {
		enemy->Fire();
		enemy->fireTimer_ = enemy->kFireInterval;
	}


	// 規定の位置に到達したら離脱
	if (enemy->GetTranslation().z < 0.0f) {
		enemy->ChangePhase(new EnemyLeave());
	}
}


// 初期化（EnemyApproach）
void EnemyLeave::Initialize(Enemy* enemy) {
	// 現段階では処理なし
	enemy;
}
// 更新処理（EnemyLeave）
void EnemyLeave::Update(Enemy* enemy) {
	// 移動
	enemy->Move(kLeaveSpeed);
};