#pragma once
#include "Model.h"
#include "ViewProjection.h"
#include "WorldTransform.h"
#include <Input.h>


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

private: // 関数
	
	// 接近する更新処理
	void UpdateApproach();
	// 離脱する更新処理
	void UpdateLeave();

private: // メンバ変数

	// メンバ関数ポインタのテーブル
	static void (Enemy::*spFuncTable[])();

	//*　　定　数　　*//

	// 接近　速さ
	const Vector3 kApproachSpeed = {0, 0, -0.5f};
	// 撤退　速さ
	const Vector3 kLeaveSpeed = {-0.2f, 0.2f, 0};


	//*　　変　数　　*//

	
	// 行動フェーズ
	enum class Phase {
		Approach, // 接近する
		Leave,    // 離脱する
	};

	// 現在のフェーズ
	Phase phase_ = Phase::Approach;


	// ワールド変換データ
	WorldTransform worldTransform_;
	// モデル
	Model* model_ = nullptr;
	// テクスチャハンドル
	uint32_t textureHandle_ = 0u;
};
