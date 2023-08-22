#pragma once
#include "ViewProjection.h"
#include "WorldTransform.h"

class FollowCamera {
public: // メンバ関数
	
	/// <summary>
	/// 初期化
	/// </summary>
	void Initialize();
	/// <summary>
	/// 更新
	/// </summary>
	void Update();

	/// <summary>
	/// 追従対象をセット
	/// </summary>
	void SetTarget(const WorldTransform* target) { target_ = target; }
	/// <summary>
	/// ビュープロジェクションを取得
	/// </summary>
	const ViewProjection& GetViewProjection() { return viewProjection_; }


private: // メンバ定数

	const float kCameraTurnSpeed = 0.02f;

private: // メンバ変数
	// ビュープロジェクション
	ViewProjection viewProjection_;

	// 追従対象
	const WorldTransform* target_ = nullptr;
	// カメラの角度
	Vector3 rotation_;
};