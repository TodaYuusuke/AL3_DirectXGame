#pragma once
#include "Model.h"
#include "WorldTransform.h"
#include "ViewProjection.h"
#include <Input.h>
#include <list>

#include "../Collider.h"
#include "PlayerBullet.h"

class Player : public Collider {
public: // メンバ関数

	// コンストラクタ
	Player();
	// デストラクタ
	~Player();


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

	/// <summary>
	/// 衝突を検出したら呼び出されるコールバック関数
	/// </summary>
	void OnCollision() override;
	/// <summary>
	/// ワールド座標を取得
	/// </summary>
	Vector3 GetWorldPosition() override;

	/// <summary>
	/// 弾リストを取得
	/// </summary>
	const std::list<PlayerBullet*>& GetBullets() const { return bullets_; }

	//*　公開する定数　*//

	// 当たり判定の半径
	const float kCollisionRadius = 3.0f;

private: // 関数

	/// <summary>
	/// 弾発射
	/// </summary>
	void Attack();


private: // メンバ変数
	
	//*　　その他　　*//

	// キーボード入力
	Input* input_ = nullptr;


	//*　　定　数　　*//
	
	// キャラクターの移動速さ
	const float kCharacterSpeed = 0.2f;
	// キャラクターの回転の速さ
	const float kRotSpeed = 0.02f;

	// 弾の速さ
	const float kBulletSpeed = 1.0f;

	//*　　変　数　　*//

	// ワールド変換データ
	WorldTransform worldTransform_;
	// モデル
	Model* model_ = nullptr;
	// テクスチャハンドル
	uint32_t textureHandle_ = 0u;


	// 弾
	std::list<PlayerBullet*> bullets_;
};
