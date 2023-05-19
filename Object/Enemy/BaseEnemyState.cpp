#include "BaseEnemyState.h"


// 更新処理（EnemyApproach）
void EnemyApproach::Update(Enemy* enemy) {
// ーーーーーーーーーーーーーーーーーー//
#pragma region Translation処理
	// 移動
	enemy->Move(kApproachSpeed);
#pragma endregion
// ーーーーーーーーーーーーーーーーーー//
#pragma region rotation処理
#pragma endregion
// ーーーーーーーーーーーーーーーーーー//
#pragma region scale処理
#pragma endregion
	// ーーーーーーーーーーーーーーーーーー//

	// 規定の位置に到達したら離脱
	if (enemy->GetTranslation().z < 0.0f) {
		enemy->ChangePhase(new EnemyLeave());
	}
}


// 更新処理（EnemyLeave）
void EnemyLeave::Update(Enemy* enemy) {
// ーーーーーーーーーーーーーーーーーー//
#pragma region Translation処理
	// 移動
	enemy->Move(kLeaveSpeed);
#pragma endregion
// ーーーーーーーーーーーーーーーーーー//
#pragma region rotation処理
#pragma endregion
// ーーーーーーーーーーーーーーーーーー//
#pragma region scale処理
#pragma endregion
	// ーーーーーーーーーーーーーーーーーー//
};