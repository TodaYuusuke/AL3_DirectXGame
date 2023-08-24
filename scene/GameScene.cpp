#include "GameScene.h"
#include "TextureManager.h"
#include <cassert>
#include <AxisIndicator.h>

GameScene::GameScene() {}

GameScene::~GameScene() {}

void GameScene::Initialize() {

	dxCommon_ = DirectXCommon::GetInstance();
	input_ = Input::GetInstance();
	audio_ = Audio::GetInstance();
	
	// 3Dモデルデータ
	playerBodyModel_.reset(Model::CreateFromOBJ("float_Body", true));
	playerHeadModel_.reset(Model::CreateFromOBJ("float_Head", true));
	playerLeftArmModel_.reset(Model::CreateFromOBJ("float_L_arm", true));
	playerRightArmModel_.reset(Model::CreateFromOBJ("float_R_arm", true));
	std::vector<Model*> playerModels = { playerBodyModel_.get(), playerHeadModel_.get(), playerLeftArmModel_.get(), playerRightArmModel_.get() };
	
	enemyBodyModel_.reset(Model::CreateFromOBJ("enemy_Body", true));
	enemyLeftWheelModel_.reset(Model::CreateFromOBJ("enemy_L_wheel", true));
	enemyRightWheelModel_.reset(Model::CreateFromOBJ("enemy_R_wheel", true));
	std::vector<Model*> enemyModels = { enemyBodyModel_.get(), enemyLeftWheelModel_.get(), enemyRightWheelModel_.get() };

	skydomeModel_.reset(Model::CreateFromOBJ("skydome", true));
	groundModel_.reset(Model::CreateFromOBJ("ground", true));

	// ビュープロジェクション
	viewProjection_.Initialize();

	// デバッグカメラの生成
	debugCamera_ = std::make_unique<DebugCamera>(1280, 720);
	// 軸方向表示を有効にする
	AxisIndicator::GetInstance()->SetVisible(true);
	// 軸方向表示が参照するビュープロジェクションを指定する（アドレス渡し）
	AxisIndicator::GetInstance()->SetTargetViewProjection(&viewProjection_);

	// スカイドームの生成
	skydome_ = std::make_unique<Skydome>();
	skydome_->Initialize(skydomeModel_.get());
	// グラウンドの生成
	ground_ = std::make_unique<Ground>();
	ground_->Initialize(groundModel_.get());
	
	// 自キャラと三人称カメラの生成
	player_ = std::make_unique<Player>();
	followCamera_ = std::make_unique<FollowCamera>();
	player_->Initialize(playerModels, {0.0f, 0.0f, 0.0f});
	followCamera_->Initialize();
	player_->SetViewProjection(&followCamera_->GetViewProjection());
	followCamera_->SetTarget(&player_->GetWorldTransform());

	// 敵
	enemy_ = std::make_unique<Enemy>();
	enemy_->Initialize(enemyModels, {0.0f, 1.6f, 30.0f});
}

void GameScene::Update() {
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

	ViewProjection v;
	// デバッグカメラ更新
	if (isDebugCameraActive_) {
		debugCamera_->Update();
		v = debugCamera_->GetViewProjection();
	// カメラ更新
	} else {
		followCamera_->Update();
		v = followCamera_->GetViewProjection();
	}
	viewProjection_.matView = v.matView;
	viewProjection_.matProjection = v.matProjection;
	// ビュープロジェクション行列の転送
	viewProjection_.TransferMatrix();


	// 自キャラの更新
	player_->Update();
	// 敵の更新
	enemy_->Update();
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
	
	// スカイドームの描画
	skydome_->Draw(viewProjection_);
	// グラウンドの描画
	ground_->Draw(viewProjection_);

	// 自キャラの描画
	player_->Draw(viewProjection_);
	// 敵の描画
	enemy_->Draw(viewProjection_);

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
