#pragma once
#include "Model.h"
#include "ViewProjection.h"
#include "WorldTransform.h"
#include <Input.h>

#include "./State/IState.h"

class IState;

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
	void ChangePhase(IState* newState);


private: // メンバ変数



	//*　　変　数　　*//

	// 現在の行動フェーズ
	IState* phase_ = nullptr;


	// ワールド変換データ
	WorldTransform worldTransform_;
	// モデル
	Model* model_ = nullptr;
	// テクスチャハンドル
	uint32_t textureHandle_ = 0u;
};
