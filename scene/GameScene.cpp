#include "GameScene.h"
#include "TextureManager.h"
#include "AxisIndicator.h"
#include <cassert>
#include <ImGuiManager.h>

GameScene::GameScene() {}

GameScene::~GameScene() {
	delete playerModel;
	delete enemyModel;
	delete skydomeModel;
	delete debugCamera_;
	delete collisionManager_;
	delete player_;
	delete enemy_;
}

void GameScene::Initialize() {

	dxCommon_ = DirectXCommon::GetInstance();
	input_ = Input::GetInstance();
	audio_ = Audio::GetInstance();

	
	// プレイヤー
	playerTexture = TextureManager::Load("sample.png");
	playerModel = Model::Create();

	// エネミー
	enemyTexture = TextureManager::Load("enemy.png");
	enemyModel = Model::Create();

	// スカイドーム
	skydomeModel = Model::CreateFromOBJ("skydome", true);

	// ビュープロジェクション
	viewProjection_.Initialize();

	// デバッグカメラの生成
	debugCamera_ = new DebugCamera(1280, 720);
	// 軸方向表示を有効にする
	AxisIndicator::GetInstance()->SetVisible(true);
	// 軸方向表示が参照するビュープロジェクションを指定する（アドレス渡し）
	AxisIndicator::GetInstance()->SetTargetViewProjection(&viewProjection_);

	// 当たり判定マネージャーの生成
	collisionManager_ = new CollisionManager();
	// 天球の生成
	skydome_ = new Skydome();
	// 天球の初期化
	skydome_->Initialize(skydomeModel);

	// 自キャラの生成
	player_ = new Player();
	// 自キャラの初期化
	player_->Initialize(playerModel, playerTexture);

	// 敵の生成
	enemy_ = new Enemy();
	// 敵の初期化
	enemy_->SetPlayer(player_);
	enemy_->Initialize(enemyModel, enemyTexture);
}

void GameScene::Update() {

	// 当たり判定マネージャーの初期化
	collisionManager_->ClearList();

	// デバッグ切り替え
#ifdef _DEBUG
	// 右altキーで切り替え
	if (input_->TriggerKey(DIK_RALT)) {
		isDebugCameraActive_ = !isDebugCameraActive_;
	}
	// リトライ
	if (input_->TriggerKey(DIK_R)) {
		Initialize();
		return;
	}
#endif // DEBUG
	// デバッグカメラ更新
	if (isDebugCameraActive_) {
		debugCamera_->Update();
		ViewProjection v = debugCamera_->GetViewProjection();
		viewProjection_.matView = v.matView;
		viewProjection_.matProjection = v.matProjection;
		// ビュープロジェクション行列の転送
		viewProjection_.TransferMatrix();
	} else {
		// ビュープロジェクション行列の更新と転送
		viewProjection_.UpdateMatrix();
	}
	// 自キャラの更新
	player_->Update();

	// 敵の更新
	if (enemy_ != nullptr) {
		enemy_->Update();
	}

	// 当たり判定を登録
	collisionManager_->PushCollider(player_);
	collisionManager_->PushCollider(enemy_);
	// 弾リストの取得
	const std::list<PlayerBullet*>& playerBullets = player_->GetBullets();
	const std::list<EnemyBullet*>& enemyBullets = enemy_->GetBullets();
	// 自弾の全ての当たり判定
	for (PlayerBullet* bullet : playerBullets) {
		collisionManager_->PushCollider(bullet);
	}
	// 敵弾の全ての当たり判定
	for (EnemyBullet* bullet : enemyBullets) {
		collisionManager_->PushCollider(bullet);
	}

	collisionManager_->CheckAllCollisions();
}

void GameScene::Draw() {

	// コマンドリストの取得
	ID3D12GraphicsCommandList* commandList = dxCommon_->GetCommandList();

#pragma region 背景スプライト描画
	// 背景スプライト描画前処理
	Sprite::PreDraw(commandList);

	/// <summary>
	/// ここに背景スプライトの描画処理を追加できる
	/// </summary>

	// スプライト描画後処理
	Sprite::PostDraw();
	// 深度バッファクリア
	dxCommon_->ClearDepthBuffer();
#pragma endregion

#pragma region 3Dオブジェクト描画
	// 3Dオブジェクト描画前処理
	Model::PreDraw(commandList);

	/// <summary>
	/// ここに3Dオブジェクトの描画処理を追加できる
	/// </summary>
	
	// 天球の描画
	skydome_->Draw(viewProjection_);
	
	// 敵の描画
	if (enemy_ != nullptr) {
		enemy_->Draw(viewProjection_);
	}
	
	// 自キャラの描画
	player_->Draw(viewProjection_);

	// 3Dオブジェクト描画後処理
	Model::PostDraw();
#pragma endregion

#pragma region 前景スプライト描画
	// 前景スプライト描画前処理
	Sprite::PreDraw(commandList);

	/// <summary>
	/// ここに前景スプライトの描画処理を追加できる
	/// </summary>

	// スプライト描画後処理
	Sprite::PostDraw();

#pragma endregion
}