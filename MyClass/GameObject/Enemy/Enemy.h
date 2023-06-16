#pragma once
#include "Model.h"
#include "ViewProjection.h"
#include "WorldTransform.h"
#include <Input.h>

#include "EnemyState.h"
#include "EnemyBullet.h"

#include "../MyClass/Utility/TimedCall/TimedCall.h"

class BaseEnemyState;

class Enemy {

public: // メンバ関数
	    // コンストラクタ
	Enemy();
	// デストラクタ
	~Enemy();

	/// <summary>
	/// 初期化
	/// </summary>
	void Initialize(Model* model, uint32_t textureHandle);

	/// <summary>
	/// 更新
	/// </summary>
	void Update();

	/// <summary>
	/// 描画
	/// </summary>
	void Draw(const ViewProjection& viewProjection);
	

	// 指定した移動量座標を変更する関数
	void Move(Vector3 speed) { worldTransform_.translation_ += speed; }
	// 座標のゲッター
	Vector3 GetTranslation() { return worldTransform_.translation_; }

	// 行動フェーズを変更する
	void ChangePhase(BaseEnemyState* newState);
	// 弾を発射してタイマーをリセットする関数
	void Fire();


public: // パブリックなメンバ変数
	
	//*　　定　数　　*//

	// 弾の発射間隔
	const int kFireInterval = 30;
	// 弾の速さ
	const float kBulletSpeed = 1.0f;

	//*　　変　数　　*//

	// 弾
	std::list<EnemyBullet*> bullets_;
	// 発射処理を呼び出すコールバック
	TimedCall<void()>* timedCall_ = nullptr;

private: // メンバ変数

	// 現在の行動フェーズ
	BaseEnemyState* phase_ = nullptr;

	// ワールド変換データ
	WorldTransform worldTransform_;
	// モデル
	Model* model_ = nullptr;
	// テクスチャハンドル
	uint32_t textureHandle_ = 0u;
};
