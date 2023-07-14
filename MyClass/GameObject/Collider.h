#pragma once
#include "../math/Vector3.h"

class Collider {
public: // メンバ関数

	// 衝突時に呼ばれる関数
	virtual void OnCollision() = 0;
	// ワールド座標を取得
	virtual Vector3 GetWorldPosition() = 0;

	// 半径の取得
	float GetRadius() { return radius_; }
	// 半径の設定
	void SetRadius(float radius) { radius_ = radius; }

private: // メンバ変数
	// 衝突半径
	float radius_ = 1;
};