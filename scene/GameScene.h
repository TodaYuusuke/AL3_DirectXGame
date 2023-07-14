#pragma once

#include "Audio.h"
#include "DirectXCommon.h"
#include "Input.h"
#include "Model.h"
#include "SafeDelete.h"
#include "Sprite.h"
#include "ViewProjection.h"
#include "WorldTransform.h"
#include "DebugCamera.h"

#include "MyClass/GameObject/Player/Player.h"
#include "MyClass/GameObject/Enemy/Enemy.h"
#include "MyClass/GameObject/Collision/CollisionManager.h"

/// <summary>
/// ゲームシーン
/// </summary>
class GameScene {

public: // メンバ関数
	/// <summary>
	/// コンストクラタ
	/// </summary>
	GameScene();

	/// <summary>
	/// デストラクタ
	/// </summary>
	~GameScene();

	/// <summary>
	/// 初期化
	/// </summary>
	void Initialize();

	/// <summary>
	/// 毎フレーム処理
	/// </summary>
	void Update();

	/// <summary>
	/// 描画
	/// </summary>
	void Draw();

private: // メンバ変数
	DirectXCommon* dxCommon_ = nullptr;
	Input* input_ = nullptr;
	Audio* audio_ = nullptr;

	/// <summary>
	/// ゲームシーン用
	/// </summary>
	
	// プレイヤー
	
	// テクスチャハンドル
	uint32_t playerTexture = 0;
	// 3Dモデルデータ
	Model* playerModel = nullptr;
	
	// エネミー

	// テクスチャハンドル
	uint32_t enemyTexture = 0;
	// 3Dモデルデータ
	Model* enemyModel = nullptr;


	// ビュープロジェクション
	ViewProjection viewProjection_;


	// デバッグカメラ有効
	bool isDebugCameraActive_ = false;
	// デバッグカメラ
	DebugCamera* debugCamera_ = nullptr;

	// 当たり判定マネージャー
	CollisionManager* collisionManager_ = nullptr;

	// 自キャラ
	Player* player_ = nullptr;
	// 敵
	Enemy* enemy_ = nullptr;

private: // メンバ関数
};
