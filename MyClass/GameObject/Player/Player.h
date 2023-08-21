#pragma once
#include "Model.h"
#include "WorldTransform.h"
#include "ViewProjection.h"

class Player {

public: // メンバ関数

	/// <summary>
	/// 初期化
	/// </summary>
	void Initialize(Model* head, Model* body, Model* Larm, Model* Rarm, Vector3 position);

	/// <summary>
	/// 更新
	/// </summary>
	void Update();

	/// <summary>
	/// 描画
	/// </summary>
	void Draw(ViewProjection viewProjection);
	
	/// <summary>
	/// ワールドトランスフォームのポインタを受け取る
	/// </summary>
	/// <returns></returns>
	WorldTransform* GetWorldTransform() { return &worldTransform_; }

private: // メンバ変数
	
	// ワールド変換データ
	WorldTransform worldTransform_;

	// 各モデル用のワールド変換データ
	WorldTransform modelTransform_[4];
	// モデル
	Model* headModel_ = nullptr;
	Model* bodyModel_ = nullptr;
	Model* leftArmModel_ = nullptr;
	Model* rightArmModel_ = nullptr;

};
