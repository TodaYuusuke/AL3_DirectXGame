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
	const WorldTransform& GetWorldTransform() { return worldTransform_; }

	void SetViewProjection(const ViewProjection* viewProjection) { viewProjection_ = viewProjection; }

private: // メンバ定数
	float kCharacterSpeed = 0.3f;

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

	// カメラのビュープロジェクション
	const ViewProjection* viewProjection_ = nullptr;

private: // プライベートな関数
	
	// コントローラーでの操作
	void MoveJoyStick();

};
