#pragma once
#include "Model.h"
#include "WorldTransform.h"
#include "ViewProjection.h"
#include <Input.h>

class Player {

public: // メンバ関数

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
	void Draw(ViewProjection viewProjection);
	


private: // メンバ変数
	
	//*　　その他　　*//

	// キーボード入力
	Input* input_ = nullptr;


	//*　　定　数　　*//
	
	// キャラクターの移動速さ
	const float kCharacterSpeed = 0.2f;


	//*　　変　数　　*//

	// ワールド変換データ
	WorldTransform worldTransform_;
	// モデル
	Model* model_ = nullptr;
	// テクスチャハンドル
	uint32_t textureHandle_ = 0u;

};
