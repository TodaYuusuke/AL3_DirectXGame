#include "Enemy.h"
#include <cassert>
#include <ImGuiManager.h>

// コンストラクタ
Enemy::Enemy() {

}
// デストラクタ
Enemy::~Enemy() {

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

	worldTransform_.translation_ = {0, 3, 50};
}

/// <summary>
/// 更新
/// </summary>
void Enemy::Update() {

	// メンバ関数ポインタに入っている関数を呼び出す
	(this->*spFuncTable[static_cast<size_t>(phase_)])();

	// ワールドトランスフォームの更新
	worldTransform_.UpdateMatrix();
}

/// <summary>
/// 描画
/// </summary>
void Enemy::Draw(const ViewProjection& viewProjection) {
	model_->Draw(worldTransform_, viewProjection, textureHandle_);
}



/*ーーーーーーーーーーーーーーー*/
/*　　　　　その他関数　　　　　*/
/*ーーーーーーーーーーーーーーー*/

// 接近する更新処理
void Enemy::UpdateApproach() {

// ーーーーーーーーーーーーーーーーーー//
#pragma region Translation処理
	// 移動
	worldTransform_.translation_ += kApproachSpeed;
#pragma endregion
// ーーーーーーーーーーーーーーーーーー//
#pragma region rotation処理
#pragma endregion
// ーーーーーーーーーーーーーーーーーー//
#pragma region scale処理
#pragma endregion
// ーーーーーーーーーーーーーーーーーー//
 
	// 規定の位置に到達したら離脱
	if (worldTransform_.translation_.z < 0.0f) {
		phase_ = Phase::Leave;
	}
}
// 離脱する更新処理
void Enemy::UpdateLeave() {

// ーーーーーーーーーーーーーーーーーー//
#pragma region Translation処理
	// 移動
	worldTransform_.translation_ += kLeaveSpeed;
#pragma endregion
// ーーーーーーーーーーーーーーーーーー//
#pragma region rotation処理
#pragma endregion
// ーーーーーーーーーーーーーーーーーー//
#pragma region scale処理
#pragma endregion
// ーーーーーーーーーーーーーーーーーー//
}



// メンバ関数ポインタのテーブルの実態
void (Enemy::*Enemy::spFuncTable[])() = {
	&Enemy::UpdateApproach,
	&Enemy::UpdateLeave
};