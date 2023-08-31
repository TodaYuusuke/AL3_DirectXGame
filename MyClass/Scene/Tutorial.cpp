#include "Tutorial.h"
#include "GamePlay.h"

// 初期化
void Tutorial::Initialize() {
	dxCommon_ = DirectXCommon::GetInstance();
	input_ = Input::GetInstance();
	audio_ = Audio::GetInstance();

	// スプライト生成
	tutorialSprite_.reset(Sprite::Create(
	    TextureManager::Load("tutorialScene.png"), {0.0f, 0.0f}, {1, 1, 1, 1},
	    {0.0f, 0.0f}));
	//titleSprite_->SetSize({1280, 720});

	// サウンドデータ読み込み
	gameStartSE = audio_->LoadWave("audio/title/GameStart.wav");
}
// 更新
void Tutorial::Update() {
	// ゲームパッドの状態を得る変数（XINPUT）
	XINPUT_STATE joyState;

	// ゲームパッド状態取得
	if (Input::GetInstance()->GetJoystickState(0, joyState)) {
		// Xトリガーを押していたら >>> 次のシーンへ
		if (!preX && joyState.Gamepad.wButtons & XINPUT_GAMEPAD_X) {
			audio_->PlayWave(gameStartSE, false, 0.5f);
			nextScene_ = new GamePlay();
		}
	}
	preX = joyState.Gamepad.wButtons & XINPUT_GAMEPAD_X;
}
// 描画
void Tutorial::Draw() {

	// コマンドリストの取得
	ID3D12GraphicsCommandList* commandList = dxCommon_->GetCommandList();
	
	// 前景スプライト描画前処理
	Sprite::PreDraw(commandList);

	/// <summary>
	/// ここに前景スプライトの描画処理を追加できる
	/// </summary>
	tutorialSprite_->Draw();

	// スプライト描画後処理
	Sprite::PostDraw();
}