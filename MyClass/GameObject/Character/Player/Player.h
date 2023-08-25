#pragma once
#include "../BaseCharacter.h"
#include <optional>
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
	/// 描画
	/// </summary>
	void Draw(const ViewProjection& viewProjection) override;

	/// <summary>
	/// ビュープロジェクションをセット
	/// </summary>
	/// <param name="viewProjection"></param>
	void SetViewProjection(const ViewProjection* viewProjection) { viewProjection_ = viewProjection; }

private: // メンバ定数
	// 移動速度
	float kCharacterSpeed = 0.3f;

private: // メンバ変数
	enum Parts {
		Body,
		Head,
		LeftArm,
		RightArm,
		Weapon,
	};

	// 振る舞い
	enum class Behavior {
		kRoot,		// 通常状態
		kAttack,	// 攻撃中
	};
	Behavior behavior_ = Behavior::kRoot;
	// 次の振る舞いをリクエスト
	std::optional<Behavior> behaviorRequest_ = std::nullopt;

	// カメラのビュープロジェクション
	const ViewProjection* viewProjection_ = nullptr;

private: // プライベートな関数
	
	/// <summary>
	/// 通常行動
	/// </summary>
	void BehaviorRootReset();
	void BehaviorRootUpdate();
	
	/// <summary>
	/// 攻撃行動
	/// </summary>
	void BehaviorAttackReset();
	void BehaviorAttackUpdate();

	// 攻撃行動各種値
	uint16_t attackAnimationFrame = 0;	// 全体のアニメーションフレーム
	const int kPreliminaryCycle_ = 15;	// 予備動作
	const float kPreliminary_ArmRotationX = 2.5f; // 腕のX回転量
	const float kPreliminary_WeaponRotationX = 1.2f; // 武器のX回転量
	const int kPreliminaryWaitCycle_ = 10;           // 予備動作の硬直
	const int kAttackCycle_ = 10;                    // 攻撃
	const int kAttackWaitCycle_ = 10;                // 攻撃後硬直

	// コントローラーでの操作
	void MoveJoyStick();

private: // アニメーション関連
	// モデルを初期値に戻す
	void SetModelNeutral();

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
