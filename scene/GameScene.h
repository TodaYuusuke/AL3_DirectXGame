#pragma once

#include "Audio.h"
#include "DirectXCommon.h"
#include "Input.h"
#include "Model.h"
#include "SafeDelete.h"
#include "Sprite.h"
#include "ViewProjection.h"
#include "WorldTransform.h"

#include <sstream>

#include "DebugCamera.h"
#include "MyClass/GameObject/RailCamera/RailCamera.h"

#include "MyClass/GameObject/Player/Player.h"
#include "MyClass/GameObject/Enemy/Enemy.h"
#include "MyClass/GameObject/Skydome/Skydome.h"
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

	/// <summary>
	/// 敵を追加する
	/// </summary>
	/// <param name="enemy">初期座標</param>
	void AddEnemy(Vector3 position);

	/// <summary>
	/// 敵弾を追加する
	/// </summary>
	/// <param name="enemyBullet">敵弾</param>
	void AddEnemyBullet(EnemyBullet* enemyBullet);

	/// <summary>
	/// 敵発生データの読み込み
	/// </summary>
	void LoadEnemyPopData();

	/// <summary>
	/// 敵発生コマンドの更新
	/// </summary>
	void UpdateEnemyPopCommands();

private: // メンバ変数
	DirectXCommon* dxCommon_ = nullptr;
	Input* input_ = nullptr;
	Audio* audio_ = nullptr;

	/// <summary>
	/// ゲームシーン用
	/// </summary>

	// *** テクスチャハンドルとモデル *** //

	// プレイヤー
	uint32_t playerTexture = 0;
	Model* playerModel = nullptr;

	// エネミー
	uint32_t enemyTexture = 0;
	Model* enemyModel = nullptr;

	// スカイドーム
	Model* skydomeModel = nullptr;

	// ビュープロジェクション
	ViewProjection viewProjection_;

	// デバッグカメラ有効
	bool isDebugCameraActive_ = false;
	// デバッグカメラ
	DebugCamera* debugCamera_ = nullptr;
	// レールカメラ
	RailCamera* railCamera_ = nullptr;

	// 当たり判定マネージャー
	CollisionManager* collisionManager_ = nullptr;
	// 天球
	Skydome* skydome_ = nullptr;

	// 自キャラ
	Player* player_ = nullptr;
	// 敵のリスト
	std::list<Enemy*> enemys_;
	// 敵弾のリスト
	std::list<EnemyBullet*> enemyBullets_;

	// ファイル読み取り
	std::stringstream enemyPopCommands;
	// 待機中フラグ
	bool isWaiting = false;
	// 待機中タイマー
	int waitTimer = 0;

private: // メンバ関数
};
