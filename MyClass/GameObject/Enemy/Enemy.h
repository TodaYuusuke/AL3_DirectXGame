#pragma once
#include "Model.h"
#include "ViewProjection.h"
#include "WorldTransform.h"
#include <Input.h>

#include "EnemyState.h"
#include "EnemyBullet.h"

#include "../Collision/Collider.h"
#include "../MyClass/Utility/TimedCall/TimedCall.h"

class BaseEnemyState;
class GameScene;
class Player;

class Enemy : public Collider {

public: // メンバ関数
	// コンストラクタ
	Enemy();
	Enemy(Vector3 position);
	// デストラクタ
	~Enemy();

	/// <summary>
	/// 初期化
	/// </summary>
	void Initialize(Model* model, uint32_t textureHandle, Vector3 position);

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

	// 指定した移動量座標を変更する関数
	void Move(Vector3 speed) { worldTransform_.translation_ += speed; }
	/// <summary>
	/// 座標を取得
	/// </summary>
	Vector3 GetTranslation() { return worldTransform_.translation_; }
	// isAliveを受け取る
	bool isAlive() const { return isAlive_; }

	// 行動フェーズを変更する
	void ChangePhase(BaseEnemyState* newState);
	// 弾を発射してタイマーをリセットする関数
	void Fire();

	// ゲームシーンをセット
	void SetGameScene(GameScene* gameScene) { gameScene_ = gameScene; }
	// プレイヤーをセット
	void SetPlayer(Player* player) { player_ = player; }

public: // パブリックなメンバ変数
	
	//*　　定　数　　*//

	// 弾の発射間隔
	const int kFireInterval = 30;
	// 弾の速さ
	const float kBulletSpeed = 1.0f;

	// 当たり判定の半径
	const float kCollisionRadius = 3.0f;

	//*　　変　数　　*//

	// 発射処理を呼び出すコールバック
	TimedCall<void()>* timedCall_ = nullptr;

private: // メンバ変数

	// ゲームシーン
	GameScene* gameScene_ = nullptr;
	// 現在の行動フェーズ
	BaseEnemyState* phase_ = nullptr;
	// 自キャラ
	Player* player_ = nullptr;

	// デスフラグ
	bool isAlive_ = true;

	// ワールド変換データ
	WorldTransform worldTransform_;
	// モデル
	Model* model_ = nullptr;
	// テクスチャハンドル
	uint32_t textureHandle_ = 0u;
};
