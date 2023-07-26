#include "GameScene.h"
#include "TextureManager.h"
#include "AxisIndicator.h"
#include <cassert>
#include <ImGuiManager.h>
#include <fstream>

GameScene::GameScene() {}

GameScene::~GameScene() {
	delete playerModel;
	delete enemyModel;
	delete skydomeModel;
	delete debugCamera_;
	delete railCamera_;
	delete collisionManager_;
	delete player_;
	for (Enemy* enemy : enemys_) {
		delete enemy;
	}
	for (EnemyBullet* enemyBullet : enemyBullets_) {
		delete enemyBullet;
	}
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

	// レールカメラの生成
	railCamera_ = new RailCamera();
	// レールカメラの初期化
	railCamera_->Initialize({0, 0, -15}, {0, 0, 0});

	// 当たり判定マネージャーの生成
	collisionManager_ = new CollisionManager();
	// 天球の生成
	skydome_ = new Skydome();
	// 天球の初期化
	skydome_->Initialize(skydomeModel);

	// 自キャラの生成
	player_ = new Player();
	Vector3 playerPosition(0, -3, 15);
	// 自キャラの初期化
	player_->Initialize(playerModel, playerTexture, playerPosition);
	player_->SetParent(&railCamera_->GetWorldTransform());

	// 敵の初期化と生成
	enemys_.clear();
	AddEnemy({20, 3, 50});
	AddEnemy({0, 3, 50});
	AddEnemy({-20, 3, 50});

	// 弾初期化
	enemyBullets_.clear();

	// ファイル読み込み
	LoadEnemyPopData();
}

void GameScene::Update() {
	// ファイル読み込み更新
	UpdateEnemyPopCommands();

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

	ViewProjection v;
	// デバッグカメラ更新
	if (isDebugCameraActive_) {
		debugCamera_->Update();
		v = debugCamera_->GetViewProjection();
	// レールカメラ更新
	} else {
		railCamera_->Update();
		v = railCamera_->GetViewProjection();
	}
	viewProjection_.matView = v.matView;
	viewProjection_.matProjection = v.matProjection;
	// ビュープロジェクション行列の転送
	viewProjection_.TransferMatrix();

	// 自キャラの更新
	player_->Update();

	// 敵の更新
	for (Enemy* enemy : enemys_) {
		enemy->Update();
	}
	// デスフラグの立った敵を削除
	enemys_.remove_if([](Enemy* enemy) {
		if (!enemy->isAlive()) {
			delete enemy;
			return true;
		}
		return false;
	});

	// 敵弾の更新
	for (EnemyBullet* enemyBullet : enemyBullets_) {
		enemyBullet->Update();
	}
	// デスフラグの立った弾を削除
	enemyBullets_.remove_if([](EnemyBullet* bullet) {
		if (!bullet->isAlive()) {
			delete bullet;
			return true;
		}
		return false;
	});


	// 当たり判定を登録
	collisionManager_->PushCollider(player_);
	// 弾リストの取得
	const std::list<PlayerBullet*>& playerBullets = player_->GetBullets();
	// 自弾の全ての当たり判定
	for (PlayerBullet* bullet : playerBullets) {
		collisionManager_->PushCollider(bullet);
	}
	// 敵の全ての当たり判定
	for (Enemy* enemy : enemys_) {
		collisionManager_->PushCollider(enemy);
	}
	// 敵弾の全ての当たり判定
	for (EnemyBullet* bullet : enemyBullets_) {
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
	for (Enemy* enemy : enemys_) {
		enemy->Draw(viewProjection_);
	}
	// 敵弾の描画
	for (EnemyBullet* enemyBullet : enemyBullets_) {
		enemyBullet->Draw(viewProjection_);
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

void GameScene::AddEnemy(Vector3 position) {
	Enemy* newEnemy = new Enemy();

	newEnemy->SetPlayer(player_);
	newEnemy->SetGameScene(this);
	newEnemy->Initialize(enemyModel, enemyTexture, position);

	enemys_.push_back(newEnemy);
}

void GameScene::AddEnemyBullet(EnemyBullet* enemyBullet) {
	// リストに登録する
	enemyBullets_.push_back(enemyBullet);
}

void GameScene::LoadEnemyPopData() {
	// ファイルを開く
	std::ifstream file;
	file.open("./Resources/enemyPop.csv");
	assert(file.is_open());

	// ファイルの内容を文字列をストリームにコピー
	enemyPopCommands << file.rdbuf();

	// ファイルを閉じる
	file.close();
}

void GameScene::UpdateEnemyPopCommands() {
	// 待機処理
	if (isWaiting) {
		waitTimer--;
		if (waitTimer <= 0) {
			// 待機完了
			isWaiting = false;
		}
		return;
	}
	
	// 1行分の文字列を入れる変数
	std::string line;

	// コマンド実行ループ
	while (getline(enemyPopCommands, line)) {
		// 1行分の文字列をストリームに変換して解析しやすくする
		std::istringstream line_stream(line);

		std::string word;
		// ,区切りで行の先頭文字列を取得
		getline(line_stream, word, ',');

		// "//"から始まる行はコメント
		if (word.find("//") == 0) {
			// コメント行を飛ばす
			continue;
		}

		else if (word.find("POP") == 0) {
			// x座標
			getline(line_stream, word,',');
			float x = static_cast<float>(std::atof(word.c_str()));
			// y座標
			getline(line_stream, word, ',');
			float y = static_cast<float>(std::atof(word.c_str()));
			// z座標
			getline(line_stream, word, ',');
			float z = static_cast<float>(std::atof(word.c_str()));

			// 敵を発生させる
			AddEnemy(Vector3(x, y, z));
		}

		else if (word.find("WAIT") == 0) {
			getline(line_stream, word, ',');

			// 待機時間
			isWaiting = true;
			waitTimer = atoi(word.c_str());

			// コマンドループを抜ける
			break;
		}
	}
}