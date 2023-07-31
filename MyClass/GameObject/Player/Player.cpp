#include "Player.h"
#include <cassert>
#include <ImGuiManager.h>

// コンストラクタ
Player::Player() {

}
// デストラクタ
Player::~Player() { 
	// 弾をDELETE
	for (PlayerBullet* bullet : bullets_) {
		delete bullet;
	}
	delete sprite2DReticle_;
}




void Player::Initialize(Model* model, uint32_t textureHandle, Vector3 position) {

	// NULLポインタチェック
	assert(model);

	// 衝突属性を設定
	SetCollisionAttribute(kCollisionAttributePlayer);
	SetCollisionMask(~kCollisionAttributePlayer);

	input_ = Input::GetInstance();

	// モデル
	model_ = model;
	textureHandle_ = textureHandle;

	// ワールドトランスフォ－ムの初期化
	worldTransform_.Initialize();
	worldTransform_.translation_ = position;
	worldTransform_.UpdateMatrix();

	// 3Dレティクルのワールドトランスフォーム初期化
	worldTransform3DReticle_.Initialize();
	//worldTransform3DReticle_.translation_.z += 50.0f;
	//worldTransform3DReticle_.parent_ = &worldTransform_;
	//worldTransform3DReticle_.UpdateMatrix();

	// 2Dレティクル用テクスチャ取得
	uint32_t textureReticle = TextureManager::Load("Reticle.png");
	// スプライト生成
	sprite2DReticle_ = Sprite::Create(textureReticle, {0,0}, {1,1,1,1}, {0.5f, 0.5f});
	sprite2DReticle_->SetSize({64, 64});
}



void Player::Update(const ViewProjection& viewProjection) {
	// 弾更新
	for (PlayerBullet* bullet : bullets_){
		bullet->Update();
	}

	// デスフラグの立った弾を削除
	bullets_.remove_if([](PlayerBullet* bullet) {
		if (bullet->isDead()) {
			delete bullet;
			return true;
		}
		return false;
	});

// ーーーーーーーーーーーーーーーーーー//
#pragma region Translation処理

	// 移動処理（キーボード）
	//MoveKeyboard();
	// 移動処理（コントローラー）
	MoveJoyStick();

	//*--　　移動限界　　--*//

	// 移動限界座標
	const float kMoveLimitX = 68 / 2;
	const float kMoveLimitY = 37 / 2;
	
	// 範囲を超えない処理
	worldTransform_.translation_.x =
	    std::clamp(worldTransform_.translation_.x, -kMoveLimitX, +kMoveLimitX);
	worldTransform_.translation_.y =
	    std::clamp(worldTransform_.translation_.y, -kMoveLimitY, +kMoveLimitY);
	
	Vector2 spritePosition = sprite2DReticle_->GetPosition();
	spritePosition.x =
	    std::clamp(spritePosition.x, 0.0f, static_cast<float>(WinApp::GetInstance()->kWindowWidth));
	spritePosition.y =
		std::clamp(spritePosition.y, 0.0f, static_cast<float>(WinApp::GetInstance()->kWindowHeight));
	sprite2DReticle_->SetPosition(spritePosition);

#pragma endregion
// ーーーーーーーーーーーーーーーーーー//
#pragma region rotation処理
	// 押した方向で移動ベクトルを変更
	if (input_->PushKey(DIK_A)) {
		worldTransform_.rotation_.y -= kRotSpeed;
	} else if (input_->PushKey(DIK_D)) {
		worldTransform_.rotation_.y += kRotSpeed;
	}
#pragma endregion
// ーーーーーーーーーーーーーーーーーー//
#pragma region scale処理
#pragma endregion
// ーーーーーーーーーーーーーーーーーー//

	// ワールドトランスフォームの更新
	worldTransform_.UpdateMatrix();

	// レティクルのトランスフォーム更新
	ReticleUpdate(viewProjection);
}



void Player::Draw(const ViewProjection& viewProjection) {
	model_->Draw(worldTransform_, viewProjection, textureHandle_);

	// 弾描画
	for (PlayerBullet* bullet : bullets_) {
		bullet->Draw(viewProjection);
	}
}
void Player::DrawUI() {
	sprite2DReticle_->Draw();
}


void Player::OnCollision() {
	// 何もしない
}

Vector3 Player::GetWorldPosition() { return worldTransform_.GetWorldPosition(); }


/*ーーーーーーーーーーーーーー*/
/*　　　　　　関数　　　　　　*/
/*ーーーーーーーーーーーーーー*/

Vector2 Player::GetMousePosition() {
	POINT mousePosition;
	// マウス座標を取得
	GetCursorPos(&mousePosition);

	// クライアントエリア座標に変換する
	HWND hwnd = WinApp::GetInstance()->GetHwnd();
	ScreenToClient(hwnd, &mousePosition);

	// Vector2にして返す
	return Vector2(static_cast<float>(mousePosition.x), static_cast<float>(mousePosition.y));
}

void Player::MoveKeyboard() {
	// キャラクターの移動ベクトル
	Vector3 move = {0, 0, 0};

	// 押した方向で移動ベクトルを変更（左右）
	if (input_->PushKey(DIK_LEFT)) {
		move.x -= kCharacterSpeed;
	}
	if (input_->PushKey(DIK_RIGHT)) {
		move.x += kCharacterSpeed;
	}

	// 押した方向で移動ベクトルを変更（上下）
	if (input_->PushKey(DIK_UP)) {
		move.y += kCharacterSpeed;
	}
	if (input_->PushKey(DIK_DOWN)) {
		move.y -= kCharacterSpeed;
	}

	// 移動
	worldTransform_.translation_ += move;

	// マウス座標をスプライト座標にセット
	sprite2DReticle_->SetPosition(GetMousePosition());

	// 射撃（Rトリガーを押していたら）
	if (input_->PushKey(DIK_SPACE)) {
		Attack();
	}
}

void Player::MoveJoyStick() {
	// キャラクターの移動ベクトル
	Vector3 move = {0, 0, 0};
	// レティクルの座標
	Vector2 spritePosition = sprite2DReticle_->GetPosition();

	// ゲームパッドの状態を得る変数（XINPUT）
	XINPUT_STATE joyState;

	// ゲームパッド状態取得
	if (Input::GetInstance()->GetJoystickState(0, joyState)) {
		// キャラクター移動
		move.x += (float)joyState.Gamepad.sThumbLX / SHRT_MAX * kCharacterSpeed;
		move.y += (float)joyState.Gamepad.sThumbLY / SHRT_MAX * kCharacterSpeed;

		// レティクル移動
		spritePosition.x += (float)joyState.Gamepad.sThumbRX / SHRT_MAX * 15.0f;
		spritePosition.y -= (float)joyState.Gamepad.sThumbRY / SHRT_MAX * 15.0f;
	}

	// 移動
	worldTransform_.translation_ += move;
	// スプライトの座標変更を反映
	sprite2DReticle_->SetPosition(spritePosition);

	// 射撃（Rトリガーを押していたら）
	if (joyState.Gamepad.wButtons & XINPUT_GAMEPAD_RIGHT_SHOULDER) {
		Attack();
	}
}

void Player::ReticleUpdate(const ViewProjection& viewProjection) {
	// ビューポート行列
	Matrix4x4 matViewport = Matrix4x4::CreateViewportMatrix(0, 0, WinApp::kWindowWidth, WinApp::kWindowHeight, 0, 1);
	// ビュー行列とプロジェクション行列、ビューポート行列を合成する
	Matrix4x4 matViewProjectionViewport = viewProjection.matView * viewProjection.matProjection * matViewport;
	// 合成行列の逆行列を計算する
	Matrix4x4 matInverseVPV = Matrix4x4::Inverse(matViewProjectionViewport);

	// スプライト座標を受け取る
	Vector2 spritePosition = sprite2DReticle_->GetPosition();

	// ニアクリップとファークリップの面上のワールド座標を得る
	Vector3 posNear = Vector3(spritePosition.x, spritePosition.y, 0);
	Vector3 posFar = Vector3(spritePosition.x, spritePosition.y, 1);

	// スクリーン→ワールド座標変換（ここで3Dから2Dになる）
	posNear = Matrix4x4::TransformCoord(posNear, matInverseVPV);
	posFar = Matrix4x4::TransformCoord(posFar, matInverseVPV);
	// マウスレイの方向
	Vector3 mouseDirection = Normalize(posFar - posNear);
	// カメラから照準オブジェクトへの距離
	const float kDistanceTestObject = 50.0f;
	worldTransform3DReticle_.translation_ = posNear + mouseDirection * kDistanceTestObject;
	worldTransform3DReticle_.UpdateMatrix();
}

void Player::Attack() {
	// 弾の速度
	Vector3 velocity{};

	velocity = worldTransform3DReticle_.GetWorldPosition() - worldTransform_.GetWorldPosition();
	velocity = Normalize(velocity) * kBulletSpeed;
	// velocity = Matrix4x4::TransformNormal(velocity,
	// Matrix4x4::MakeRotateMatrix(worldTransform_.rotation_));

	// 弾を生成し、初期化
	PlayerBullet* newBullet = new PlayerBullet();
	newBullet->Initialize(model_, GetWorldPosition(), velocity);

	// 弾を登録する
	bullets_.push_back(newBullet);
}