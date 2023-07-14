#pragma once
#include "Model.h"
#include "WorldTransform.h"
#include "ViewProjection.h"

class PlayerBullet 
{
public: // メンバ関数

	/// <summary>
	/// 初期化
	/// </summary>
	void Initialize(Model* model, const Vector3& position, const Vector3& velocity);

	/// <summary>
	/// 更新
	/// </summary>
	void Update();

	/// <summary>
	/// 描画
	/// </summary>
	void Draw(const ViewProjection& viewProjection);

	/// <summary>
	/// 衝突を検出したら呼び出されるコールバック関数
	/// </summary>
	void OnCollision();

	/// <summary>
	/// ワールド座標を取得
	/// </summary>
	Vector3 GetWorldPosition();	
	// isDeadを受け取る
	bool isDead() const { return isDead_; }


private: // メンバ変数

	//*　　定　数　　*//

	static const int32_t kLifeTime = 60 * 5;

	//*　　変　数　　*//

	// ワールド変換データ
	WorldTransform worldTransform_;
	// モデル
	Model* model_ = nullptr;
	// テクスチャハンドル
	uint32_t textureHandle_ = 0u;


	// 速度
	Vector3 velocity_;

	// デスタイマー
	int32_t deathTimer_ = kLifeTime;
	// デスフラグ
	bool isDead_ = false;
};
