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
#include "MyClass/GameObject/FollowCamera/FollowCamera.h"
#include "../MyClass/GameObject/Field/Skydome/Skydome.h"
#include "../MyClass/GameObject/Field/Ground/Ground.h"

#include "../MyClass/GameObject/Character/Player/Player.h"
#include "../MyClass/GameObject/Character/Enemy/Enemy.h"
#include <memory>

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

	// ビュープロジェクション
	ViewProjection viewProjection_;


	// 3Dモデルデータ
	std::unique_ptr<Model> playerBodyModel_ = nullptr;
	std::unique_ptr<Model> playerHeadModel_ = nullptr;
	std::unique_ptr<Model> playerLeftArmModel_ = nullptr;
	std::unique_ptr<Model> playerRightArmModel_ = nullptr;

	std::unique_ptr<Model> enemyBodyModel_ = nullptr;
	std::unique_ptr<Model> enemyLeftWheelModel_ = nullptr;
	std::unique_ptr<Model> enemyRightWheelModel_ = nullptr;

	std::unique_ptr<Model> skydomeModel_ = nullptr;
	std::unique_ptr<Model> groundModel_ = nullptr;


	// デバッグカメラ有効
	bool isDebugCameraActive_ = false;
	// デバッグカメラ
	std::unique_ptr<DebugCamera> debugCamera_ = nullptr;
	// 三人称カメラ
	std::unique_ptr<FollowCamera> followCamera_ = nullptr;

	// スカイドーム
	std::unique_ptr<Skydome> skydome_ = nullptr;
	// グラウンド
	std::unique_ptr<Ground> ground_ = nullptr;

	// 自キャラ
	std::unique_ptr<Player> player_ = nullptr;
	// 敵
	std::unique_ptr<Enemy> enemy_ = nullptr;
};
