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

	input_ = Input::GetInstance();

	// モデル
	model_ = model;
	textureHandle_ = textureHandle;

	// ワールドトランスフォ－ムの初期化
}

/// <summary>
/// 更新
/// </summary>
void Enemy::Update() {

// ーーーーーーーーーーーーーーーーーー//
#pragma region Translation処理
	// 移動ベクトル
	Vector3 move = {0, 0, -1};

	// 座標移動
	//worldTransform_.translation_ += move;
#pragma endregion
// ーーーーーーーーーーーーーーーーーー//
#pragma region rotation処理
#pragma endregion
// ーーーーーーーーーーーーーーーーーー//
#pragma region scale処理
#pragma endregion
	// ーーーーーーーーーーーーーーーーーー//

	// ワールドトランスフォームの更新
	worldTransform_.UpdateMatrix();
}

/// <summary>
/// 描画
/// </summary>
void Enemy::Draw(const ViewProjection& viewProjection) {
	model_->Draw(worldTransform_, viewProjection, textureHandle_);
}