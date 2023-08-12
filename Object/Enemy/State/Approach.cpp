#include "Approach.h"
#include "Leave.h"

// 更新処理（EnemyApproach）
void Approach::Update(Enemy* enemy) {
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
		enemy->ChangePhase(new Leave());
	}
}