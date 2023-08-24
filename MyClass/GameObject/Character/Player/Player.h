#pragma once
#include "../BaseCharacter.h"

#define _USE_MATH_DEFINES
#include <math.h>

class Player : public BaseCharacter {

public: // メンバ関数

	/// <summary>
	/// 初期化
	/// </summary>
	void Initialize(const std::vector<Model*>& models, Vector3 position) override;

	/// <summary>
	/// 更新
	/// </summary>
	void Update() override;

	/// <summary>
	/// ビュープロジェクションをセット
	/// </summary>
	/// <param name="viewProjection"></param>
	void SetViewProjection(const ViewProjection* viewProjection) { viewProjection_ = viewProjection; }

private: // メンバ定数
	float kCharacterSpeed = 0.3f;

private: // メンバ変数
	enum Parts {
		Body,
		Head,
		LeftArm,
		RightArm,
	};

	// カメラのビュープロジェクション
	const ViewProjection* viewProjection_ = nullptr;

private: // プライベートな関数
	
	// コントローラーでの操作
	void MoveJoyStick();

private: // アニメーション関連
	// 関数
	void InitializeAnimation();
	void Animation();

	// 浮遊ギミック
	const uint16_t kFloatingCycle_ = 60;
	const double kFloatingStep_ = 2.0f * M_PI / kFloatingCycle_;	
	const float kFloatingHeight = 0.2f;
	float floatingParameter_ = 0.0f;
	void FloatingUpdate();

	// 腕を振るアニメーション
	const uint16_t kArmSwingCycle_ = 60;
	const double kArmSwingStep_ = 2.0f * M_PI / kFloatingCycle_;
	const float kArmSwingHeight = 0.2f;
	float armSwingParameter_ = 0.0f;
	void ArmSwingUpdate();
};
