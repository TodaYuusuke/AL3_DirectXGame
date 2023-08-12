#include "Leave.h"

// 更新処理（EnemyLeave）
void Leave::Update(Enemy* enemy) {
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