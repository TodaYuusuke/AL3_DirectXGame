#pragma once
#include "ViewProjection.h"
#include "WorldTransform.h"
#include <vector>

#include "../math/Vector3.h"

class RailCamera {
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
	/// 描画
	/// </summary>
	void Draw();


	/// <summary>
	/// ワールドトランスフォームを取得
	/// </summary>
	const WorldTransform& GetWorldTransform() { return worldTransform_; }
	/// <summary>
	/// ビュープロジェクションを取得
	/// </summary>
	const ViewProjection& GetViewProjection() { return viewProjection_; }

private: // メンバ変数

	// ワールド変換データ
	WorldTransform worldTransform_;
	// ビュープロジェクション
	ViewProjection viewProjection_;
	
	// スプライン曲線制御点
	std::vector<Vector3> controlPoints_;

	// 補間
	float t;
};