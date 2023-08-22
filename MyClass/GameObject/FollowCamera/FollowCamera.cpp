#include "FollowCamera.h"
#include <Input.h>
#include <ImGuiManager.h>

void FollowCamera::Initialize() {
	// ビュープロジェクションの初期化
	viewProjection_.Initialize();
	rotation_ = {0.0f, 0.0f, 0.0f};
}

void FollowCamera::Update() {
	// 追従対象がいれば
	if (target_) {
		// ゲームパッドの状態を得る変数（XINPUT）
		XINPUT_STATE joyState;

		// ゲームパッド状態取得
		if (Input::GetInstance()->GetJoystickState(0, joyState)) {
			// キャラクター移動
			Vector3 turn = {
			    -(float)joyState.Gamepad.sThumbRY / SHRT_MAX,
			    (float)joyState.Gamepad.sThumbRX / SHRT_MAX,
			    0.0f};
			rotation_ += Normalize(turn) * kCameraTurnSpeed;
		}


		// 追従対象からカメラまでのオフセット
		Vector3 offset = {0.0f, 4.0f, -20.0f};

		// カメラから追従対象に対する角度を求める
		Vector3 to = target_->translation_ - offset;

		offset = offset * Matrix4x4::MakeRotateMatrix(rotation_);

		// 座標をコピーしてオフセット分ずらす
		viewProjection_.translation_ = target_->translation_ + offset;
		viewProjection_.rotation_ = rotation_;
	}

	// カメラオブジェクトのワールド行列からビュー行列を計算する
	viewProjection_.UpdateViewMatrix();
}