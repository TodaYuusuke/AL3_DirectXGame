#pragma once
#include "Model.h"
#include "WorldTransform.h"
#include "ViewProjection.h"

#define _USE_MATH_DEFINES
#include <math.h>

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

	enum Parts {
		Head,
		Body,
		LeftArm,
		RightArm,
	};

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

private: // アニメーション関連
	// 関数
	void InitializeAnimation();
	void Animation();

	// 浮遊ギミック
	const uint16_t kFloatingCycle_ = 120;
	const double kFloatingStep_ = 2.0f * M_PI / kFloatingCycle_;	
	const float kFloatingHeight = 0.2f;
	float floatingParameter_ = 0.0f;
	void FloatingUpdate();
};
