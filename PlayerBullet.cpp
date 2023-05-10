#include "PlayerBullet.h"

/// <summary>
/// 初期化
/// </summary>
void PlayerBullet::Initialize(Model* model, const Vector3& textureHandle) { 
	// NULLポインタチェック
	assert(model);

	model_ = model;
	// テクスチャ読み込み
	textureHandle_ = TextureManager::Load("bullet.png");

	// ワールドトランスフォ－ムの初期化
	worldTransform_.Initialize();
	// 引数で受け取った初期座標をセット
	worldTransform_.translation_ = textureHandle;

}

/// <summary>
/// 更新
/// </summary>
void PlayerBullet::Update() {


	// ワールドトランスフォームの更新
	worldTransform_.UpdateMatrix();
}

/// <summary>
/// 描画
/// </summary>
void PlayerBullet::Draw(const ViewProjection& viewProjection) {
	model_->Draw(worldTransform_, viewProjection, textureHandle_);
}