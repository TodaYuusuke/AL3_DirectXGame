#include "Enemy.h"
#include <cassert>
#include <ImGuiManager.h>

// コンストラクタ
Enemy::Enemy() {

}
// デストラクタ
Enemy::~Enemy() {
	delete phase_;
}

/// <summary>
/// 初期化
/// </summary>
void Enemy::Initialize(Model* model, uint32_t textureHandle) {

	// NULLポインタチェック
	assert(model);

	// 最初の行動フェーズ
	phase_ = new EnemyApproach();

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
	// 行動フェーズごとの更新処理
	phase_->Update(this);

	// ワールドトランスフォームの更新
	worldTransform_.UpdateMatrix();
}

/// <summary>
/// 描画
/// </summary>
void Enemy::Draw(const ViewProjection& viewProjection) {
	model_->Draw(worldTransform_, viewProjection, textureHandle_);
}



/*ーーーーーーーーーーー*/
/*　　　その他関数　　　*/
/*ーーーーーーーーーーー*/



// 行動フェーズを変更する
void Enemy::ChangePhase(BaseEnemyState* newState) {
	delete phase_;
	phase_ = newState;
}