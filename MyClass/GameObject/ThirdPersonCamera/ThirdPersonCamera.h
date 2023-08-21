#pragma once
#include "ViewProjection.h"
#include "WorldTransform.h"

class ThirdPersonCamera {
public: // メンバ関数
	
	/// <summary>
	/// 初期化
	/// </summary>
	void Initialize(Vector3 worldPosition, Vector3 radian);
	/// <summary>
	/// 更新
	/// </summary>
	void Update();

	/// <summary>
	/// 追従対象をセット
	/// </summary>
	void SetParent();
	/// <summary>
	/// ビュープロジェクションを取得
	/// </summary>
	const ViewProjection& GetViewProjection() { return viewProjection_; }

	WorldTransform worldTransform_;

private: // メンバ変数
	// ワールド変換データ
	// ビュープロジェクション
	ViewProjection viewProjection_;
};